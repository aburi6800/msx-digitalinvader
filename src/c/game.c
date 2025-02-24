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
uint8_t OFFSCREEN[BUFF_SIZE];


/*
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

    // テスト：オフバッファにデータを設定
    buff_wrttext(6, 6, "THIS IS TEST PROGRAM");

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
    vwrite(OFFSCREEN, VRAM_PTN_NAME_TBL, VRAM_PTN_NAME_SIZE);

}

/**
 * オフスクリーンクリア
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void buff_clear()
{
    for (uint16_t i = 0; i < BUFF_SIZE; i++) {
        OFFSCREEN[i] = CHR_SPACE;
    }
}

/**
 * オフスクリーン書き込み
 * - 引数x,yの位置にテキストを書き込む。
 * - 画面端のはみ出し処理はしていないので注意。
 *
 * args:
 * - x              uint8_t     更新先のX座標
 * - y              uint8_t     更新先のY座標
 * - text           char*       表示テキストのアドレス
 *
 * return:
 * - void
 */
void buff_wrttext(uint8_t x, uint8_t y, char* text)
{
    for (uint8_t i = 0; i < strlen(text); i++) {
        OFFSCREEN[y * BUFF_WIDTH + x] = text[i];
        x++;
    }
}
