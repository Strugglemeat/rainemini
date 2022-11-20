#define NOGDI // define this before including windows.h to avoid al_bitmap !
#ifdef ANDROID
#include <GLES/gl.h>
#else
#define GL_GLEXT_LEGACY // to try not to include glext.h which redefines the GL_GLEXT_VERSION which shouldn't have gone to SDL_opengl.h !
#include <SDL_opengl.h>
#endif
#undef WINAPI
#include <time.h>
#include "raine.h"
#include "blit.h"
#include "blit_sdl.h"
#include "palette.h"
#include "compat.h"
#include "video/res.h"
#ifdef RAINE_UNIX
#include <unistd.h>
#endif
#include "gui/menu.h"
#include "winpos.h"
#include "opengl.h"
#include "display_sdl.h"
#include "profile.h"

togl_options ogl;
float max_fps;

int disp_screen_x;
int disp_screen_y;
int desktop_w,desktop_h;
int hack_fs;

void display_read_config() {
   hack_fs = raine_get_config_int( "Display", "hack_fs", 0); // hack_fs : don't call SDL_SetWindowFullscreen
   display_cfg.video_mode = raine_get_config_int( "Display", "video_mode", 0); // default = opengl, the most tested
   if (display_cfg.video_mode != 0 && display_cfg.video_mode != 3)
       display_cfg.video_mode = 3;
   int x = 0,y = 0;
   SDL_GetWindowPosition(win,&x,&y);
   display_cfg.posx = raine_get_config_int("Display", "posx", x);
   display_cfg.posy = raine_get_config_int("Display", "posy", y);
   if (display_cfg.posx != x || display_cfg.posy != y) {
       SDL_SetWindowPosition(win,display_cfg.posx,display_cfg.posy);
   }

   display_cfg.screen_x = raine_get_config_int( "Display", "screen_x", display_cfg.screen_x);
   display_cfg.screen_y = raine_get_config_int( "Display", "screen_y", display_cfg.screen_y);
   display_cfg.winx = raine_get_config_int( "Display", "winx", 640);
   display_cfg.winy = raine_get_config_int( "Display", "winy", 480);
   char *s = raine_get_config_string("Display", "max_fps", "60");
   if (*s)
       sscanf(s,"%f",&max_fps);

   display_cfg.user_rotate = raine_get_config_int( "Display", "rotate", 0);
   display_cfg.user_flip = raine_get_config_int( "Display", "flip", 0);
   display_cfg.fix_aspect_ratio = raine_get_config_int("display", "fix_aspect_ratio", 1);
   display_cfg.fullscreen = raine_get_config_int("display", "fullscreen", 0);

   ogl.dbuf = raine_get_config_int("display","ogl_dbuf",2);
   integer_scaling = raine_get_config_int("display","integer_scaling",0);
   ogl.render = raine_get_config_int("display","ogl_render",1); // 0 = drawpixels, 1 = texture
   ogl.overlay = raine_get_config_int("display","ogl_overlay",1); // overlay interface
   ogl.save = raine_get_config_int("display","ogl_save",1);
   ogl.filter = raine_get_config_int("display","ogl_filter",GL_NEAREST);
   strcpy(ogl.shader, raine_get_config_string("display","ogl_shader","None"));

   display_cfg.keep_ratio = raine_get_config_int("display","keep_ratio",1);

}

void set_opengl_filter(int filter) {
    if (filter == 1)
	ogl.filter = GL_LINEAR;
    else
	ogl.filter = GL_NEAREST; // default
}

void display_write_config() {

   raine_set_config_int("Display", "hack_fs", hack_fs);
   raine_set_config_int("Display", "video_mode", display_cfg.video_mode);
   print_debug("display_write_config: screen_x %d screen_y %d\n",display_cfg.screen_x,display_cfg.screen_y);
   raine_set_config_int("Display", "screen_x", display_cfg.screen_x);
   raine_set_config_int("Display", "screen_y", display_cfg.screen_y);
   if (!display_cfg.fullscreen)
       SDL_GetWindowPosition(win,&display_cfg.posx,&display_cfg.posy);
   raine_set_config_int("Display", "posx", display_cfg.posx);
   raine_set_config_int("Display", "posy", display_cfg.posy);
   raine_set_config_int("Display", "winx", display_cfg.winx);
   raine_set_config_int("Display", "winy", display_cfg.winy);
   char s[20];
   snprintf(s,20,"%g",max_fps);
   raine_set_config_string("Display","max_fps",s);

   raine_set_config_int("Display", "rotate", display_cfg.user_rotate);
   raine_set_config_int("Display", "flip", display_cfg.user_flip);
   raine_set_config_int("display", "fix_aspect_ratio", display_cfg.fix_aspect_ratio);
   raine_set_config_int("display", "ogl_dbuf", ogl.dbuf);
   raine_set_config_int("display", "integer_scaling", integer_scaling);
   raine_set_config_int("display", "ogl_render", ogl.render);
   raine_set_config_int("display", "ogl_overlay", ogl.overlay);
   raine_set_config_int("display", "ogl_save", ogl.save);
   raine_set_config_int("display", "ogl_filter", ogl.filter);
   raine_set_config_string("display", "ogl_shader", ogl.shader);
   raine_set_config_int("display", "fullscreen", display_cfg.fullscreen);

   raine_set_config_int("Display", "keep_ratio", display_cfg.keep_ratio);

}

// Same thing, but saved as specific game parameters...
void load_screen_settings(char *section)
{
   if(raine_cfg.save_game_screen_settings){

       // DISPLAY

       display_cfg.frame_skip	= raine_get_config_int( section,        "frame_skip", 0);

       display_cfg.screen_x = raine_get_config_int(	section, "screen_x", display_cfg.screen_x);
       display_cfg.screen_y = raine_get_config_int(	section, "screen_y", display_cfg.screen_y);
       char *s = raine_get_config_string(section,"fps","");
       if (*s) {
	   sscanf(s,"%f",&fps);
       }
   }
}

void save_screen_settings(char *section)
{
   // remove all old settings

   raine_clear_config_section(section);

   if(raine_cfg.save_game_screen_settings){

       // DISPLAY

       raine_set_config_int(	section, "frame_skip", display_cfg.frame_skip);
       raine_set_config_int(	section, "screen_x", display_cfg.screen_x);
       raine_set_config_int(	section, "screen_y", display_cfg.screen_y);
       char buf[40];
       snprintf(buf,40,"%g",fps);
       raine_set_config_string(section,"fps",buf);


   }
}

void init_display() {
}

SDL_Texture *game_tex;

void ScreenChange(void)
{
    get_ogl_infos();
    int w,h;
    SDL_GetRendererOutputSize(rend,&w,&h);
    ReClipScreen();
    if (sdl_screen) {
	sdl_screen->w = w; sdl_screen->h = h;
    }
    opengl_reshape(w,h);
}

int resize(int call,int sx,int sy) {
  // Minimum size
  if (keep_vga && (sx < 640 || sy < 480)) {
      SDL_SetWindowSize(win,640,480);
      return 0;
  }
  int changed = 0;
  if (sx < 320) { sx = 320; changed = 1; }
  if (sy < 200) { sy = 200; changed = 1; }
  if (sx == display_cfg.screen_x && sy == display_cfg.screen_y)
      return 0;
  display_cfg.screen_x = sx;
  display_cfg.screen_y = sy;
  if (changed) SDL_SetWindowSize(win,sx,sy);

  if (call) {
      print_debug("calling ScreenChange from resize\n");
      ScreenChange();
  }
  return 1;
}

void set_default_video_mode() {
  display_cfg.screen_x = 640;
  display_cfg.screen_y = 480;
  display_cfg.bpp = 32;
}

void setup_gfx_modes() {
  set_default_video_mode();
}

void clear_bitmap(al_bitmap *screen) {
  int len = screen->w*screen->h*bytes_per_pixel(screen);
  SDL_Surface *s = get_surface_from_bmp(screen);
  if (s->pixels) {
    memset(s->pixels,0,len);
  }
}

void clear_raine_screen() {
    // The only call left for this thing is in gui.cpp before starting emulation
    // it doesn't seem necessary anymore with sdl2
}

int bestw,besth,bestbpp;

// Chooses a resolution with the variables bestw, besth and bestbpp
int switch_res(const VIDEO_INFO *vid)
{
    // Since res.c is removed from sdl2 build for now, there is not much point for this function...
   bestw = besth = bestbpp = 0; // No change !!!
   return 0;
}

void build_mode_list() {
}
