[ [Engligh](README.md) | [日本語](README.ja.md) ]

---
# DIGIAL INVADER for MSX

<img src="image/01.png">

<br>

## Play in WebMSX

- Please access the following URL.

    - C Language version
    https://webmsx.org/?MACHINE=MSX1&CARTRIDGE1_URL=https://github.com/aburi6800/msx-digitalinvader/raw/main/dist/dgtl-inv.rom

    - MSX-BASIC verison
    https://webmsx.org/?MACHINE=MSXTRJ&DISKA_URL=https://github.com/aburi6800/msx-digitalinvader/raw/main/DGTL-INV.dsk

<br>

## How to play

### Control

- Cursor keys left/Joypad left
    - Aiming
- Cursor key right / Joypad right
    - Beam
- Spacebar / Trigger button
    - Game Start
<br>

### Rules

- Press SPACE key to start the game.
- Press the AIM key to set the number. Each time the key is pressed, the number increases from "0" to "9". Next comes "n" and pressing the key again returns the number to "0".
- When you press the FIRE key, a digital invader with the same number as you is shot down. If there is a digital invader with the same number, press the key again.
- There are 16 digital invaders attacking in one round. The beam cannon can be used 30 times.
- When the total number of erased numbers is a multiple of 10, a UFO("n") appears.If you shoot it down, you will get a bonus of 300pts.
- When invaded by digital invaders, the player loses one life. The game is over when the number of lives reaches zero.

<br>

## Build

<br>

## License

MIT License

<br>

## Thanks

- [Z88DK - The Development Kit for Z80 Computers](https://github.com/z88dk/z88dk)
- [C-BIOS](http://cbios.sourceforge.net/)
- [openMSX](https://openmsx.org/)
- [nMSXtiles](https://github.com/pipagerardo/nMSXtiles)
- [WebMSX](https://github.com/ppeccin/WebMSX)
- [MSXPen](https://msxpen.com/)
