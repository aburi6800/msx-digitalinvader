// License:MIT License
// copyright-holders:Hitoshi Iwai

#ifndef GAME_H
#define GAME_H

#include <stdint.h>


/*
 * ゲーム初期化
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_init();

/*
 * ゲーム処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_update();

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
void game_draw();

/**
 * オフスクリーンクリア
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void buff_clear();

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
void buff_wrttext(uint8_t x, uint8_t y, char* text);

#endif
