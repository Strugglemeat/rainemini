modification of raine emulator to use no asm and be portable

all credit goes to https://github.com/zelurker/raine

when removing neogeo CD I ended up removing neogeo completely
it should be doable to add it back, but I'm not going to do that right now

ultimately my aim is to set up this codebase to be portable to put on ESP32 and/or STM32H7

I removed blending, emudx, samples, png, gzip, leds. eventually I might get rid of all the GUI stuff, since it's a huge part of the codebase.

most of the code is C but there's a fair number of C++ files in the SDL and SDL2 directories

I've also taken out the games which use mouse/lightgun/trackball, as well as a lot of bootlegs and clones.

most taito F3 games work but sadly cleopatra fortune does not.
