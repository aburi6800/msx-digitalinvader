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

// 仮想画面
uint8_t offScreen[BUFF_SIZE];

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
//             ptn   SP,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   n,   -,  一,  二,  三
char lcdPtn0[16] = {'`', 'a', 'b', 'c', 'c', 'd', 'e', 'e', 'c', 'a', 'a', '`', '`', '`', '`', 'f'};
char lcdPtn1[16] = {'`', 'p', 'q', 'r', 's', 't', 's', 'u', 'q', 'u', 's', 'v', 'y', 'x', 'w', 'w'};

// LCDデータ
int lcdData[10] = {  32, 32, 32, 32, 32, 32, 32, 32, 32, 32};

/*+
 * ゲーム初期化
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_init() {
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

    // テスト：オフバッファにデータを設定
    offscr_putTextLn(6, 6, "THIS IS TEST PROGRAM");

    // テスト：オフバッファに矩形データを設定
    offscr_putTextRect(10, 8, 12, 6, mainScreenData);
    offscr_putTextRect(10,19, 12, 2, controlGuideData);
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
void game_update() {
    lcdData[get_rnd() % 10] = get_rnd() % 10;

    lcd_update();
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
void game_draw() {
    // パターンネームテーブル更新
    vwrite(offScreen, VRAM_PTN_NAME_TBL, VRAM_PTN_NAME_SIZE);
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
void lcd_clear() {
    for (uint8_t i = 0; i < 10; i++) {
        lcdData[i] = 32;
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
void lcd_update() {
    int v;
    uint16_t offscr_p0 = 10 * BUFF_WIDTH + 11;
    uint16_t offscr_p1 = 11 * BUFF_WIDTH + 11;

    for (int i = 0; i < 10; i++) {
        v = lcdData[i];

        if (v == 32) {
            // LCDデータ 32 は 空白として0番目のパターンを表示
            v = 0;
        } else if (v == 45) {
            // LCDデータ 45 は '-'として12番目のパターンを表示
            v = 12;
        } else if (v > 64 && v < 68) {
            // LCDデータ 65～67 は残機数のキャラクターなので、13～16番目のパターンを表示
            v = v - 48;
        } else if (v > 47 && v < 58) {
            // LCDデータ 48～57 は数値のキャラクターなので、 1～10番目のパターンを表示
            v = v - 47;
        } else {
            // LCDデータ 0～10 は数値 or 'n' として1～11番目のパターンを表示
            v = v + 1;
        }

        offScreen[offscr_p0++] = lcdPtn0[v];
        offScreen[offscr_p1++] = lcdPtn1[v];
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
    for (uint16_t i = 0; i < BUFF_SIZE; i++) {
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
        offScreen[y * BUFF_WIDTH + x] = text[i];
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
    uint16_t offscreen_p = y * BUFF_WIDTH + x;
    uint16_t p = 0;

    for (uint8_t j = 0; j < h; j++) {
        for (uint8_t i = 0; i < w; i++) {
            offScreen[offscreen_p++] = text[p++];
        }
        offscreen_p = offscreen_p + BUFF_WIDTH - w;
    }
}
