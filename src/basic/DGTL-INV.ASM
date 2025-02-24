START:
LDIRVM:     EQU 0x005C                  ; BIOS LDIRVM
	ORG 0xC000

	; パターンジェネレータテーブル・カラーテーブル設定
	; BASICプログラムでスクリーンモード等設定済の前提で呼び出すこと
	CALL SET_PTN_TBL
	CALL SET_COL_TBL
;	CALL SET_SPRPTN_TBL
	RET

SET_PTN_TBL:
	; PATTERN GENERATE TABLE
	; PAGE 0
	LD DE,0x0000
	CALL SET_PTN_TBL_1
	; PAGE 1
	LD DE,0x0800
	CALL SET_PTN_TBL_1
	; PAGE 2
	LD DE,0x1000

SET_PTN_TBL_1:
	LD HL,BANK_PATTERN_0
	LD BC,0x0800
	CALL LDIRVM
	RET

SET_COL_TBL:
	; COLOR TABLE
	; PAGE 0
	LD DE,0x2000
	CALL SET_COL_TBL_1
	; PAGE 1
	LD DE,0x2800
	CALL SET_COL_TBL_1
	; PAGE 2
	LD DE,0x3000

SET_COL_TBL_1:
	LD HL,BANK_COLOR_0
	LD BC,0x0800
	CALL LDIRVM
	RET

;SET_SPRPTN_TBL:
;	LD DE,0x3800
;	LD HL,SPRITE_PTN
;    ; BCレジスタにはパターン数*16の値を設定する
;	LD BC,576
;	CALL LDIRVM
;	RET

    ; 以下にnMSXtilesのExport ASM Dataで出力したasmデータのBANK_PATTERN_0を貼り付ける
BANK_PATTERN_0:
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 124, 68, 68, 254, 226, 226, 226, 0
	DB 252, 196, 196, 254, 226, 226, 254, 0
	DB 254, 130, 128, 224, 224, 226, 254, 0
	DB 252, 130, 130, 226, 226, 226, 252, 0
	DB 254, 128, 128, 254, 224, 224, 254, 0
	DB 254, 128, 128, 254, 224, 224, 224, 0
	DB 254, 130, 128, 238, 226, 226, 254, 0
	DB 130, 130, 130, 254, 226, 226, 226, 0
	DB 32, 32, 32, 56, 56, 56, 56, 0
	DB 12, 12, 12, 14, 142, 142, 124, 0
	DB 132, 132, 132, 252, 226, 226, 226, 0
	DB 128, 128, 128, 224, 224, 224, 254, 0
	DB 246, 138, 138, 234, 234, 234, 234, 0
	DB 252, 130, 130, 226, 226, 226, 226, 0
	DB 254, 142, 142, 142, 130, 130, 254, 0
	DB 252, 132, 132, 252, 224, 224, 224, 0
	DB 254, 134, 134, 134, 134, 156, 250, 0
	DB 252, 132, 132, 254, 226, 226, 226, 0
	DB 254, 194, 192, 254, 14, 142, 254, 0
	DB 254, 16, 16, 28, 28, 28, 28, 0
	DB 130, 130, 130, 226, 226, 226, 254, 0
	DB 226, 226, 226, 226, 230, 36, 60, 0
	DB 138, 138, 138, 234, 234, 234, 254, 0
	DB 194, 194, 194, 124, 226, 226, 226, 0
	DB 130, 130, 130, 124, 56, 56, 56, 0
	DB 254, 134, 24, 96, 224, 226, 254, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 28, 34, 34, 34, 34
	DB 0, 0, 0, 2, 2, 2, 2, 2
	DB 0, 0, 0, 28, 2, 2, 2, 2
	DB 0, 0, 0, 0, 34, 34, 34, 34
	DB 0, 0, 0, 30, 32, 32, 32, 32
	DB 0, 0, 0, 28, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 68, 68, 68, 68, 56, 0, 0
	DB 0, 4, 4, 4, 4, 0, 0, 0
	DB 60, 64, 64, 64, 64, 56, 0, 0
	DB 60, 4, 4, 4, 4, 120, 0, 0
	DB 60, 4, 4, 4, 4, 0, 0, 0
	DB 60, 68, 68, 68, 68, 56, 0, 0
	DB 60, 68, 68, 68, 68, 0, 0, 0
	DB 60, 0, 0, 0, 0, 56, 0, 0
	DB 0, 0, 0, 0, 0, 56, 0, 0
	DB 60, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 255, 255, 255, 255, 252, 248, 240, 240
	DB 255, 255, 255, 255, 63, 31, 15, 15
	DB 240, 240, 248, 252, 255, 255, 255, 255
	DB 15, 15, 31, 63, 255, 255, 255, 255
	DB 0, 0, 0, 0, 255, 255, 255, 255
	DB 255, 255, 255, 255, 0, 0, 0, 0
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 15, 15, 15, 15, 15, 15, 15, 15
	DB 255, 255, 205, 186, 170, 168, 202, 255
	DB 255, 255, 168, 139, 136, 171, 168, 255
	DB 255, 255, 205, 186, 186, 184, 202, 255
	DB 255, 255, 187, 186, 186, 186, 139, 255
	DB 255, 255, 42, 234, 234, 234, 34, 255
	DB 255, 255, 246, 235, 235, 227, 43, 255
	DB 255, 255, 54, 106, 106, 106, 118, 255
	DB 255, 255, 63, 191, 127, 191, 191, 255
	DB 255, 255, 255, 255, 255, 255, 255, 255
	DB 0, 63, 127, 126, 124, 120, 112, 96
	DB 0, 252, 254, 254, 254, 254, 14, 14
	DB 96, 112, 120, 124, 126, 127, 63, 0
	DB 14, 14, 254, 254, 254, 254, 252, 0
	DB 0, 63, 127, 127, 127, 127, 112, 112
	DB 0, 252, 254, 126, 62, 30, 14, 6
	DB 112, 112, 127, 127, 127, 127, 63, 0
	DB 6, 14, 30, 62, 126, 254, 252, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0
	DB 0, 0, 0, 0, 0, 0, 0, 0

    ; 以下にnMSXtilesのExport ASM Dataで出力したasmデータのBANK_COLOR_0を貼り付ける
BANK_COLOR_0:
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 14, 30, 30, 30, 30, 30, 30, 30
	DB 14, 30, 30, 30, 30, 30, 30, 30
	DB 14, 30, 30, 30, 30, 30, 30, 30
	DB 14, 30, 30, 30, 30, 30, 30, 30
	DB 14, 30, 30, 30, 30, 30, 30, 30
	DB 14, 30, 30, 30, 30, 30, 30, 30
	DB 14, 30, 30, 30, 30, 30, 30, 30
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 14, 30, 14, 30, 30, 30, 30, 30
	DB 14, 30, 14, 30, 30, 30, 30, 30
	DB 14, 30, 14, 30, 30, 30, 30, 30
	DB 14, 30, 14, 30, 30, 30, 30, 30
	DB 14, 30, 14, 30, 30, 30, 30, 30
	DB 14, 30, 14, 30, 30, 30, 30, 30
	DB 14, 30, 14, 30, 30, 30, 30, 30
	DB 14, 30, 14, 30, 30, 30, 30, 30
	DB 14, 30, 14, 30, 30, 30, 30, 30
	DB 14, 30, 14, 30, 30, 30, 30, 30
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 240, 240, 240, 240, 240, 240, 240, 240
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16
	DB 16, 16, 16, 16, 16, 16, 16, 16

END START
