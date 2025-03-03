[ [Engligh](README.md) | [日本語](README.ja.md) ]

---
# デジタルインベーダー for MSX

<img src="image/01.png">

<br>

## 概要

カシオ社「SL-880」に搭載された「デジタルインベーダー」をMSXで再現したものです。
細かいところに違いがあると思いますが、基本的なルールは同じになっています。

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
- デジタルインベーダーに侵略されると、プレイヤーはライフを1つ失います。
- ライフがゼロになるか、1ラウンド中にビーム砲を30発使い切るとゲームオーバーです。

<br>

## Cソースからのビルド方法

- `z88dk`と`cmake`がインストールされている前提となります。
- `z88dk`については、以下リンク先を参照ください。

    [z88dk installation](https://github.com/z88dk/z88dk/wiki/installation)

- `cmake`がインストールされていない場合は、以下コマンドでインストールします。
    ```
    sudo apt install cmake
    ```

<br>

- 初回のみ、cloneしたディレクトリに移動し、以下コマンドを実行します。
    ```
    mkdir build
    (cd build && cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/z88dk.cmake ..)
    ```

<br>

- 次に、以下コマンドを実行すると、`dist`ディレクトリに`degi-inv.rom`ファイルが作成されます。
    ```
    cd build
    make clean && make
    ```

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
