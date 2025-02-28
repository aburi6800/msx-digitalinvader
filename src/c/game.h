// License:MIT License
// copyright-holders:Hitoshi Iwai

#ifndef GAME_H
#define GAME_H

#include <stdint.h>


// ゲーム状態
typedef enum {
    STATE_START,
    STATE_GAME,
    STATE_CLEAR,
    STATE_MISS,
    STATE_OVER
} game_state_t;


/*
 * ゲーム状態変更
 *
 * args:
 * - game_state_t    state       ゲーム状態
 *
 * return:
 * - void
 */
void change_game_state(game_state_t s);

/*
 * オフスクリーンクリア
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void offscr_clear()__z88dk_fastcall;

/*
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
void offscr_putTextRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, char* text);

/*
 * LCDデータクリア
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void lcd_clear()__z88dk_fastcall;

/*
 * LCDに文字列データ設定
 *
 * args:
 * - text           char*       表示テキストのアドレス、または配列
 *
 * return:
 * - void
 */
void lcd_setText(char* text)__z88dk_fastcall;

/*
 * LCDデータをオフスクリーンへ書き込む
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void lcd_update()__z88dk_fastcall;

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

/*
 * ゲーム初期化
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_init()__z88dk_fastcall;

/*
 * ゲーム処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_update()__z88dk_fastcall;

/*
 * ゲーム開始処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_start()__z88dk_fastcall;

/*
 * ゲームメイン／ショット処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_main_shot()__z88dk_fastcall;

/*
 * ゲームメイン／プレイヤー処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_main_player()__z88dk_fastcall;

/*
 * ゲームメイン／エネミー処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_main_enemy()__z88dk_fastcall;

/*
 * ゲームメイン／LCDデータ更新処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_main_updateLCDData()__z88dk_fastcall;

/*
 * ゲームクリア処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_clear()__z88dk_fastcall;

/*
 * ゲームミス処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_miss()__z88dk_fastcall;

/*
 * ゲームオーバー処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_over()__z88dk_fastcall;

/*
 * ゲームメイン処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_main()__z88dk_fastcall;

#endif
