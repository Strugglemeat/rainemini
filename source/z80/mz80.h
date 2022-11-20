/* Multi-Z80 32 Bit emulator */

/* Copyright 1999, Neil Bradley, All rights reserved
 *
 * License agreement:
 *
 * The mZ80 emulator may be distributed in unmodified form to any medium.
 *
 * mZ80 May not be sold, or sold as a part of a commercial package without
 * the express written permission of Neil Bradley (neil@synthcom.com). This
 * includes shareware.
 *
 * Modified versions of mZ80 may not be publicly redistributed without author
 * approval (neil@synthcom.com). This includes distributing via a publicly
 * accessible LAN. You may make your own source modifications and distribute
 * mZ80 in object only form.
 *
 * mZ80 Licensing for commercial applications is available. Please email
 * neil@synthcom.com for details.
 *
 * Synthcom Systems, Inc, and Neil Bradley will not be held responsible for
 * any damage done by the use of mZ80. It is purely "as-is".
 *
 * If you use mZ80 in a freeware application, credit in the following text:
 *
 * "Multi-Z80 CPU emulator by Neil Bradley (neil@synthcom.com)"
 *
 * must accompany the freeware application within the application itself or
 * in the documentation.
 *
 * Legal stuff aside:
 *
 * If you find problems with mZ80, please email the author so they can get
 * resolved. If you find a bug and fix it, please also email the author so
 * that those bug fixes can be propogated to the installed base of mZ80
 * users. If you find performance improvements or problems with mZ80, please
 * email the author with your changes/suggestions and they will be rolled in
 * with subsequent releases of mZ80.
 *
 * The whole idea of this emulator is to have the fastest available 32 bit
 * Multi-z80 emulator for the PC, giving maximum performance.
 */

/* General z80 based defines */

#ifndef	_MZ80_H_
#define	_MZ80_H_

#include "deftypes.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MEMORYREADWRITEBYTE_
#define _MEMORYREADWRITEBYTE_

struct MemoryWriteByte
{
	UINT32 lowAddr;
	UINT32 highAddr;
	void (*memoryCall)(UINT32, UINT8, struct MemoryWriteByte *);
	void *pUserArea;
};

struct MemoryReadByte
{
	UINT32 lowAddr;
	UINT32 highAddr;
	UINT8 (*memoryCall)(UINT32, struct MemoryReadByte *);
	void *pUserArea;
};

#endif // _MEMORYREADWRITEBYTE_

struct z80PortWrite
{
	UINT16 lowIoAddr;
	UINT16 highIoAddr;
	void (*IOCall)(UINT16, UINT8, struct z80PortWrite *);
	void *pUserArea;
};

struct z80PortRead
{
	UINT16 lowIoAddr;
	UINT16 highIoAddr;
	UINT16 (*IOCall)(UINT16, struct z80PortRead *);
	void *pUserArea;
};

extern UINT8 ExitOnEI,Z80Has16bitsPorts;;
extern UINT32 dwElapsedTicks;

#ifndef MAME_Z80
struct mz80context
{
	UINT8 *z80Base;
	struct MemoryReadByte *z80MemRead;
	struct MemoryWriteByte *z80MemWrite;
	struct z80PortRead *z80IoRead;
	struct z80PortWrite *z80IoWrite;
  UINT32 dwElapsedTicks; // sorry but we need to know this for each cpu
  // if we want to use timers !!!

  // A few of the interrupt fields could be word instead of UINT32 but I keep
  // them as UINT32 for compatibility with mz80 2.7 while loading a game...
	UINT32 z80iff,z80interruptMode;
        UINT32 z80intPending;
	UINT32 z80halted;

	UINT16 z80af;
	UINT16 z80bc;
	UINT16 z80de;
	UINT16 z80hl;
	UINT16 z80afprime;
	UINT16 z80bcprime;
	UINT16 z80deprime;
	UINT16 z80hlprime;
	UINT16 z80ix;
	UINT16 z80iy;
	UINT16 z80sp;
	UINT16 z80pc;
	UINT16 z80nmiAddr;
	UINT16 z80intAddr;
  UINT8 z80i;
  UINT8 z80r;
  UINT8 z80rCounter;
};

extern UINT32 z80intPending; // For debuging
extern UINT32 cyclesRemaining; // for the timers
extern UINT32 _z80iff;

extern UINT8 *z80Base;		// mz80Base;
extern INT32 z80_offdata;
extern UINT32 mz80exec(unsigned long int);
extern UINT32 mz80GetContextSize(void);
extern UINT32 mz80GetElapsedTicks(UINT32);
extern void mz80ReleaseTimeslice();
extern void mz80GetContext(void *);
extern void mz80SetContext(void *);
extern void mz80reset(void);
extern UINT32 mz80int(UINT32);
extern UINT32 mz80nmi(void);
extern UINT16 z80intAddr;
extern UINT16 z80nmiAddr;
extern UINT16 z80pc;

typedef struct mz80context CONTEXTMZ80;
#else
#include "mame/z80/z80.h"

#define mz80ReleaseTimeslice z80_release_time_slice
#define z80intPending  Z80.irq_state
#define mz80GetContext(a) z80_get_context(a)
#define mz80SetContext(a) z80_set_context(a)
void mz80int(int vector);
#define cyclesRemaining z80_ICount
#define _z80iff (Z80.iff1|(Z80.iff2<<1))
#define mz80nmi()                                  \
{                                                  \
    z80_set_irq_line(Z80.irq_vector,INPUT_LINE_NMI,HOLD_LINE);  \
    z80_execute(10);                              \
    z80_set_irq_line(Z80.irq_vector,INPUT_LINE_NMI,CLEAR_LINE); \
}
#define mz80exec(cycles) z80_execute(cycles)
#define mz80reset() z80_reset()
#define z80af af.d
#define z80bc bc.d
#define z80de de.d
#define z80hl hl.d
#define z80pc Z80.pc.d
#define z80sp sp.d
#define z80ix ix.d
#define z80iy iy.d
#endif

#ifdef __cplusplus
};
#endif

#endif	// _MZ80_H_
