/******************************************************************************/
/*									      */
/*  'Default' driver, used to init some stuff with default values mainly...   */
/*									      */
/******************************************************************************/

#include "gameinc.h"
#include "default.h"
#include "savegame.h"
#include "emumain.h"
#include "profile.h"
#include "timer.h" // default z80 frame
#include "adpcm.h"
#include "ay8910.h"
#include "priorities.h"
#include "tc100scn.h"
#include "conf-cpu.h"
#include "conf-sound.h"
#include "config.h"
#include "video/res.h"
#include "tc005rot.h"
#include "blit.h"
#include "speed_hack.h"
#include "taitosnd.h"
#include "tc200obj.h"
#include "files.h"
#ifdef SDL
#include "control_internal.h"
#endif
//#include "sasound.h"            // sample support routines

void LoadDefault(void)
{
  memset(tc0100scn,0,sizeof(tc0100scn));
  read_region_byte = NULL;
  write_region_byte = NULL;
#ifdef RDTSC_PROFILE
  cycles_per_frame = 0; // recalibrate for non 60fps games
#endif
#if HAS_TC200
  f2_sprites_colors = 16;
#endif
  default_fps = 0.0; // init only by the dialog which allows to change fps
#if HAS_ADPCM
  adpcm_amplify = 1;
#endif
#if HAS_AY8910
  ay8910_amplify = 1;
#endif

  ExitOnEI = 0;
  Z80Has16bitsPorts = 0;
  MouseB = &mouse_b;
  setup_z80_frame(CPU_Z80_0,CPU_FRAME_MHz(4,60));
  z80_offdata = 0; // code location = data location
  reset_timers();
  reset_z80_banks();

  ResetMemoryPool();				// Init game memory pool

 

   // ExecuteSoundFrame=NULL;			// Default execution for 1 frame (sound cpu execution)

#if HAVE_68000
   Clear68000List();				// Clear M68000 memory lists
   StarScreamEngine=0;				// No M68000 by default
#endif

#if HAVE_Z80
   ClearZ80List();				// Clear Z80 memory lists
   MZ80Engine=0;				// No Z80 by default
#endif


  // GameSound=0; 				// No Sound emulation by default
//   GameMouse=0; 				// No Mouse driver by default

   raine_cfg.req_pause_game = 0;


   SaveSlot=0;					// Reset save slot to 0
   SaveDataCount=0;				// No save data
   SaveCallbackCount=0; 			// No save callbacks
   savecbptr_count = 0;
   reset_dyn_callbacks();

   RAMSize=0x80000;				// Size of RAM memory allocated (should be 0 here really)

   clear_eeprom_list(); 			// No EEPROMs mapped

   if(raine_cfg.show_fps_mode==2) raine_cfg.show_fps_mode=0;			// Don't like it running from time=0

 //  PCMROM=NULL; 				// Might as well clear these too
   Z80ROM=NULL;
   ROM=RAM=GFX=NULL;

   tile_list_count = 0;
   max_tile_sprites = 0;
   set_pulse_time(15);

   tile_start = 0; // tile queue reset

   set_white_pen(255);

   current_cmap_func = NULL;
   current_colour_mapper = NULL;

   reset_layer_switches();
   set_reset_function(NULL);
#ifdef HAS_CONSOLE
   preinit_console();
#endif
}

void ClearDefault(void)
{
//    free_alpha_tree();
#ifdef SDL
    unregister_driver_emu_keys();
#endif
#if SDL != 2
  use_scale2x = 0;
#endif

  memset(tile_list,0,sizeof(tile_list));
#if USE_TAITOSND
  RemoveTaitoSoundBanking();
#endif
#if USE_TC005
  tc0005rot.RAM = NULL;
#endif
  undo_hack();
  save_game_config();


  if (current_game->clear)
    current_game->clear();

#ifdef RAINE_DEBUG
  for (int region = REGION_CPU1; region <= REGION_CPU4; region++) {
      if (load_region[region]) {
	  int size = get_region_size(region);
	  int swap = 0;;
	  char name[10];
	  sprintf(name,"ROM%d.bin",region);
	  // Only starscream needs its region to be swapped, so...
	  if (!MC68020 && StarScreamEngine && region <= StarScreamEngine)
	      swap = 1;
	  else if (MC68020 && StarScreamEngine && region > REGION_CPU1 && region <= StarScreamEngine+1)
	      swap = 1;
	  save_debug(name,load_region[region],size,swap);
      }
  }

  save_debug("RAM.bin",RAM,RAMSize,0);
#endif

  save_eeprom();
#ifndef NO020
   MC68020 = 0;
#endif

   reset_savegames();

   saDestroySound(1);				// Free all sound resources

   destroy_palette_map();			// Free colour mapping resources

   if(raine_cfg.show_fps_mode==2) raine_cfg.show_fps_mode=0;			// Don't like it running from time=0

   clear_regions();
   FreeMemoryPool();				// Free anything left in the memory pool

   LanguageSw.Count = LanguageSw.Address = 0;

   if (pbitmap) {
     destroy_bitmap(pbitmap);
     pbitmap = NULL;
   }


   DestroyScreenBitmap();

   done_commands();

}

