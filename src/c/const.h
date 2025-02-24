// License:MIT License
// copyright-holders:Hitoshi Iwai

#ifndef CONST_H
#define CONST_H

// VRAM操作用定数
#define VRAM_PTN_GENR_TBL1  0x0000
#define VRAM_PTN_GENR_TBL2  0x0800
#define VRAM_PTN_GENR_TBL3  0x1000
#define VRAM_PTN_GENR_SIZE  0x0800

#define VRAM_COLOR_TBL1     0x2000
#define VRAM_COLOR_TBL2     0x2800
#define VRAM_COLOR_TBL3     0x3000
#define VRAM_COLOR_SIZE     0x0800

#define VRAM_PTN_NAME_TBL   0x1800
#define VRAM_PTN_NAME_SIZE  768

#define VRAM_SPR_PTN_TBL    0x3800

#define VRAM_SPR_ATTR_TBL   0x1B00
#define VRAM_SPR_ATTR_SIZE  128

#define VRAM_WIDTH          32
#define VRAM_HEIGHT         24

// H.TIMI割り込みフックアドレス
#define MSX_H_TIMI          0xfd9f

// キャラクタコード定数
#define CHR_SPACE           0x20

// マクロ（インライン展開される）
#define VPOS(x, y)  (VRAM_START + VRAM_WIDTH * y + x)
#define POS(x, y)   (VRAM_WIDTH * y + x)

// 仮想画面バッファの定義
#define BUFF_WIDTH          32
#define BUFF_HEIGHT         24
#define BUFF_SIZE           BUFF_WIDTH * BUFF_HEIGHT

#endif
