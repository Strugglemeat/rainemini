#ifndef MENUITEM_H
#define MENUITEM_H

#include "deftypes.h"
#include <SDL.h>

#ifdef __cplusplus
extern "C" {
#endif
// See the comments on usage in menu.cpp

#define clear_surface(s) SDL_FillRect(s,NULL,0)

// Margin from the left border of menus for the start of text
#define HMARGIN 10

// converts a gfx to SDL_Color format :
#if SDL == 2
#define gfx_to_sdlcolor(format,c) SDL_MapRGBA(format,(c)>>0,((c)>>8)&0xff,((c>>16)&0xff),(c>>24)&0xff)
// SDL_gfx does its own mapping of colors and requires to be passed colors
// in this format... format is abgr confirmed (intel)
#define mymakecol(r,g,b) (((r)<<0)|((g)<<8)|((b)<<16)|(255<<24))
#define makecol_alpha(r,g,b,a) (((r&0xff)<<0)|((g&0xff)<<8)|((b&0xff)<<16)|(a&0xff)<<24)
// rgb on 24 bits to sdl_gfx format, which is also used for TStatic
#define rgb2gfx(c) (c>>16)|((c&0xff)<<16)|(c&0xff00)|(255<<24)
#else
#define gfx_to_sdlcolor(surf,c) SDL_MapRGBA(surf->format,(c)>>24,((c)>>16)&0xff,((c>>8)&0xff),(c)&0xff)
// SDL_gfx does its own mapping of colors and requires to be passed colors
// in this format...
#define mymakecol(r,g,b) (((r)<<24)|((g)<<16)|((b)<<8)|255)
#define makecol_alpha(r,g,b,a) (((r&0xff)<<24)|((g&0xff)<<16)|((b&0xff)<<8)|(a&0xff))
#endif

#define NB_VALUES 75

typedef struct {
                char *label;
                int (*menu_func)(int);
                int     *value_int;
                int     values_list_size;
                int values_list[NB_VALUES];
                char* values_list_label[NB_VALUES];
} menu_item_t;

// default colors
extern int fg_color, bg_color,fgframe_color,bgframe_color,cslider_border,
  cslider_bar,cslider_lift,bg_dialog_bar,keep_vga,bg_dialog_bar_gfx,
  gui_level;

#if SDL == 1
extern int emulate_mouse_cursor;
#endif

void sort_menu(menu_item_t *menu);
int add_menu_options(menu_item_t *menu);

void disp_cursor(SDL_Surface *s,int x,int y, int w, int h);

/* Extensions to menu_items :
 * normally a menu_item is a string, with some other string options if
 * value_int != NULL.
 * Now I want some special widgets like progress bars. So if value_int != NULL
 * then if value_list_size > 0, it's a normal list of options
 * and if values_list_size < 0, it's an extension */

#define ITEM_NORMAL (0)
/* Progress bar : value_int must point to an integer with a value
 * from 0 to 100 */
#define ITEM_PROGRESS_BAR (-1)

/* Slider : it's an horizontal lift
 * parameters in values_list :
 * 0 : max value (min is always 0 for now)
 * 1 : step (amount of 1 page)
 * 2 : width in pixels
 * 3 : color of border
 * 4 : color of bar
 * 5 : color of thumb */
#define ITEM_SLIDER (-2)

/* TEdit
 * parameters :
 * values_list_label[0] -> pointer to the resulting string
 * values_list[0] : maxlen
 * values_list[1] : use history (0/1). If using history the widget captures
 * the up and down keys.
 * values_list[2] : max width in pixels to display */
#define ITEM_EDIT (-3)

/* TBitmap (see tbitmap.h) */
#define ITEM_Tal_bitmap (-4)

/* TFloatEdit
 * parameters :
 * values_list_label[0] : not used (the field for tedit, useless here).
 * values_list_label[1] : pointer to the resulting float (overwrite the type)
 * values_list_label[2] and [3] : min max values (in string format, put the same value to skip test)
 * values_list[0] = maxlen
 * values_list[2] : max width in pixels to display */
#define ITEM_FLOATEDIT (-5)

/* THexEdit same thing as TFloatEdit
 * parameters :
 * values_list_label[0] : not used (the field for tedit, useless here).
 * values_list_label[1] : pointer to the resulting hex (UINT32)
 * values_list_label[2] and [3] : min max values (in string format, put the same value to skip test)
 * values_list[0] = maxlen
 * values_list[2] : max width in pixels to display */
#define ITEM_HEXEDIT (-6)

/* TIntEdit same thing as THexEdit but in decimal
 * parameters :
 * value_int is used for the result
 * values_list_label[0] : unused (the same), but must be initialized ("")
 * values_list[0] maxlen
 * values_list[2] max width in pixels
 * values_list[3] & 4 : min and max, same value to skip test */
#define ITEM_INTEDIT (-7)

#ifdef __cplusplus
}
#endif
#endif

