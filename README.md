modification of raine emulator to use no asm and be portable

all credit goes to https://github.com/zelurker/raine

when removing neogeo CD I ended up removing neogeo completely
it should be doable to add it back, but I'm not going to do that right now

ultimately my aim is to set up this codebase to be portable to put on ESP32 and/or STM32H7

I removed blending, emudx, samples, png, gzip, leds.

I've also taken out the games which use mouse/lightgun/trackball, as well as a lot of bootlegs and clones.

most taito F3 games work but sadly cleopatra fortune does not.

most of the code is C but there's a fair number of C++ files in the SDL and SDL2 directories:

./source/sdl/gui.cpp

./source/sdl/gui/menu.cpp

./source/sdl/gui/tedit.cpp

./source/sdl/gui/tbitmap.cpp

./source/sdl/gui/tlift.cpp

./source/sdl/gui/tslider.cpp

./source/sdl/gui/widget.cpp

./source/sdl/gui/tfont.cpp

./source/sdl/gui/tconsole.cpp

./source/sdl/dialogs/dirs.cpp

./source/sdl/dialogs/colors.cpp

./source/sdl/dialogs/sound_options.cpp

./source/sdl/dialogs/video_info.cpp

./source/sdl/dialogs/controls.cpp

./source/sdl/dialogs/about.cpp

./source/sdl/dialogs/game_options.cpp

./source/sdl/dialogs/messagebox.cpp

./source/sdl/dialogs/romdirs.cpp

./source/sdl/dialogs/fsel.cpp

./source/sdl/dialogs/game_selection.cpp

./source/sdl/dialogs/translator.cpp

./source/sdl/dialogs/sprite_viewer.cpp

./source/sdl/dialogs/video_options.cpp

./source/sdl/dialogs/dlg_dsw.cpp

./source/sdl/dialogs/gui_options.cpp

./source/sdl2/gui/menu.cpp

./source/sdl2/gui/tedit.cpp
