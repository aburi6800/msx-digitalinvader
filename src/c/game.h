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
void offscr_clear();

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
void offscr_putTextLn(uint8_t x, uint8_t y, char* text);

/**
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
void offscr_putTextRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, char* text);

#endif
