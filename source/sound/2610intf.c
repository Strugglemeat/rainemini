/***************************************************************************

  2610intf.c

  The YM2610 emulator supports up to 2 chips.
  Each chip has the following connections:
  - Status Read / Control Write A
  - Port Read / Data Write A
  - Control Write B
  - Data Write B

***************************************************************************/

#include "driver.h"
#include "sasound.h"
#include "fm.h"
#include "timer.h"
#include "loadroms.h"
#include "2610intf.h"
#include "streams.h"
#include "games.h"
#include "savegame.h"

UINT8 *YM2610_Rompointers[2];
UINT32 YM2610_Romsizes[2];
extern UINT8 *neogeo_pcm_memory;

#if BUILD_YM2610

#define sound_name(x) "YM2610"

#define YM2610_NUMBUF 2
/* use FM.C with stream system */

static int stream[MAX_2610];

/* Global Interface holder */
static const struct YM2610interface *intf;

static void *Timer[MAX_2610][2];

/*------------------------- TM2610 -------------------------------*/
/* IRQ Handler */
static void IRQHandler(int n,int irq)
{
	if(intf->handler[n]) intf->handler[n](irq);
}

/* Timer overflow callback from timer.c */
void timer_callback_2610(int param)
{
	int n=param&0x7f;
	int c=param>>7;

/*	logerror("2610 TimerOver %d\n",c); */
	if (Timer[n][c]) timer_remove(Timer[n][c]);
	Timer[n][c] = 0;
	YM2610TimerOver(n,c);
}

/* TimerHandler from fm.c */
static void TimerHandler(int n,int c,int count,double stepTime)
{
	if( count == 0 )
	{	/* Reset FM Timer */
		if( Timer[n][c] )
		{
/*			logerror("2610 TimerReset %d\n",c); */
	 		timer_remove (Timer[n][c]);
			Timer[n][c] = 0;
		}
	}
	else
	{	/* Start FM Timer */
		double timeSec = (double)count * stepTime;

		if( Timer[n][c] == 0 )
		{
			Timer[n][c] = timer_set (timeSec , (c<<7)|n, timer_callback_2610 );
		}
	}
}

static void FMTimerInit( void )
{
	int i;

	for( i = 0 ; i < MAX_2610 ; i++ )
		Timer[i][0] = Timer[i][1] = 0;
	save_timers();
	AddSaveData_ext("timers_2610",(UINT8*)&Timer,sizeof(Timer));
}

/* update request from fm.c */
void YM2610UpdateRequest(int chip)
{
	stream_update(stream[chip],100);
}

int YM2610_sh_start(const struct YM2610interface *msound)
{
	int i,j;
	int rate = audio_sample_rate;
	char buf[YM2610_NUMBUF][40];
	const char *name[YM2610_NUMBUF];
	int mixed_vol,vol[YM2610_NUMBUF];
	void *pcmbufa[YM2610_NUMBUF],*pcmbufb[YM2610_NUMBUF];
	int  pcmsizea[YM2610_NUMBUF],pcmsizeb[YM2610_NUMBUF];

	intf = msound;
	if( intf->num > MAX_2610 ) return 1;

	if (AY8910_sh_start((const struct AY8910interface *)msound)) return 1;

	/* Timer Handler set */
	FMTimerInit();

	/* stream system initialize */
	for (i = 0;i < intf->num;i++)
	{
		/* stream setup */
		mixed_vol = intf->volumeFM[i];
		/* stream setup */
		for (j = 0 ; j < YM2610_NUMBUF ; j++)
		{
			name[j]=buf[j];
			vol[j] = mixed_vol & 0xffff;
			mixed_vol>>=16;
			sprintf(buf[j],"%s #%d Ch%d",sound_name(msound),i,j+1);
		}
		stream[i] = stream_init_multim(YM2610_NUMBUF,name,vol,rate,i,YM2610UpdateOne);
		/* setup adpcm buffers */
		if (is_neocd()) {
		    pcmbufa[i] = (void *)PCMROM;
		    pcmsizea[i] = 0x100000;
		    pcmbufb[i] = NULL;
		    pcmsizeb[i] = 0;
		} else {
		    pcmbufa[i]  = (void *)(memory_region(intf->pcmroma[i]));
		    pcmsizea[i] = memory_region_length(intf->pcmroma[i]);
		    pcmbufb[i]  = (void *)(memory_region(intf->pcmromb[i]));
		    pcmsizeb[i] = memory_region_length(intf->pcmromb[i]);
		}
		if (!pcmbufb[i] && pcmbufa[i]) {
		    // if no deltat, use pcm instead
		    pcmbufb[i] = pcmbufa[i];
		    pcmsizeb[i] = pcmsizea[i];
		}
	}

	/**** initialize YM2610 ****/
	if (YM2610Init(intf->num,intf->baseclock,rate,
		           pcmbufa,pcmsizea,pcmbufb,pcmsizeb,
		           TimerHandler,IRQHandler) == 0)
		return 0;

	/* error */
	return 1;
}

#if BUILD_YM2610B
int YM2610B_sh_start(const struct YM2610interface *msound)
{
	int i,j;
	int rate = audio_sample_rate;
	char buf[YM2610_NUMBUF][40];
	const char *name[YM2610_NUMBUF];
	int mixed_vol,vol[YM2610_NUMBUF];
	void *pcmbufa[YM2610_NUMBUF],*pcmbufb[YM2610_NUMBUF];
	int  pcmsizea[YM2610_NUMBUF],pcmsizeb[YM2610_NUMBUF];

	intf = msound;
	if( intf->num > MAX_2610 ) return 1;

	if (AY8910_sh_start_ym((const struct AY8910interface *)msound)) return 1;

	/* Timer Handler set */
	FMTimerInit();

	/* stream system initialize */
	for (i = 0;i < intf->num;i++)
	{
		/* stream setup */
		mixed_vol = intf->volumeFM[i];
		/* stream setup */
		for (j = 0 ; j < YM2610_NUMBUF ; j++)
		{
			name[j]=buf[j];
			vol[j] = mixed_vol & 0xffff;
			mixed_vol>>=16;
			sprintf(buf[j],"%s #%d Ch%d",sound_name(msound),i,j+1);
		}
		stream[i] = stream_init_multim(YM2610_NUMBUF,name,vol,rate,i,YM2610BUpdateOne);
		/* setup adpcm buffers */
		if (is_neocd()) {
		    pcmbufa[i] = (void *)PCMROM;
		    pcmsizea[i] = 0x100000;
		    pcmbufb[i] = NULL;
		    pcmsizeb[i] = 0;
		} else {
		    pcmbufa[i]  = (void *)(memory_region(intf->pcmroma[i]));
		    pcmsizea[i] = memory_region_length(intf->pcmroma[i]);
		    pcmbufb[i]  = (void *)(memory_region(intf->pcmromb[i]));
		    pcmsizeb[i] = memory_region_length(intf->pcmromb[i]);
		}
	}

	/**** initialize YM2610 ****/
	if (YM2610Init(intf->num,intf->baseclock,rate,
		           pcmbufa,pcmsizea,pcmbufb,pcmsizeb,
		           TimerHandler,IRQHandler) == 0)
		return 0;

	/* error */
	return 1;
}
#endif

/************************************************/
/* Sound Hardware Stop							*/
/************************************************/
void YM2610_sh_stop(void)
{
	YM2610Shutdown();
	AY8910_sh_stop_ym();
	AY8910_sh_stop();
}

/* reset */
void YM2610_sh_reset(void)
{
	int i;

	for (i = 0;i < intf->num;i++)
		YM2610ResetChip(i);
}

/************************************************/
/* Status Read for YM2610 - Chip 0				*/
/************************************************/
READ_HANDLER( YM2610_status_port_0_A_r )
{
/*logerror("PC %04x: 2610 S0A=%02X\n",activecpu_get_pc(),YM2610Read(0,0)); */
	return YM2610Read(0,0);
}

READ16_HANDLER( YM2610_status_port_0_A_lsb_r )
{
/*logerror("PC %04x: 2610 S0A=%02X\n",activecpu_get_pc(),YM2610Read(0,0)); */
	return YM2610Read(0,0);
}

READ_HANDLER( YM2610_status_port_0_B_r )
{
/*logerror("PC %04x: 2610 S0B=%02X\n",activecpu_get_pc(),YM2610Read(0,2)); */
	return YM2610Read(0,2);
}

READ16_HANDLER( YM2610_status_port_0_B_lsb_r )
{
/*logerror("PC %04x: 2610 S0B=%02X\n",activecpu_get_pc(),YM2610Read(0,2)); */
	return YM2610Read(0,2);
}

/************************************************/
/* Status Read for YM2610 - Chip 1				*/
/************************************************/
READ_HANDLER( YM2610_status_port_1_A_r ) {
	return YM2610Read(1,0);
}

READ16_HANDLER( YM2610_status_port_1_A_lsb_r ) {
	return YM2610Read(1,0);
}

READ_HANDLER( YM2610_status_port_1_B_r ) {
	return YM2610Read(1,2);
}

READ16_HANDLER( YM2610_status_port_1_B_lsb_r ) {
	return YM2610Read(1,2);
}

/************************************************/
/* Port Read for YM2610 - Chip 0				*/
/************************************************/
READ_HANDLER( YM2610_read_port_0_r ){
	return YM2610Read(0,1);
}

READ16_HANDLER( YM2610_read_port_0_lsb_r ){
	return YM2610Read(0,1);
}

/************************************************/
/* Port Read for YM2610 - Chip 1				*/
/************************************************/
READ_HANDLER( YM2610_read_port_1_r ){
	return YM2610Read(1,1);
}

READ16_HANDLER( YM2610_read_port_1_lsb_r ){
	return YM2610Read(1,1);
}

/************************************************/
/* Control Write for YM2610 - Chip 0			*/
/* Consists of 2 addresses						*/
/************************************************/
WRITE_HANDLER( YM2610_control_port_0_A_w )
{
/*logerror("PC %04x: 2610 Reg A %02X",activecpu_get_pc(),data); */
	YM2610Write(0,0,data);
}

WRITE16_HANDLER( YM2610_control_port_0_A_lsb_w )
{
/*logerror("PC %04x: 2610 Reg A %02X",activecpu_get_pc(),data); */
	if (ACCESSING_LSB)
	{
		YM2610Write(0,0,data);
	}
}

WRITE_HANDLER( YM2610_control_port_0_B_w )
{
/*logerror("PC %04x: 2610 Reg B %02X",activecpu_get_pc(),data); */
	YM2610Write(0,2,data);
}

WRITE16_HANDLER( YM2610_control_port_0_B_lsb_w )
{
/*logerror("PC %04x: 2610 Reg B %02X",activecpu_get_pc(),data); */
	if (ACCESSING_LSB)
	{
		YM2610Write(0,2,data);
	}
}

/************************************************/
/* Control Write for YM2610 - Chip 1			*/
/* Consists of 2 addresses						*/
/************************************************/
WRITE_HANDLER( YM2610_control_port_1_A_w ){
	YM2610Write(1,0,data);
}

WRITE16_HANDLER( YM2610_control_port_1_A_lsb_w ){
	if (ACCESSING_LSB)
	{
		YM2610Write(1,0,data);
	}
}

WRITE_HANDLER( YM2610_control_port_1_B_w ){
	YM2610Write(1,2,data);
}

WRITE16_HANDLER( YM2610_control_port_1_B_lsb_w ){
	if (ACCESSING_LSB)
	{
		YM2610Write(1,2,data);
	}
}

/************************************************/
/* Data Write for YM2610 - Chip 0				*/
/* Consists of 2 addresses						*/
/************************************************/
WRITE_HANDLER( YM2610_data_port_0_A_w )
{
/*logerror(" =%02X\n",data); */
	YM2610Write(0,1,data);
}

WRITE16_HANDLER( YM2610_data_port_0_A_lsb_w )
{
/*logerror(" =%02X\n",data); */
	if (ACCESSING_LSB)
	{
		YM2610Write(0,1,data);
	}
}

WRITE_HANDLER( YM2610_data_port_0_B_w )
{
/*logerror(" =%02X\n",data); */
	YM2610Write(0,3,data);
}

WRITE16_HANDLER( YM2610_data_port_0_B_lsb_w )
{
/*logerror(" =%02X\n",data); */
	if (ACCESSING_LSB)
	{
		YM2610Write(0,3,data);
	}
}

/************************************************/
/* Data Write for YM2610 - Chip 1				*/
/* Consists of 2 addresses						*/
/************************************************/
WRITE_HANDLER( YM2610_data_port_1_A_w ){
	YM2610Write(1,1,data);
}

WRITE16_HANDLER( YM2610_data_port_1_A_lsb_w ){
	if (ACCESSING_LSB)
	{
		YM2610Write(1,1,data);
	}
}

WRITE_HANDLER( YM2610_data_port_1_B_w ){
	YM2610Write(1,3,data);
}

WRITE16_HANDLER( YM2610_data_port_1_B_lsb_w ){
	if (ACCESSING_LSB)
	{
		YM2610Write(1,3,data);
	}
}

int YM2610_get_stream_num( int num )
{
  return stream[num];
}

/**************** end of file ****************/

#endif
