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
 * PSGレジスタ初期化
 *
 * args:
 * - reg            uint8_t     レジスタ番号
 * - dat            uint8_t     データ
 *
 * return:
 * - void
 */
void psg_init();

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
void psg_write(uint8_t reg, uint8_t dat);

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
void offscr_clear();

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
void lcd_clear();

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
void lcd_setText(char* text, uint8_t pos);

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
void lcd_setNumber(uint16_t val, uint8_t pos, uint8_t len);

/*
 * LCDデータをオフスクリーンへ書き込む
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void lcd_update();

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
 * ゲーム開始処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_start();

/*
 * ゲームメイン／ショット処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_main_player_shot();

/*
 * ゲームメイン／プレイヤー処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_main_player();

/*
 * ゲームメイン／エネミー処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_main_enemy();

/*
 * ゲームメイン／LCDデータ更新処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_main_updateLCDData();

/*
 * ゲームクリア処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_clear();

/*
 * ゲームミス処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_miss();

/*
 * ゲームオーバー処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_over();

/*
 * ゲームメイン処理
 *
 * args:
 * - none
 *
 * return:
 * - void
 */
void game_main();

#endif
