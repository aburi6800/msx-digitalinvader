/*
 * DIGITAL INVADER for MSX
 *
 * Programed by ABURI6800 (Hitoshi Iwai)
 *
 *
 * MIT License
 */

 // Compiler     : zcc (z88dk)
 // Include path : {$Z88DK_HOME}/include/* , {$Z88DK_HOME}/include/**/*

 #include "game.h"

 void main() {
    // Initialize
    game_init();

    // Main Loop
    while (1) {
        // Update
        game_update();
    }
}
