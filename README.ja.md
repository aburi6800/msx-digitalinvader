[ [Engligh](README.md) | [日本語](README.ja.md) ]

---
# デジタルインベーダー for MSX

<img src="image/01.png">

<br>

## WebMSXでプレイする

- 以下のURLにアクセスしてください。

    - C言語バージョン
    https://webmsx.org/?MACHINE=MSX1&CARTRIDGE1_URL=https://github.com/aburi6800/msx-digitalinvader/raw/main/dist/dgtl-inv.rom

    - BASICバージョン
    https://webmsx.org/?MACHINE=MSXTRJ&DISKA_URL=https://github.com/aburi6800/msx-digitalinvader/raw/main/DGTL-INV.dsk

<br>

## プレイ方法

### 操作方法

- カーソルキー左／ジョイパッド左 :
    - 照準
- カーソルキー右／ジョイパッド右 :
    - ビーム
- スペースキー／トリガボタン :
    - ゲームスタート

<br>

### ルール

- SPACEキーを押してゲームを開始します。
- AIMキーを押して、数字を設定します。キーを押すたびに数字が「0」から「9」まで増えていきます。次に「n」となり、もう一度キーを押すと「0」に戻ります。
- FIREキーを押すと、自分と同じ数字のデジタルインベーダーを撃墜します。同じ数字のデジタルインベーダーがいたら、もう一度キーを押してください。
- 1ラウンドに攻撃してくるデジタルインベーダーは16体。ビーム砲は30回使用可能です。
- 消した数字の合計が10の倍数になると、UFO("n")が出現します。撃墜すると300ptsのボーナスです。
- デジタルインベーダーに侵略されると、プレイヤーはライフを1つ失います。ライフがゼロになるとゲームオーバーです。

<br>

## ビルド方法

<br>

## ライセンス

MIT License

<br>

## Thanks

- [Z88DK - The Development Kit for Z80 Computers](https://github.com/z88dk/z88dk)
- [C-BIOS](http://cbios.sourceforge.net/)
- [openMSX](https://openmsx.org/)
- [nMSXtiles](https://github.com/pipagerardo/nMSXtiles)
- [WebMSX](https://github.com/ppeccin/WebMSX)
- [MSXPen](https://msxpen.com/)
