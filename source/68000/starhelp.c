/******************************************************************************/
/*                                                                            */
/*                     RAINE - STARSCREAM 68000 INTERFACE                     */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h> // Required to avoid a non sense when declaring uint from m68kcpu.h !

#include "starhelp.h"
#include "raine.h"
#include "savegame.h"
#include "games/default.h"
#include "loadroms.h"
#include "newmem.h"
#include "emumain.h"
#include "cpumain.h"
#include "compat.h"

#if USE_MUSASHI < 2
struct S68000CONTEXT            M68000_context[MAX_68000];
#else
m68ki_cpu_core M68000_context[MAX_68000];
#endif
static struct STARSCREAM_PROGRAMREGION M68000_programregion[MAX_68000][MAX_PROGRAM];
static struct STARSCREAM_DATAREGION    M68000_dataregion_rb[MAX_68000][MAX_DATA];
static struct STARSCREAM_DATAREGION    M68000_dataregion_rw[MAX_68000][MAX_DATA];
static struct STARSCREAM_DATAREGION    M68000_dataregion_wb[MAX_68000][MAX_DATA];
struct STARSCREAM_DATAREGION    M68000_dataregion_ww[MAX_68000][MAX_DATA];
static void *M68000_resethandler[MAX_68000];

int StarScreamEngine;

/*
 *  Fill in the basic structures via these functions...
 */

// FIRST EMULATED 68000

static UINT32 program_count[MAX_68000];
static UINT32 data_count_rb[MAX_68000];
static UINT32 data_count_rw[MAX_68000];
static UINT32 data_count_wb[MAX_68000];
static UINT32 data_count_ww[MAX_68000];

extern UINT8 *RAM_PAL;

void s68000_get_ram(UINT32 cpu, UINT32 *range, UINT32 *count) {
  *count = 0;
  int max = data_count_rb[cpu];
  int n;
  for (n=0; n<max; n++) {
    if (!M68000_dataregion_rb[cpu][n].memorycall &&
         M68000_dataregion_rb[cpu][n].userdata &&
         M68000_dataregion_rb[cpu][n].userdata+M68000_dataregion_rb[cpu][n].lowaddr != RAM_PAL &&
	 (M68000_dataregion_rb[cpu][n].lowaddr & 0xff000000) == 0) {
	range[(*count)++] = M68000_dataregion_rb[cpu][n].lowaddr;
	range[(*count)++] = M68000_dataregion_rb[cpu][n].highaddr;
    }
  }
}

UINT8 *s68k_get_userdata(UINT32 cpu, UINT32 adr) {
  int max = data_count_rb[cpu];
  int n;
  for (n=0; n<max; n++) {
    if (!M68000_dataregion_rb[cpu][n].memorycall &&
         M68000_dataregion_rb[cpu][n].userdata &&
	 M68000_dataregion_rb[cpu][n].lowaddr <= adr &&
	 M68000_dataregion_rb[cpu][n].highaddr >= adr) {
      return M68000_dataregion_rb[cpu][n].userdata;
    }
  }
  return NULL;
}

void *get_userfunc(UINT32 cpu, int read, int size, int off_start, UINT32 offset) {
  int max = 0;
  if (size == 1) {
      if (read) max = data_count_rb[cpu];
      else
	  max = data_count_wb[cpu];
  } else if (size == 2) {
      if (read) max = data_count_rw[cpu];
      else
	  max = data_count_ww[cpu];
  }
  int n;
  for (n=off_start; n<max; n++) {
    if (read) {
      if (size == 1) {
	if (M68000_dataregion_rb[cpu][n].memorycall &&
	    M68000_dataregion_rb[cpu][n].lowaddr <= offset &&
	    M68000_dataregion_rb[cpu][n].highaddr >= offset) {
	  return M68000_dataregion_rb[cpu][n].memorycall;
	}
      } else if (size == 2) {
	if (M68000_dataregion_rw[cpu][n].memorycall &&
	    M68000_dataregion_rw[cpu][n].lowaddr <= offset &&
	    M68000_dataregion_rw[cpu][n].highaddr >= offset) {
	  return M68000_dataregion_rw[cpu][n].memorycall;
	}
      }
    } else { // writes
      if (size == 1) {
	if (M68000_dataregion_wb[cpu][n].memorycall &&
	    M68000_dataregion_wb[cpu][n].lowaddr <= offset &&
	    M68000_dataregion_wb[cpu][n].highaddr >= offset) {
	  return M68000_dataregion_wb[cpu][n].memorycall;
	}
      } else if (size == 2) {
	if (M68000_dataregion_ww[cpu][n].memorycall &&
	    M68000_dataregion_ww[cpu][n].lowaddr <= offset &&
	    M68000_dataregion_ww[cpu][n].highaddr >= offset) {
	  return M68000_dataregion_ww[cpu][n].memorycall;
	}
      }
    }
  }
  return NULL;
}

void add_68000_program_region(UINT32 cpu, UINT32 d0, UINT32 d1, UINT8 *d2)
{
	int n;
	for (n=0; n<program_count[cpu]; n++) {
		if (d0 == M68000_programregion[cpu][n].lowaddr &&
		    d1 == M68000_programregion[cpu][n].highaddr) {
			// already has a memfetch for this, skip it
			return;
		}
	}

   M68000_programregion[cpu][program_count[cpu]].lowaddr  = d0;
   M68000_programregion[cpu][program_count[cpu]].highaddr = d1;
#if USE_MUSASHI == 2
   M68000_programregion[cpu][program_count[cpu]].offset   = d2;
#else
   M68000_programregion[cpu][program_count[cpu]].offset   = (UINT32) d2;
#endif
   program_count[cpu]++;
}

static void set_68000_program_region(UINT32 cpu, UINT32 d0, UINT32 d1, UINT8 *d2)
{
    int n;
    for (n=0; n<program_count[cpu]; n++) {
	if (d0 == M68000_programregion[cpu][n].lowaddr &&
		d1 == M68000_programregion[cpu][n].highaddr) {
#if USE_MUSASHI == 2
	    M68000_programregion[cpu][n].offset   = d2;
#else
	    M68000_programregion[cpu][n].offset   = (UINT32) d2;
#endif
	    return;
	}
    }
}

UINT8 *s68k_get_code_range(UINT32 cpu, UINT32 adr, UINT32 *start, UINT32 *end)
{
  int n;
  for (n=0; n<program_count[cpu]; n++)
    if (M68000_programregion[cpu][n].lowaddr <= adr &&
	M68000_programregion[cpu][n].highaddr >= adr) {
      *start = M68000_programregion[cpu][n].lowaddr;
      *end = M68000_programregion[cpu][n].highaddr;
      return (UINT8*)M68000_programregion[cpu][n].offset;
    }
  return NULL;
}

// macro to check if a callback needs to be inserted before some data
#define CHECK_INSERT(type)                                             \
    if (d3 == NULL) {                                                  \
        int n;                                                         \
        for (n=0; n<data_count_##type[cpu]; n++) {                     \
            if (d0 >= M68000_dataregion_##type[cpu][n].lowaddr &&      \
                    d1 <= M68000_dataregion_##type[cpu][n].highaddr) { \
        printf("*WARNING*: CHECK_INSERT active: %x,%x\n",d0,d1);       \
                insert_##type(cpu,n,d0,d1,d2,d3);                      \
                return;                                                \
            }                                                          \
        }                                                              \
    }

void add_68000_rb(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
	CHECK_INSERT(rb);
   M68000_dataregion_rb[cpu][data_count_rb[cpu]].lowaddr    = d0;
   M68000_dataregion_rb[cpu][data_count_rb[cpu]].highaddr   = d1;
   M68000_dataregion_rb[cpu][data_count_rb[cpu]].memorycall = d2;
   M68000_dataregion_rb[cpu][data_count_rb[cpu]].userdata   = d3 - d0;
   if (data_count_rb[cpu]++ >= MAX_DATA) {
     fatal_error("overflow rb");
   }

}

void add_68000_rw(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
	CHECK_INSERT(rw);
   M68000_dataregion_rw[cpu][data_count_rw[cpu]].lowaddr    = d0;
   M68000_dataregion_rw[cpu][data_count_rw[cpu]].highaddr   = d1;
   M68000_dataregion_rw[cpu][data_count_rw[cpu]].memorycall = d2;
   M68000_dataregion_rw[cpu][data_count_rw[cpu]].userdata   = d3 - d0;
   if (data_count_rw[cpu]++ >= MAX_DATA) {
     fatal_error("overflow rw");
   }

}

void add_68000_wb(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
	CHECK_INSERT(wb);
   M68000_dataregion_wb[cpu][data_count_wb[cpu]].lowaddr    = d0;
   M68000_dataregion_wb[cpu][data_count_wb[cpu]].highaddr   = d1;
   M68000_dataregion_wb[cpu][data_count_wb[cpu]].memorycall = d2;
   M68000_dataregion_wb[cpu][data_count_wb[cpu]].userdata   = d3 - d0;
   if (data_count_wb[cpu]++ >= MAX_DATA) {
     fatal_error("overflow wb");
   }

}

void del_wb(int cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3) {
  int index;
  for (index=0; index < data_count_wb[cpu]; index++) {
    if (M68000_dataregion_wb[cpu][index].lowaddr == d0 &&
        M68000_dataregion_wb[cpu][index].highaddr == d1 &&
	M68000_dataregion_wb[cpu][index].memorycall == d2 &&
	M68000_dataregion_wb[cpu][index].userdata  == d3 - d0)
      break;
  }

  if (index >= data_count_wb[cpu]) return;
  if (data_count_wb[cpu] > index+1)
    memmove(&M68000_dataregion_wb[cpu][index],
	    &M68000_dataregion_wb[cpu][index+1],
	    sizeof(struct STARSCREAM_DATAREGION)*(data_count_wb[cpu]-index-1));
  data_count_wb[cpu]--;
}

void del_ww(int cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3) {
  int index;
  for (index=0; index < data_count_ww[cpu]; index++) {
    if (M68000_dataregion_ww[cpu][index].lowaddr == d0 &&
        M68000_dataregion_ww[cpu][index].highaddr == d1 &&
	M68000_dataregion_ww[cpu][index].memorycall == d2 &&
	M68000_dataregion_ww[cpu][index].userdata  == d3 - d0)
      break;
  }

  if (index >= data_count_ww[cpu]) return;
  if (data_count_ww[cpu] > index+1)
    memmove(&M68000_dataregion_ww[cpu][index],
	    &M68000_dataregion_ww[cpu][index+1],
	    sizeof(struct STARSCREAM_DATAREGION)*(data_count_ww[cpu]-index-1));
  data_count_ww[cpu]--;
}

void del_rb(int cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3) {
  int index;
  for (index=0; index < data_count_rb[cpu]; index++) {
    if (M68000_dataregion_rb[cpu][index].lowaddr == d0 &&
        M68000_dataregion_rb[cpu][index].highaddr == d1 &&
	M68000_dataregion_rb[cpu][index].memorycall == d2 &&
	M68000_dataregion_rb[cpu][index].userdata  == d3 - d0)
      break;
  }

  if (index >= data_count_rb[cpu]) return;
  if (data_count_rb[cpu] > index+1)
    memmove(&M68000_dataregion_rb[cpu][index],
	    &M68000_dataregion_rb[cpu][index+1],
	    sizeof(struct STARSCREAM_DATAREGION)*(data_count_rb[cpu]-index-1));
  data_count_rb[cpu]--;
}

void del_rw(int cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3) {
  int index;
  for (index=0; index < data_count_rw[cpu]; index++) {
    if (M68000_dataregion_rw[cpu][index].lowaddr == d0 &&
        M68000_dataregion_rw[cpu][index].highaddr == d1 &&
	M68000_dataregion_rw[cpu][index].memorycall == d2 &&
	M68000_dataregion_rw[cpu][index].userdata  == d3 - d0)
      break;
  }

  if (index >= data_count_rw[cpu]) return;
  if (data_count_rw[cpu] > index+1)
    memmove(&M68000_dataregion_rw[cpu][index],
	    &M68000_dataregion_rw[cpu][index+1],
	    sizeof(struct STARSCREAM_DATAREGION)*(data_count_rw[cpu]-index-1));
  data_count_rw[cpu]--;
}

int insert_wb(int cpu, int index, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3) {
  if (data_count_wb[cpu] >= MAX_DATA || !data_count_wb[cpu])
    return 0;
  if (index < data_count_wb[cpu])
    memmove(&M68000_dataregion_wb[cpu][index+1],
	    &M68000_dataregion_wb[cpu][index],
	    sizeof(struct STARSCREAM_DATAREGION)*(data_count_wb[cpu]-index));
   M68000_dataregion_wb[cpu][index].lowaddr    = d0;
   M68000_dataregion_wb[cpu][index].highaddr   = d1;
   M68000_dataregion_wb[cpu][index].memorycall = d2;
   M68000_dataregion_wb[cpu][index].userdata   = d3 - d0;
   data_count_wb[cpu]++;
   return 1;
}

int insert_ww(int cpu, int index, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3) {
  if (data_count_ww[cpu] >= MAX_DATA || !data_count_ww[cpu])
    return 0;
  if (index < data_count_ww[cpu])
    memmove(&M68000_dataregion_ww[cpu][index+1],
	    &M68000_dataregion_ww[cpu][index],
	    sizeof(struct STARSCREAM_DATAREGION)*(data_count_ww[cpu]-index));
  M68000_dataregion_ww[cpu][index].lowaddr    = d0;
  M68000_dataregion_ww[cpu][index].highaddr   = d1;
  M68000_dataregion_ww[cpu][index].memorycall = d2;
  M68000_dataregion_ww[cpu][index].userdata   = d3 - d0;
  data_count_ww[cpu]++;
  return 1;
}

int insert_rb(int cpu, int index, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3) {
  if (data_count_rb[cpu] >= MAX_DATA || !data_count_rb[cpu])
    return 0;
  if (index < data_count_rb[cpu])
    memmove(&M68000_dataregion_rb[cpu][index+1],
	&M68000_dataregion_rb[cpu][index],
	sizeof(struct STARSCREAM_DATAREGION)*(data_count_rb[cpu]-index));
  M68000_dataregion_rb[cpu][index].lowaddr    = d0;
  M68000_dataregion_rb[cpu][index].highaddr   = d1;
  M68000_dataregion_rb[cpu][index].memorycall = d2;
  M68000_dataregion_rb[cpu][index].userdata   = d3 - d0;
  data_count_rb[cpu]++;
  return 1;
}

int insert_rw(int cpu, int index, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3) {
  if (data_count_rw[cpu] >= MAX_DATA || !data_count_rw[cpu])
    return 0;
  if (index < data_count_rw[cpu])
    memmove(&M68000_dataregion_rw[cpu][index+1],
	&M68000_dataregion_rw[cpu][index],
	sizeof(struct STARSCREAM_DATAREGION)*(data_count_rw[cpu]-index));
  M68000_dataregion_rw[cpu][index].lowaddr    = d0;
  M68000_dataregion_rw[cpu][index].highaddr   = d1;
  M68000_dataregion_rw[cpu][index].memorycall = d2;
  M68000_dataregion_rw[cpu][index].userdata   = d3 - d0;
  data_count_rw[cpu]++;
  return 1;
}

void add_68000_ww(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
  CHECK_INSERT(ww);

   M68000_dataregion_ww[cpu][data_count_ww[cpu]].lowaddr    = d0;
   M68000_dataregion_ww[cpu][data_count_ww[cpu]].highaddr   = d1;
   M68000_dataregion_ww[cpu][data_count_ww[cpu]].memorycall = d2;
   M68000_dataregion_ww[cpu][data_count_ww[cpu]].userdata   = d3 - d0;
   if (data_count_ww[cpu]++ >= MAX_DATA) {
     fatal_error("overflow add_68000_ww");
   }

}

void set_68000_rb(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
  int i;
  for (i=0; i<data_count_rb[cpu]; i++) {
    if (M68000_dataregion_rb[cpu][i].lowaddr == d0 &&
	M68000_dataregion_rb[cpu][i].highaddr == d1) {
      M68000_dataregion_rb[cpu][i].memorycall = d2;
      M68000_dataregion_rb[cpu][i].userdata = d3 - d0;
      break;
    }
  }
  if (i>=data_count_rb[cpu]) {
    fatal_error("couldn't set rb %x - %x",d0,d1);
  }
}

void set_68000_rw(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
  int i;
  for (i=0; i<data_count_rw[cpu]; i++) {
    if (M68000_dataregion_rw[cpu][i].lowaddr == d0 &&
	M68000_dataregion_rw[cpu][i].highaddr == d1) {
      M68000_dataregion_rw[cpu][i].memorycall = d2;
      M68000_dataregion_rw[cpu][i].userdata = d3 - d0;
      break;
    }
  }
  if (i>=data_count_rw[cpu]) {
    fatal_error("couldn't set rw %x - %x",d0,d1);
  }
}

void set_68000_wb(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
  int i;
  for (i=0; i<data_count_wb[cpu]; i++) {
    if (M68000_dataregion_wb[cpu][i].lowaddr == d0 &&
	M68000_dataregion_wb[cpu][i].highaddr == d1) {
      M68000_dataregion_wb[cpu][i].memorycall = d2;
      M68000_dataregion_wb[cpu][i].userdata = d3 - d0;
      break;
    }
  }
}

void set_68000_ww(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
  int i;
  for (i=0; i<data_count_ww[cpu]; i++) {
    if (M68000_dataregion_ww[cpu][i].lowaddr == d0 &&
	M68000_dataregion_ww[cpu][i].highaddr == d1) {
      M68000_dataregion_ww[cpu][i].memorycall = d2;
      M68000_dataregion_ww[cpu][i].userdata = d3 - d0;
      break;
    }
  }
}

void set_68000_io(UINT32 cpu, UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
  set_68000_rb(cpu, d0, d1, d2, d3);
  set_68000_rw(cpu, d0, d1, d2, d3);
  set_68000_wb(cpu, d0, d1, d2, d3);
  set_68000_ww(cpu, d0, d1, d2, d3);
  if (!d2)
      set_68000_program_region(cpu,d0,d1,d3-d0);
}

void AddMemFetch(UINT32 d0, UINT32 d1, UINT8 *d2)
{
   add_68000_program_region(0, d0, d1, d2);
}

void AddReadByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_68000_rb(0, d0, d1, d2, d3);
}

void AddReadWord(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_68000_rw(0, d0, d1, d2, d3);
}

void AddReadBW (UINT32 d0, UINT32 d1, void *d2, UINT8 *d3) {
   add_68000_rb(0, d0, d1, d2, d3);
   add_68000_rw(0, d0, d1, d2, d3);
}


void AddWriteByte(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_68000_wb(0, d0, d1, d2, d3);
}

void AddWriteWord(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_68000_ww(0, d0, d1, d2, d3);
}

void AddWriteBW(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_68000_wb(0, d0, d1, d2, d3);
   add_68000_ww(0, d0, d1, d2, d3);
}

void AddRWBW (UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_68000_rb(0, d0, d1, d2, d3);
   add_68000_rw(0, d0, d1, d2, d3);
   add_68000_wb(0, d0, d1, d2, d3);
   add_68000_ww(0, d0, d1, d2, d3);
}

void add_68000_ram(int cpu,UINT32 d0, UINT32 d1, UINT8 *d2)
{
   add_68000_rb(cpu, d0, d1, NULL, d2);
   add_68000_rw(cpu, d0, d1, NULL, d2);
   add_68000_wb(cpu, d0, d1, NULL, d2);
   add_68000_ww(cpu, d0, d1, NULL, d2);
}

void add_68000_rom(int cpu,UINT32 d0, UINT32 d1, UINT8 *d2)
{
   add_68000_rb(cpu, d0, d1, NULL, d2);
   add_68000_rw(cpu, d0, d1, NULL, d2);
   add_68000_program_region(cpu,d0,d1,d2-d0);
}

void quiet_reset_handler() {
  print_debug("RESET\n");
}

void AddResetHandler(void *d0)
{
   M68000_resethandler[0] = d0;
}

/*

darn, neill moves things around in the context, so it's not
safe to save starscream contexts incase they change in future
releases, have to 'pack' them into our own save buffer then.

*/

typedef UINT32(*read_func)(UINT32);
typedef void(*write_func)(UINT32,UINT32);

#if USE_MUSASHI < 2
typedef struct SAVE_BUFFER
{
   UINT32 id;
   UINT32 interrupts[8];
   UINT32 dreg[8];
   UINT32 areg[8];
   UINT32 asp;
   UINT32 pc;
   UINT32 odometer;
   UINT16 sr;
   UINT8 stopped;
} SAVE_BUFFER;

static struct SAVE_BUFFER save_buffer[2];
#else
extern uint32 current_cpu_num[16];

static uint32 m68k_read8(uint32 adr) {
    adr &= 0xffffff;
    int cpu = current_cpu_num[CPU_68K_0 >> 4];
    int max = data_count_rb[cpu];
    int n;
    for (n=0; n<max; n++) {
	if (M68000_dataregion_rb[cpu][n].lowaddr <= adr &&
		adr <= M68000_dataregion_rb[cpu][n].highaddr) {
	    if (M68000_dataregion_rb[cpu][n].memorycall)
		return (*(read_func)M68000_dataregion_rb[cpu][n].memorycall)(adr);
	    return ReadByte(M68000_dataregion_rb[cpu][n].userdata+(adr^1));
	}
    }
    return 0xff; // DefBadRead is handled by the starscream structs normally
}

static uint32 m68k_read16(uint32 adr) {
    adr &= 0xffffff;
    int cpu = current_cpu_num[CPU_68K_0 >> 4];
    int max = data_count_rw[cpu];
    int n;
    for (n=0; n<max; n++) {
	if (M68000_dataregion_rw[cpu][n].lowaddr <= adr &&
		adr <= M68000_dataregion_rw[cpu][n].highaddr) {
	    if (M68000_dataregion_rw[cpu][n].memorycall)
		return (*(read_func)M68000_dataregion_rw[cpu][n].memorycall)(adr);

	    return ReadWord(M68000_dataregion_rw[cpu][n].userdata+adr);
	}
    }
    return 0xffff;
}

static uint32 m68k_read32(uint32 adr) {
    adr &= 0xffffff; // needed for games like burningf !
    int cpu = current_cpu_num[CPU_68K_0 >> 4];
    int max = data_count_rw[cpu];
    int n;
    for (n=0; n<max; n++) {
	if (M68000_dataregion_rw[cpu][n].lowaddr <= adr &&
		adr <= M68000_dataregion_rw[cpu][n].highaddr) {
	    if (M68000_dataregion_rw[cpu][n].memorycall)
		return ((*(read_func)M68000_dataregion_rw[cpu][n].memorycall)(adr)<<16) |
		    (*(read_func)M68000_dataregion_rw[cpu][n].memorycall)(adr+2);
	    return ReadLongSc(M68000_dataregion_rw[cpu][n].userdata+adr);
	}
    }
    return 0xffffffff;
}

static void m68k_write8(uint32 adr,uint32 data) {
    adr &= 0xffffff;
    int cpu = current_cpu_num[CPU_68K_0 >> 4];
    int max = data_count_wb[cpu];
    int n;
    for (n=0; n<max; n++) {
	if (M68000_dataregion_wb[cpu][n].lowaddr <= adr &&
		adr <= M68000_dataregion_wb[cpu][n].highaddr) {
	    if (M68000_dataregion_wb[cpu][n].memorycall) {
		(*(write_func)M68000_dataregion_wb[cpu][n].memorycall)(adr,data);
		return;
	    }
	    WriteByte(M68000_dataregion_wb[cpu][n].userdata+(adr^1), data);
	    return;
	}
    }
}

static void m68k_write16(uint32 adr,uint32 data) {
    adr &= 0xffffff;
    int cpu = current_cpu_num[CPU_68K_0 >> 4];
    int max = data_count_ww[cpu];
    int n;
    for (n=0; n<max; n++) {
	if (M68000_dataregion_ww[cpu][n].lowaddr <= adr &&
		adr <= M68000_dataregion_ww[cpu][n].highaddr) {
	    if (M68000_dataregion_ww[cpu][n].memorycall) {
		(*(write_func)M68000_dataregion_ww[cpu][n].memorycall)(adr,data);
		return;
	    }
	    WriteWord(M68000_dataregion_ww[cpu][n].userdata+adr, data);
	    return;
	}
    }
}

static void m68k_write32(uint32 adr,uint32 data) {
    adr &= 0xffffff;
    int cpu = current_cpu_num[CPU_68K_0 >> 4];
    int max = data_count_ww[cpu];
    int n;
    for (n=0; n<max; n++) {
	if (M68000_dataregion_ww[cpu][n].lowaddr <= adr &&
		adr <= M68000_dataregion_ww[cpu][n].highaddr) {
	    if (M68000_dataregion_ww[cpu][n].memorycall) {
		(*(write_func)M68000_dataregion_ww[cpu][n].memorycall)(adr,data >> 16);
		(*(write_func)M68000_dataregion_ww[cpu][n].memorycall)(adr+2,data & 0xffff);
		return;
	    }
	    WriteLongSc(M68000_dataregion_ww[cpu][n].userdata+adr,data);
	    return;
	}
    }
}
#endif

void AddInitMemory(void)
{
#if USE_MUSASHI < 2
   M68000_context[0].fetch       = M68000_programregion[0];
   M68000_context[0].readbyte    = M68000_dataregion_rb[0];
   M68000_context[0].readword    = M68000_dataregion_rw[0];
   M68000_context[0].writebyte   = M68000_dataregion_wb[0];
   M68000_context[0].writeword   = M68000_dataregion_ww[0];
   M68000_context[0].s_fetch     = M68000_programregion[0];
   M68000_context[0].s_readbyte  = M68000_dataregion_rb[0];
   M68000_context[0].s_readword  = M68000_dataregion_rw[0];
   M68000_context[0].s_writebyte = M68000_dataregion_wb[0];
   M68000_context[0].s_writeword = M68000_dataregion_ww[0];
   M68000_context[0].u_fetch     = M68000_programregion[0];
   M68000_context[0].u_readbyte  = M68000_dataregion_rb[0];
   M68000_context[0].u_readword  = M68000_dataregion_rw[0];
   M68000_context[0].u_writebyte = M68000_dataregion_wb[0];
   M68000_context[0].u_writeword = M68000_dataregion_ww[0];
   M68000_context[0].resethandler = M68000_resethandler[0];
   if (!M68000_context[0].resethandler)
       M68000_context[0].resethandler = &reset_game_hardware; // a sound default... !
   M68000_context[0].sr = 0x2700;

   AddSaveCallback_Internal(M68000A_save_update);
   AddLoadCallback_Internal(M68000A_load_update);
   AddSaveData(SAVE_68K_0, (UINT8 *) &save_buffer[0], sizeof(SAVE_BUFFER));
#else
    m68k_init();
    m68ki_cpu.read8 = m68k_read8;
    m68ki_cpu.read16 = m68k_read16;
    m68ki_cpu.read32 = m68k_read32;

    m68ki_cpu.read_im16 = m68k_read16;
    m68ki_cpu.read_im32 = m68k_read32;

    m68ki_cpu.read_pc8 = m68k_read8;
    m68ki_cpu.read_pc16 = m68k_read16;
    m68ki_cpu.read_pc32 = m68k_read32;

    m68ki_cpu.write8 = m68k_write8;
    m68ki_cpu.write16 = m68k_write16;
    m68ki_cpu.write32 = m68k_write32;
    m68k_set_cpu_type(M68K_CPU_TYPE_68000);
    m68k_get_context(&M68000_context[0]);
    // Avoid the pointers at the end of the struct... they should already be initialized
    AddSaveData(SAVE_68K_0, (UINT8 *) &M68000_context[0], (UINT8*)&M68000_context[0].cyc_instruction - ((UINT8*)&M68000_context[0]));
#endif

   if (StarScreamEngine < 1) StarScreamEngine = 1;
}

void Clear68000List(void)
{
   UINT32 ta;

   for(ta = 0; ta < MAX_68000; ta ++){
      program_count[ta] = 0;
      data_count_rb[ta] = 0;
      data_count_rw[ta] = 0;
      data_count_wb[ta] = 0;
      data_count_ww[ta] = 0;
      M68000_resethandler[ta] = NULL;
   }

}

void WriteStarScreamByte(UINT32 address, UINT8 data)
{
   int ta;

   for(ta=0;ta<data_count_wb[0];ta++){
      if((M68000_dataregion_wb[0][ta].lowaddr)==-1 || M68000_dataregion_wb[0][ta].memorycall == &DefBadWriteByte){
	  break;
      }
      else{
         if((address>=M68000_dataregion_wb[0][ta].lowaddr)&&(M68000_dataregion_wb[0][ta].highaddr>=address)){
	     // Notice : the function uses the memoryall array here and not the usual memory array
	     // so the offset must indeed be corrected by substracting the low addr
            if(M68000_dataregion_wb[0][ta].memorycall==NULL && M68000_dataregion_wb[0][ta].userdata){
               WriteByte( ((UINT8 *) M68000_dataregion_wb[0][ta].userdata) + (address^1),data);
	       return;
            }
            else{
               ((write_func)M68000_dataregion_wb[0][ta].memorycall)(address,data);
	       return;
            }
         }
      }
   }
   // Now if it was not found, look in the _rb array even if it's a write
   // it's mainly for the region switch when it's located in rom
   for(ta=0;ta<data_count_rb[0];ta++){
      if((M68000_dataregion_rb[0][ta].lowaddr)==-1){
	  return;
      }
      else{
         if((address>=M68000_dataregion_rb[0][ta].lowaddr)&&(M68000_dataregion_rb[0][ta].highaddr>=address)){
	     // Notice : the function uses the memoryall array here and not the usual memory array
	     // so the offset must indeed be corrected by substracting the low addr
            if(M68000_dataregion_rb[0][ta].memorycall==NULL && M68000_dataregion_rb[0][ta].userdata){
               WriteByte( ((UINT8 *) M68000_dataregion_rb[0][ta].userdata) + (address^1),data);
	       return;
            }
	    // there can't be any function called here, it's a write, not a read !
         }
      }
   }
}

UINT8 ReadStarScreamByte(UINT32 address)
{
   int ta;

   for(ta=0;(UINT32)ta<data_count_rb[0];ta++){
      if((M68000_dataregion_rb[0][ta].lowaddr)==-1){
            print_debug("Rb(%06x) [Via ReadStarScreamByte]\n",address);
         return(0x00);
      }
      else{
         if((address>=M68000_dataregion_rb[0][ta].lowaddr)&&(M68000_dataregion_rb[0][ta].highaddr>=address)){
            if(M68000_dataregion_rb[0][ta].memorycall==NULL && M68000_dataregion_rb[0][ta].userdata){
               return ReadByte( ((UINT8 *) M68000_dataregion_rb[0][ta].userdata) + (address^1) );
	    } else{
               return ((read_func)M68000_dataregion_rb[0][ta].memorycall)(address);
            }
         }
      }
   }

   return 0x00;
}

// SECOND EMULATED 68000

void AddMemFetchMC68000B(UINT32 d0, UINT32 d1, UINT8 *d2)
{
   add_68000_program_region(1, d0, d1, d2);
}

void AddReadByteMC68000B(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_68000_rb(1, d0, d1, d2, d3);
}

void AddReadWordMC68000B(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_68000_rw(1, d0, d1, d2, d3);
}

void AddWriteByteMC68000B(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_68000_wb(1, d0, d1, d2, d3);
}

void AddWriteWordMC68000B(UINT32 d0, UINT32 d1, void *d2, UINT8 *d3)
{
   add_68000_ww(1, d0, d1, d2, d3);
}

void AddInitMemoryMC68000B(void)
{
#if USE_MUSASHI < 2
   M68000_context[1].fetch       = M68000_programregion[1];
   M68000_context[1].readbyte    = M68000_dataregion_rb[1];
   M68000_context[1].readword    = M68000_dataregion_rw[1];
   M68000_context[1].writebyte   = M68000_dataregion_wb[1];
   M68000_context[1].writeword   = M68000_dataregion_ww[1];
   M68000_context[1].s_fetch     = M68000_programregion[1];
   M68000_context[1].s_readbyte  = M68000_dataregion_rb[1];
   M68000_context[1].s_readword  = M68000_dataregion_rw[1];
   M68000_context[1].s_writebyte = M68000_dataregion_wb[1];
   M68000_context[1].s_writeword = M68000_dataregion_ww[1];
   M68000_context[1].u_fetch     = M68000_programregion[1];
   M68000_context[1].u_readbyte  = M68000_dataregion_rb[1];
   M68000_context[1].u_readword  = M68000_dataregion_rw[1];
   M68000_context[1].u_writebyte = M68000_dataregion_wb[1];
   M68000_context[1].u_writeword = M68000_dataregion_ww[1];
   M68000_context[1].resethandler = M68000_resethandler[1];
   M68000_context[1].sr = 0x2700;

   AddSaveCallback_Internal(M68000B_save_update);
   AddLoadCallback_Internal(M68000B_load_update);
   AddSaveData(SAVE_68K_1, (UINT8 *) &save_buffer[1], sizeof(SAVE_BUFFER));
#else
    m68k_init();
    m68k_set_cpu_type(M68K_CPU_TYPE_68000);
    m68ki_cpu.read8 = m68k_read8;
    m68ki_cpu.read16 = m68k_read16;
    m68ki_cpu.read32 = m68k_read32;

    m68ki_cpu.read_im16 = m68k_read16;
    m68ki_cpu.read_im32 = m68k_read32;

    m68ki_cpu.read_pc8 = m68k_read8;
    m68ki_cpu.read_pc16 = m68k_read16;
    m68ki_cpu.read_pc32 = m68k_read32;

    m68ki_cpu.write8 = m68k_write8;
    m68ki_cpu.write16 = m68k_write16;
    m68ki_cpu.write32 = m68k_write32;
    m68k_get_context(&M68000_context[1]);
    // Avoid the pointers at the end of the struct... they should already be initialized
    AddSaveData(SAVE_68K_1, (UINT8 *) &M68000_context[1], (UINT8*)&M68000_context[1].cyc_instruction - ((UINT8*)&M68000_context[1]));
#endif

   if (StarScreamEngine < 2) StarScreamEngine = 2;
}

/*
 *  Helper Functions for Starscream memory read/write structs
 *  ---------------------------------------------------------
 */

void Stop68000(UINT32 address, UINT8 data)
{
	(void)(address);
	(void)(data);
   s68000releaseTimeslice();
   print_debug("[Stop68000]\n");
}

UINT8 DefBadReadByte(UINT32 address)
{
  print_debug("RB(%06x) [%06x]\n",address,s68000_read_pc);
  return 0xFF;
}

UINT16 DefBadReadWord(UINT32 address)
{
       print_debug("RW(%06x) [%06x]\n",address,s68000_read_pc);
   return 0xffff;
}

void DefBadWriteByte(UINT32 address, UINT8 data)
{
      print_debug("WB(%06x,%02x) [%06x]\n",address,data,s68000_read_pc);
#ifdef RAINE_DEBUG
      if (s68000_pc & 0xff000000) {
	printf("68k out of bounds\n");
	print_debug("68k out of bounds\n");
	exit(1);
      }
#endif
}

void DefBadWriteWord(UINT32 address, UINT16 data)
{
      print_debug("WW(%06x,%04x) [%06x]\n",address,data,s68000_read_pc);
}

typedef struct OLD_CONTEXT
{
   UINT8 *memoryfetch;
   UINT8 *memoryreadbyte;
   UINT8 *memoryreadword;
   UINT8 *memorywritebyte;
   UINT8 *memorywriteword;
   void (*resethandler)(void);
   UINT32 dreg[8];
   UINT32 areg[8];
   UINT32 asp;
   UINT32 pc;
   UINT32 odometer;
   UINT16 sr;
   UINT8 stopped;
   UINT8 contextfiller;
} OLD_CONTEXT;

#if USE_MUSASHI < 2
static void do_save_packing(int cpu)
{
   UINT32 ta;

   save_buffer[cpu].id = ASCII_ID('S','0','2','6');

   for(ta=0;ta<8;ta++){
   save_buffer[cpu].dreg[ta]       = M68000_context[cpu].dreg[ta];
   save_buffer[cpu].areg[ta]       = M68000_context[cpu].areg[ta];
   save_buffer[cpu].interrupts[ta] = M68000_context[cpu].interrupts[ta];
   }

   save_buffer[cpu].asp         = M68000_context[cpu].asp;
   save_buffer[cpu].pc          = M68000_context[cpu].pc;
   save_buffer[cpu].odometer    = M68000_context[cpu].odometer;
   save_buffer[cpu].sr          = M68000_context[cpu].sr;

}

void M68000A_save_update(void)
{
   do_save_packing(0);
}

void M68000B_save_update(void)
{
   do_save_packing(1);
}

static void do_load_unpacking(int cpu)
{
   UINT32 ta;

   if( save_buffer[cpu].id == ASCII_ID('S','0','2','6') ){

      for(ta=0;ta<8;ta++){
      M68000_context[cpu].dreg[ta]       = save_buffer[cpu].dreg[ta];
      M68000_context[cpu].areg[ta]       = save_buffer[cpu].areg[ta];
      M68000_context[cpu].interrupts[ta] = save_buffer[cpu].interrupts[ta];
      }

      M68000_context[cpu].asp         = save_buffer[cpu].asp;
      M68000_context[cpu].pc          = save_buffer[cpu].pc;
      M68000_context[cpu].odometer    = save_buffer[cpu].odometer;
      M68000_context[cpu].sr          = save_buffer[cpu].sr;

   }
   else{

      // this hack will make old saves work

      OLD_CONTEXT *old_context;

      old_context = (OLD_CONTEXT *) &save_buffer[cpu];

      for(ta=0;ta<8;ta++){
      M68000_context[cpu].dreg[ta]       = old_context->dreg[ta];
      M68000_context[cpu].areg[ta]       = old_context->areg[ta];
      M68000_context[cpu].interrupts[ta] = 0x00;
      }

      M68000_context[cpu].asp         = old_context->asp;
      M68000_context[cpu].pc          = old_context->pc;
      M68000_context[cpu].odometer    = old_context->odometer;
      M68000_context[cpu].sr          = old_context->sr;
   }
}

void M68000A_load_update(void)
{
   do_load_unpacking(0);
}

void M68000B_load_update(void)
{
   do_load_unpacking(1);
}
#endif

void finish_conf_68000(int cpu) {
   add_68000_rb(cpu,0x000000, 0xFFFFFFFF, DefBadReadByte, NULL);
   add_68000_rw(cpu,0x000000, 0xFFFFFFFF, DefBadReadWord, NULL);
   add_68000_wb(cpu,0x000000, 0xFFFFFFFF, DefBadWriteByte, NULL);
   add_68000_ww(cpu,0x000000, 0xFFFFFFFF, DefBadWriteWord, NULL);

   add_68000_program_region(cpu,-1,-1,NULL);

   if (cpu == 1)
	   AddInitMemoryMC68000B();	// Set Starscream mem pointers...
   else if (cpu == 0)
	   AddInitMemory();	// Set Starscream mem pointers...
   else {
	   fatal_error("can't finish conf for 68000 #%d",cpu);
   }
}

void Add68000Code(int cpu, int offset, int region)
{
    UINT8 *rom = load_region[region];
    int end = offset+get_region_size(region)-1;
    ByteSwap(rom,get_region_size(region));
    cpu &= 0xf;
    add_68000_rb(cpu, offset, end, NULL, rom);
    add_68000_rw(cpu, offset, end, NULL, rom);
    add_68000_program_region(cpu, offset, end, rom-offset);
}
