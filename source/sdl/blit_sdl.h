// extensions for SDL

#ifndef BLIT_SDL_H
#define BLIT_SDL_H

#include "compat_sdl.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void blit_x2_func(al_bitmap *src, al_bitmap *dest, int s_x, int s_y, int d_x, int d_y, int w, int h);
extern SDL_Rect area_overlay;
extern int integer_scaling;

extern blit_x2_func *my_blit_x2_y1,*my_blit_x2_y2;
extern SDL_Surface *sdl_game_bitmap;
void get_overlay_area(int *x, int *y, int *w, int *h);

#ifdef __cplusplus
}
#endif

#endif

