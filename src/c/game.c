// License:MIT License
// copyright-holders:Hitoshi Iwai

#include <stdio.h>
#include <msx.h>
#include <msx/gfx.h>
#include "const.h"
#include "game.h"


// pcgdata.asm : BANK_PATTERN_0への参照
extern uint8_t BANK_PATTERN_0[];

// pcgdata.asm : BANK_COLOR_0への参照
extern uint8_t BANK_COLOR_0[];

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
int lcdData[10] = { 15, 15, 15, 15, 15, 15, 15, 15, 15, 15};

// 入力バッファ（方向）
uint8_t buff_stick = 0;

// 入力バッファ（トリガ）
int buff_trigger = 0;

// 入力フラグ
bool_t input_flag = false;

// ラウンド
uint8_t game_round = 0;

// スコア
uint16_t game_score = 0;

// プレイヤーの数字
// 内部的には、表示する値+1を保持
uint8_t player_number = 1;

// プレイヤーの残り
uint8_t player_left = 3;

// 敵の列
// 内部的には、表示する値+1を保持（ゼロは空白）
uint8_t enemy_line[] = {0, 0, 0, 0, 0, 0};

// ゲームの状態
game_state_t game_state;

// ゲーム経過時間
uint16_t game_tick = 0;

// VSYNC処理実行フラグ
bool_t vsync_exec = false;


/*
 * ゲーム状態変更
 *
 * args:
 * - game_state_t    state       ゲーム状態
 *
 * return:
 * - void
 */
void change_game_state(game_state_t s)
{
    game_state = s;
    game_tick = 0;
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
void offscr_clear()__z88dk_fastcall
{
    for (uint16_t i = 0; i < OFFSCR_SIZE; i++) {
        offScreen[i] = CHR_SPACE;
    }
}

/**
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
void lcd_clear()__z88dk_fastcall
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
 *
 * return:
 * - void
 */
void lcd_setText(char* text)__z88dk_fastcall
{
    char v;

    for (uint8_t i = 0; i < 10; i++) {
        v = text[i];

        // 文字データの場合は、LCDデータに変換
        if (v > 10) {
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
            lcdData[i] = v;
        }
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
void lcd_update()__z88dk_fastcall
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
    // VSYNC処理が許可されていないときは処理を抜ける
    if (!vsync_exec) {
        return;
    }

    #ifndef __INTELLISENSE__
    __asm
    EXX
    __endasm;
    #endif

    // パターンネームテーブル更新
    // アセンブラのブロック転送で書いた方が速い
    vwrite(offScreen, VRAM_PTN_NAME_TBL, VRAM_PTN_NAME_SIZE);

    #ifndef __INTELLISENSE__
    __asm
    EXX
    __endasm;
    #endif

    // VSYNC処理不許可にして終了
    vsync_exec = false;
}

/*+
 * ゲーム初期化
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_init()__z88dk_fastcall
{
    // 画面初期化
    set_color(15, 1, 1);
    set_mangled_mode();
    msx_set_sprite_mode(sprite_large);

    // パターンジェネレータテーブル設定
    vwrite(BANK_PATTERN_0, VRAM_PTN_GENR_TBL1, VRAM_PTN_GENR_SIZE);
    vwrite(BANK_PATTERN_0, VRAM_PTN_GENR_TBL2, VRAM_PTN_GENR_SIZE);
    vwrite(BANK_PATTERN_0, VRAM_PTN_GENR_TBL3, VRAM_PTN_GENR_SIZE);

    // カラーテーブル設定
    vwrite(BANK_COLOR_0, VRAM_COLOR_TBL1, VRAM_COLOR_SIZE);
    vwrite(BANK_COLOR_0, VRAM_COLOR_TBL2, VRAM_COLOR_SIZE);
    vwrite(BANK_COLOR_0, VRAM_COLOR_TBL3, VRAM_COLOR_SIZE);

    // サウンドドライバ初期化
//    sounddrv_init();

    // H.TIMIフック設定
    #ifndef __INTELLISENSE__
    __asm
    DI
    __endasm;
    #endif
    uint8_t *h_timi = (uint8_t *)MSX_H_TIMI;
    uint16_t hook_addr = (uint16_t)&game_draw;
    h_timi[0] = 0xc3; // JP
    h_timi[1] = (uint8_t)(hook_addr & 0xff);
    h_timi[2] = (uint8_t)((hook_addr & 0xff00) >> 8);
    #ifndef __INTELLISENSE__
    __asm
    EI
    __endasm;
    #endif

    vsync_exec = false;

    // 画面の基本部分を描画
    offscr_putTextRect(10, 8, 12, 6, mainScreenData);
    offscr_putTextRect(10,19, 12, 2, controlGuideData);

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
void game_start()__z88dk_fastcall
{
    if (game_tick == 1) {
        lcd_clear();
        lcd_update();
    }
    change_game_state(STATE_GAME);
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
void game_main_shot()__z88dk_fastcall
{
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
void game_main_player()__z88dk_fastcall
{
    buff_stick = get_stick(0);

    // 左入力で数字変更
    if (buff_stick == STICK_NONE) {
        input_flag = false;
    }
    else if (buff_stick == STICK_LEFT && !input_flag) {
        input_flag = true;
        player_number++;
        if (player_number > 10) {
            player_number = 1;
        }
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
void game_main_enemy()__z88dk_fastcall
{
    // 仮実装：LCDデータをランダムで更新
    enemy_line[get_rnd() % 6] = get_rnd() % 10 + 1;
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
void game_main_updateLCDData()__z88dk_fastcall
{
    lcdData[1] = player_number - 1;     // プレイヤー
    lcdData[2] = player_left + 11;      // 残機数
    for (int i = 0; i < 6; i++) {       // 敵
        if (enemy_line[i] == 0) {
            lcdData[i + 3] = LCD_SPACE;
        } else {
            lcdData[i + 3] = enemy_line[i] - 1;
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
void game_main()__z88dk_fastcall
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
void game_clear()__z88dk_fastcall
{
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
void game_miss()__z88dk_fastcall
{
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
void game_over()__z88dk_fastcall
{

    if (game_tick == 1) {
        // メッセージ表示
        offscr_putTextLn(11,  6, "GAME  OVER");
        offscr_putTextLn(11, 15, "PUSH SPACE");
        // LCD表示
        lcd_clear();
        char v[10];
        sprintf(v, "%3d-%6d", game_round, game_score);
        lcd_setText(v);
        lcd_update();
    }

    buff_trigger = get_trigger(0);

    if (buff_trigger != 0) {
        // メッセージ消去
        offscr_putTextLn(11,  6, "          ");
        offscr_putTextLn(11, 15, "          ");
        // 全体初期設定
        game_round = 1;
        game_score = 0;
        player_left = 3;
        // ゲームスタート処理に遷移
        change_game_state(STATE_START);
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
void game_update()__z88dk_fastcall
{
    // ゲーム経過時間更新
    game_tick++;

    switch (game_state) {
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

    // vsync処理を許可し、終了を待つ
    vsync_exec = true;
    while (vsync_exec) {
        // NOP
    }
}
