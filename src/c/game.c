// License:MIT License
// copyright-holders:Hitoshi Iwai

#include <msx.h>
#include <msx/gfx.h>
#include "const.h"
#include "game.h"

// pcgdata.asm : BANK_PATTERN_0への参照
extern uint8_t BANK_PATTERN_0[];

// pcgdata.asm : BANK_COLOR_0への参照
extern uint8_t BANK_COLOR_0[];

// ゲーム状態Enum
typedef enum {
    STATE_START,                            // スタート
    STATE_GAME,                             // ゲームメイン
    STATE_CLEAR,                            // クリア
    STATE_MISS,                             // ミス
    STATE_OVER                              // ゲームオーバー
} game_state_t;

// 操作入力情報構造体
typedef struct {
    uint8_t input_stick;                    // 入力バッファ（レバー）
    uint8_t input_trigger;                  // 入力バッファ（トリガ）
    bool_t input_stick_flag;                // 入力フラグ（レバー）
    bool_t input_trigger_flag;              // 入力フラグ（トリガ）
} Control_t;
Control_t control;

// ゲーム情報構造体
typedef struct {
    uint8_t round;                          // ラウンド
    uint16_t score;                         // スコア
    game_state_t state;                     // ゲームの状態
    uint16_t tick;                          // ゲーム経過時間
} Game_t;
Game_t game;

// プレイヤー構造体
typedef struct {
    uint8_t number;                         // プレイヤーの数字（内部的には表示する値+1を保持）
    uint8_t left;                           // プレイヤーの残り
    uint8_t shot_left;                      // プレイヤーの残弾数
} Player_t;
Player_t player;

// 敵構造体
typedef struct {
    uint8_t line[6];                        // 敵の列（内部的には表示する値+1を保持、ゼロは空白）
    uint8_t wait_cnt;                       // 敵のウェイトカウンタ
    uint8_t wait_time;                      // 敵のウェイトタイム
    uint8_t left;                           // 敵の残数
    uint8_t summary;                        // 敵の数字の合計数
    bool_t ufo_flg;                         // UFO発生フラグ
} Enemy_t;
Enemy_t enemy;

// サウンドデータ
uint8_t sound_data[5][16] = {
    // 停止（初期化）
    { 0x07, 0xB8, 0x08, 0x00, 0x09, 0x00, 0x0A, 0x00, 0x0B, 0x0B, 0x0C, 0x00, 0x0D, 0x00, 0xFF, 0xFF},
    // アタリ
    { 0x07, 0xB8, 0x08, 0x10, 0x0B, 0x03, 0x0C, 0x00, 0x0D, 0x0C, 0x00, 0xBE, 0x01, 0x00, 0xFF, 0xFF},
    // クリア
    { 0x07, 0xB8, 0x08, 0x10, 0x0B, 0x02, 0x0C, 0x00, 0x0D, 0x0C, 0x00, 0xAA, 0x01, 0x00, 0xFF, 0xFF},
    // ハズレ
    { 0x07, 0xB8, 0x08, 0x10, 0x0B, 0x0F, 0x0C, 0x00, 0x0D, 0x0C, 0x00, 0xAF, 0x01, 0x06, 0xFF, 0xFF},
    // ミス
    { 0x07, 0xB8, 0x08, 0x10, 0x0B, 0x03, 0x0C, 0x0D, 0x0C, 0x00, 0x00, 0x7D, 0x01, 0x01, 0xFF, 0xFF}
};

// 仮想画面
uint8_t offScreen[OFFSCR_SIZE];

// ゲーム画面
char mainScreenData[] = {
    136,137,138,139,140,141,142,143,144,144,144,144,
    128,133,133,133,133,133,133,133,133,133,133,129,
    134, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,135,
    134, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,135,
    130,132,132,132,132,132,132,132,132,132,132,131,
    144,144,144,144,144,144,144,144,144,144,144,144
};

// キー操作ガイド
char controlGuideData[] = {
    145,146, 32, 32, 32, 32,149,150, 32, 32, 32, 32,
    147,148,'A','I','M', 32,151,152,'F','I','R','E'
};

// LCDパターン
//             idx    0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15
//             ptn    0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   n,   -,  一,  二,  三,  SP
char lcdPtn0[16] = {'a', 'b', 'c', 'c', 'd', 'e', 'e', 'c', 'a', 'a', '`', '`', '`', '`', 'f', '`'};
char lcdPtn1[16] = {'p', 'q', 'r', 's', 't', 's', 'u', 'q', 'u', 's', 'v', 'y', 'x', 'w', 'w', '`'};

// LCDデータ
uint8_t lcdData[10] = { 15, 15, 15, 15, 15, 15, 15, 15, 15, 15};

// サウンド再生時間
uint16_t sound_time = 0;

// VSYNC処理実行フラグ
bool_t vsync_exec = false;


/*
 * PSGレジスタ初期化
 *
 * args:
 * - reg            uint8_t     レジスタ番号
 * - dat            uint8_t     データ
 *
 * return:
 * - void
 */
void psg_init()
{
// __INTELLISENSE__ 判定は vscode で非標準インラインアセンブル構文をエラーにしないように挿入
#ifndef __INTELLISENSE__
#asm
    CALL    $0090       ; CALL GICINI
#endasm
#endif
}

/*
 * PSGレジスタ書き込み
 *
 * args:
 * - reg            uint8_t     レジスタ番号
 * - dat            uint8_t     データ
 *
 * return:
 * - void
 */
void psg_write(uint8_t reg, uint8_t dat)
{
// __INTELLISENSE__ 判定は vscode で非標準インラインアセンブル構文をエラーにしないように挿入
#ifndef __INTELLISENSE__
#asm
    LD      HL , 2      ;
    ADD     HL, SP      ; skip over return address on stack
    LD      E, (HL)     ; WRTPSG(E)
    INC     HL          ; skip value call stack
    INC     HL          ;
    LD      A,(HL)      ; WRTPSG(A)
    CALL    $0093       ; call WRTPSG(A, E)
#endasm
#endif
}

/*
 * サウンド発声処理
 *
 * args:
 * - sound_no       uint8_t     sound番号
 *
 * return:
 * - void
 */
void play_sound(uint8_t sound_no) {
    uint8_t i = 0;
    char* _sound_data_p = sound_data[sound_no];

    while (0 == 0) {
        if (_sound_data_p[i] == 0xFF) {
            break;
        } else {
            psg_write(_sound_data_p[i++], _sound_data_p[i++]);
        }
    }
}

/*
 * 操作入力初期化処理
 *
 * args:
 * - void
 *
 * return:
 * - void
 */
void init_control()
{
    control.input_stick = STICK_NONE;
    control.input_trigger = TRIGGER_OFF;
    control.input_stick_flag = false;
    control.input_trigger_flag = false;
}

/*
 * 操作入力取得処理
 *
 * args:
 * - void
 *
 * return:
 * - void
 */
void get_control()
{
    control.input_stick = get_stick(0) + get_stick(1);
    // レバー押しっぱなし抑止
    if (control.input_stick == STICK_NONE) {
        control.input_stick_flag = false;
    } else {
        if (control.input_stick_flag) {
            control.input_stick = STICK_NONE;
        } else {
            control.input_stick_flag = true;
        }
    }

    control.input_trigger = get_trigger(0) + get_trigger(1);
    // トリガ押しっぱなし抑止
    if (control.input_trigger == TRIGGER_OFF) {
        control.input_trigger_flag = false;
    } else {
        if (control.input_trigger_flag) {
            control.input_trigger = TRIGGER_OFF;
        } else {
            control.input_trigger_flag = true;
        }
    }
}

/*
 * ゲーム状態変更
 *
 * args:
 * - s              game_state_t ゲーム状態
 *
 * return:
 * - void
 */
void change_game_state(game_state_t s)
{
    game.state = s;
    game.tick = 0;

    while (control.input_stick != STICK_NONE || control.input_trigger != TRIGGER_OFF) {
        get_control();                      // 操作入力取得
    }
}

/*
 * オフスクリーンクリア
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void offscr_clear()
{
    for (uint16_t i = 0; i < OFFSCR_SIZE; i++) {
        offScreen[i] = CHR_SPACE;
    }
}

/*
 * オフスクリーンへの1行書き込み
 * - 引数x,yの位置にテキストを書き込む。
 * - 画面端のはみ出し処理はしていないので注意。
 *
 * args:
 * - x              uint8_t     描画先のX座標
 * - y              uint8_t     描画先のY座標
 * - text           char*       表示テキストのアドレス、または配列
 *
 * return:
 * - void
 */
void offscr_putTextLn(uint8_t x, uint8_t y, char* text)
{
    for (uint8_t i = 0; i < strlen(text); i++) {
        offScreen[y * OFFSCR_WIDTH + x] = text[i];
        x++;
    }
}

/*
 * オフスクリーンへの矩形書き込み
 * - 引数x,yの位置からw,hの幅、高さでテキストを書き込む。
 * - テキストが描画範囲に満たない場合は、そこで処理を中断する。
 * - 画面端のはみ出し処理はしていないので注意。←さすがにしないとダメだろ
 *
 * args:
 * - x              uint8_t     描画更新先のX座標
 * - y              uint8_t     描画先のY座標
 * - w              uint8_t     描画幅
 * - h              uint8_t     描画高さ
 * - text           char*       表示テキストのアドレス、または配列
 *
 * return:
 * - void
 */
void offscr_putTextRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, char* text)
{
    uint16_t offscreen_p = y * OFFSCR_WIDTH + x;
    uint16_t p = 0;

    for (uint8_t j = 0; j < h; j++) {
        for (uint8_t i = 0; i < w; i++) {
            offScreen[offscreen_p++] = text[p++];
        }
        offscreen_p = offscreen_p + OFFSCR_WIDTH - w;
    }
}

/*
 * LCDデータクリア
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void lcd_clear()
{
    for (uint8_t i = 0; i < 10; i++) {
        lcdData[i] = LCD_SPACE;
    }
}

/*
 * LCDに文字列データ設定
 * - 表示可能な文字以外は空白とする
 *
 * args:
 * - text           char*       表示テキストのアドレス、または配列
 * - pos            uint8_t     設定開始位置
 *
 * return:
 * - void
 */
void lcd_setText(char* text, uint8_t pos)
{
    char v;

    for (uint8_t i = 0; i < strlen(text); i++) {
        v = text[i];

        // 文字データの場合は、LCDデータに変換
        if (v == CHR_MINUS) {
            // LCDデータ 45 は '-'として11番目のパターンを設定
            v = LCD_MINUS;
        } else if (v >= CHR_0 && v <= CHR_9) {
            // LCDデータ 48～57 は数値のキャラクターなので、 0～9番目のパターンを設定
            v = v - 48;
        } else if (v >= CHR_A && v <= CHR_C) {
            // LCDデータ 65～67 は残機数のキャラクターなので、12～14番目のパターンを設定
            v = v - 53;
        } else {
            // 上記以外は空白として15番目のパターンを設定
            v = LCD_SPACE;
        }
        lcdData[i + pos] = v;
    }
}

/*
 * LCDデータに数値を設定
 * - 整数のみ対応
 * - 指定桁数以上の値は切捨て
 *
 * args:
 * - val            uint16_t    変換する数値
 * - pos            uint8_t     設定開始位置
 * - len            uint8_t     桁数
 *
 * return:
 * - void
 *
 */
void lcd_setNumber(uint16_t val, uint8_t pos, uint8_t len)
{
    uint8_t i = 0;
    uint8_t num[10];

    // 数値を文字列に変換
    // 下の桁から設定するため、ここの結果は逆順になる
    do {
        num[i++] = val % 10; // + '0';
    } while ((val /= 10) > 0 && i < len); // (val = val / 10)の結果が0より大きい場合は繰り返す

    // 表示開始位置補正
    pos = pos + (len - i);

    // 文字列を逆順にLCDデータに設定
    for (int j = pos; i > 0; i--) {
        lcdData[j++] = num[i - 1];
    }
}

/*
 * LCDデータをオフスクリーンへ書き込む
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void lcd_update()
{
    uint16_t offscr_p0 = 10 * OFFSCR_WIDTH + 11;
    uint16_t offscr_p1 = 11 * OFFSCR_WIDTH + 11;

    for (int i = 0; i < 10; i++) {
        offScreen[offscr_p0++] = lcdPtn0[lcdData[i]];
        offScreen[offscr_p1++] = lcdPtn1[lcdData[i]];
    }
}

/*
 * ゲーム画面描画
 * H.TIMI割り込みで呼ばれる
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_draw()
{
#ifndef __INTELLISENSE__
#asm
    EXX
#endasm;
#endif
    // VSYNC処理が許可されているときだけ処理する
    if (vsync_exec) {
        // パターンネームテーブル更新
        vwrite(offScreen, VRAM_PTN_NAME_TBL, VRAM_PTN_NAME_SIZE);
        // VSYNC処理不許可にする
        vsync_exec = false;
    }

#ifndef __INTELLISENSE__
#asm
    EXX
#endasm;
#endif
}

/*
 * ゲーム初期化
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_init()
{
    // 割り込み処理不許可
    vsync_exec = false;

    // 画面初期化
    set_color(15, 1, 1);
    set_mangled_mode();
    msx_set_sprite_mode(sprite_large);

    // キークリックスイッチOFF
    *(uint8_t *)MSX_CLIKSW = 0;

    // パターンジェネレータテーブル設定
    vwrite(BANK_PATTERN_0, VRAM_PTN_GENR_TBL1, VRAM_PTN_GENR_SIZE);
    vwrite(BANK_PATTERN_0, VRAM_PTN_GENR_TBL2, VRAM_PTN_GENR_SIZE);
    vwrite(BANK_PATTERN_0, VRAM_PTN_GENR_TBL3, VRAM_PTN_GENR_SIZE);

    // カラーテーブル設定
    vwrite(BANK_COLOR_0, VRAM_COLOR_TBL1, VRAM_COLOR_SIZE);
    vwrite(BANK_COLOR_0, VRAM_COLOR_TBL2, VRAM_COLOR_SIZE);
    vwrite(BANK_COLOR_0, VRAM_COLOR_TBL3, VRAM_COLOR_SIZE);

    // PSG初期化
    psg_init();

    // PSGレジスタの初期設定
    play_sound(SOUND_STOP);

    // H.TIMIフック設定
#ifndef __INTELLISENSE__
#asm
    DI
#endasm;
    #endif
    uint8_t *h_timi = (uint8_t *)MSX_H_TIMI;
    uint16_t hook_addr = (uint16_t)&game_draw;
    h_timi[0] = 0xc3; // JP
    h_timi[1] = (uint8_t)(hook_addr & 0xff);
    h_timi[2] = (uint8_t)((hook_addr & 0xff00) >> 8);
#ifndef __INTELLISENSE__
#asm
    EI
#endasm;
#endif

    // 画面の基本部分を描画
    offscr_putTextRect(10, 8, 12, 6, mainScreenData);
    offscr_putTextRect(10,19, 12, 2, controlGuideData);
    offscr_putTextLn(24, 0, "./250306");

    change_game_state(STATE_OVER);
}

/*
 * ゲーム開始処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_start()
{
    if (game.tick == 1) {
        lcd_clear();
        lcd_setNumber(game.round, 0, 3);
        lcd_setText("-", 3);
        lcd_setNumber(game.score, 4, 6);
        lcd_update();
    } else if (game.tick > 120) {
        lcd_clear();
        offscr_putTextLn( 7, 15, ":; <<<<<<<<<<<<<<<");
        player.number = 1;
        player.shot_left = 30;
        for (int i = 0; i < 6; i++) {
            enemy.line[i] = 0;
        }
        enemy.summary = 0;
        enemy.left = 16;
        enemy.ufo_flg = false;
        enemy.wait_cnt = 254;
        init_control();
        change_game_state(STATE_GAME);
    }
}

/*
 * ゲームメイン／ショット処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_main_player_shot()
{
    bool_t hit;
    uint8_t hit_idx;
    uint8_t check_cnt;

    if (--player.shot_left == 0) {
        // 弾切れしたらゲームオーバー
        change_game_state(STATE_OVER);
        return;
    }

    // ビームゲージ更新
    offscr_putTextLn(10 + player.shot_left / 2, 15, "> ");
    if (player.shot_left % 2 != 0) {
        offscr_putTextLn(10 + player.shot_left / 2, 15, "=");
    }

    // ヒットチェック
    hit_idx = 0;
    for (int i = 0; i < 6; i++) {
        if (enemy.line[i] == player.number) {
            enemy.line[i] = 0;
            hit_idx = i + 1;
            break;
        }
    }
    if (hit_idx == 0) {
        // はずれ
        play_sound(SOUND_FAIL);
        sound_time = 5;
        return;
    }

    // あたり
    // 効果音再生
    play_sound(SOUND_HIT);
    sound_time = 5;

    // スコア加算
    game.score += ((player.number == 11) ? 300 : 10);

    // 敵表示数チェック
    check_cnt = 0;
    for (int i = 0; i < 6; i++) {
        check_cnt += enemy.line[i];
    }
    if (enemy.left < 1 && check_cnt == 0) {
        // 敵残数と表示数がゼロならクリア
        change_game_state(STATE_CLEAR);
        return;
    }

    // 敵を詰める
    hit_idx--;
    if (hit_idx > 0) {
        for (int i = hit_idx; i > 0; i--) {
            enemy.line[i] = enemy.line[i - 1];
            enemy.line[i - 1] = 0;
        }
    }

    // UFO出現チェック
    if (player.number > 1 && player.number < 11) {
        enemy.summary += player.number - 1;
        if (enemy.summary % 10 == 0 && enemy.summary > 0) {
            // 倒した敵の数の合計が10の倍数ならUFO出現
            enemy.ufo_flg = true;
        }
    }
}

/*
 * ゲームメイン／プレイヤー処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_main_player()
{
    get_control();                          // 操作入力取得
    if (control.input_stick == STICK_LEFT) {
        // 左入力で数字変更（0～9、n）
        player.number++;
        if (player.number > 11) {
            player.number = 1;
        }
    } else if (control.input_stick == STICK_RIGHT || control.input_trigger) {
        // 右入力でショット
        control.input_stick_flag = true;
        game_main_player_shot();
    }
}

/*
 * ゲームメイン／エネミー処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_main_enemy()
{
    // 敵出現待ちの時は処理を抜ける
    if (enemy.wait_cnt++ < enemy.wait_time) {
        return;
    }
    // ウェイトカウンタリセット
    enemy.wait_cnt = 0;
    // 既に一番左に敵がいたらミス
    if (enemy.line[0] > 0) {
        change_game_state(STATE_MISS);
        return;
    }
    // 全体を左にシフト
    for (int i = 0; i < 5; i++) {
        enemy.line[i] = enemy.line[i + 1];
    }
    if (enemy.left > 0) {
        // 敵残数デクリメント
        enemy.left--;
        if (enemy.ufo_flg) {
            // UFO出現
            enemy.ufo_flg = false;
            enemy.line[5] = 11;
        } else {
            // 敵出現
            enemy.line[5] = get_rnd() % 10 + 1;
        }
    } else {
        // 敵残数ゼロなら何も表示しない
        enemy.line[5] = 0;
    }
}

/*
 * ゲームメイン／LCDデータ更新処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_main_updateLCDData()
{
    lcdData[1] = player.number - 1;         // プレイヤー
    lcdData[2] = player.left + 11;          // 残機数
    for (int i = 0; i < 6; i++) {           // 敵
        if (enemy.line[i] == 0) {
            lcdData[i + 3] = LCD_SPACE;
        } else {
            lcdData[i + 3] = enemy.line[i] - 1;
        }
    }
    lcd_update();
}

/*
 * ゲームメイン処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_main()
{
    game_main_player();
    game_main_enemy();
    game_main_updateLCDData();
}

/*
 * ゲームクリア処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_clear()
{
    if (game.tick == 1 || game.tick == 3 || game.tick == 5) {
        play_sound(SOUND_CLEAR);
        sound_time = 10;
    } else if (game.tick == 2 || game.tick == 4 || game.tick == 6) {
        play_sound(SOUND_STOP);
        sound_time = 10;
    } else if (game.tick > 60) {
        enemy.wait_time = enemy.wait_time - 5;
        if (enemy.wait_time < 40) {
            enemy.wait_time = 40;
        }
        game.round++;
        change_game_state(STATE_START);
    }
}

/*
 * ゲームミス処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_miss()
{
    if (game.tick == 1) {
        play_sound(SOUND_MISS);
        sound_time = 20;
        player.left--;
        if (player.left == 0) {
            change_game_state(STATE_OVER);
        } else {
            // LCD表示
            lcd_clear();
            lcd_setNumber(game.round, 0, 3);
            lcd_setText("-", 3);
            lcd_setNumber(game.score, 4, 6);
            lcd_update();
        }
    } else if (game.tick > 100) {
        // 画面上に残った敵を残りに加える
        for (int i = 0; i < 6; i++) {
            if (enemy.line[i] > 0) {
                enemy.left++;
            }
            enemy.line[i] = 0;
        }
        lcd_clear();
        player.number = 1;
        enemy.summary = 0;
        enemy.wait_cnt = 254;
        sound_time = 0;
        init_control();
        change_game_state(STATE_GAME);
    }
}

/*
 * ゲームオーバー処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_over()
{
    if (game.tick == 1) {
        // メッセージ表示
        offscr_putTextLn(11,  6, "GAME  OVER");
        // LCD表示
        lcd_clear();
        lcd_setNumber(game.round, 0, 3);
        lcd_setText("-", 3);
        lcd_setNumber(game.score, 4, 6);
        lcd_update();
    } else if (game.tick == 90) {
        // メッセージ表示
        offscr_putTextLn( 7, 15, "  PUSH SPACE KEY  ");
        init_control();
    } else {
        int rnd = get_rnd();                    // 乱数を発行してパターンを変える
        get_control();                          // 操作入力取得
        if (control.input_trigger != 0) {
            // メッセージ消去
            offscr_putTextLn(11,  6, "          ");
            offscr_putTextLn( 7, 15, ":; <<<<<<<<<<<<<<<");
            // 全体初期設定
            game.round = 1;
            game.score = 0;
            player.left = 3;
            enemy.wait_time = 120;
            // ゲームスタート処理に遷移
            change_game_state(STATE_START);
        }
    }
}

/*
 * ゲーム処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_update()
{
    if (sound_time > 0) {
        if (--sound_time == 0) {
            // 効果音停止
            play_sound(SOUND_STOP);
        }
    } else {
        game.tick++;
        switch (game.state) {
            case STATE_START:
                game_start();
                break;
            case STATE_GAME:
                game_main();
                break;
            case STATE_CLEAR:
                game_clear();
                break;
            case STATE_MISS:
                game_miss();
                break;
            case STATE_OVER:
                game_over();
                break;
        }
    }

    // vsync処理を許可し、終了を待つ
    vsync_exec = true;
    while (vsync_exec) {
        // NOP
    }
}
