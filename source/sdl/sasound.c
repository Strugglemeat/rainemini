/******************************************************************************/
/*									      */
/*			    SAMPLE SUPPORT FOR RAINE			      */
/*									      */
/*			  modified by Hiromitsu Shioya			      */
/* Author : Emmanuel Anne						      */
/******************************************************************************/
//
// This is the main sound driver for raine right now.
// The seal driver is ported from this driver.
//
/* This is now the reference sound driver for raine.
   SDL allows an incredible flexibility.

   There is clearly an imprecision in the soundcards when playing a 22Khz sound for
   almost nothing, I tested it in streams.c a difference of 1 byte makes the sound
   late or in advance for base_len. And the precise base_len can't be guessed apparently.

   In allegro this problem is without solution, see the 2 versions of sasound.c in its
   directory (in windows, allegro works. Apparently its sampling functions lack precision
   in linux, but I didn't try to find out why).

   In SDL, a handler is called precisely when needed to update this sound buffer.
   Then when we update the streams buffers we check the difference between the point
   writen to by the streams and the point read by sdl. If the difference is changing
   too much, we just drop or add a sound frame (it can't be heared at all).

   This can't be adapted to allegro, the differences vary too much in allegro to be
   usable, and there is no callback.

   Notice : there are still some pieces of very old code from before version 0.28
   in this file. I should clean it up one day... maybe.
*/


#ifdef RAINE_DEBUG
/* Normally when you mix different voices, you are supposed to check if the result
   gets too loud. But we can avoid this by setting the volume of the different sound chips
   to reasonable values. That's exactly what mame is already doing. Nice idea, it's faster
   and since the sound has not to be bounded it probably sounds better too.
   So this setting is here only to know if our volume is still too loud when in debug
   mode (prints out on stderr) */
#define TEST_OVERFLOW
#endif

#if SDL < 2
#define SDL_PauseAudioDevice(dev,pause) SDL_PauseAudio(pause)
#endif

#include <time.h>
#include "raine.h"
#include "sasound.h"
#include "games.h"
#include "debug.h"
#include "timer.h"
#include "profile.h" // fps

#include "SDL.h"
#include "SDL_audio.h"

#include "control.h"
#include "control_internal.h"

int GameSound,dev;
static int fadeout,fade_nb,fade_frame;

static char driver_name[40];


int RaineSoundCard;

/* Avoid to uncomment USE_8BITS unless you finish 8bit support... which is
    pretty useless nowdays ! */

//#define USE_8BITS 1


SoundRec      *SndMachine = NULL, snd_entry;

/* audio related stuff */

static INT16 *lpWave[NUMVOICES];

// The "normal" version of PlayStream does not use samples nor voicexs.
// It just uses "streams" ! What a mess !

static int	   playing[NUMVOICES];

int	    audio_sample_rate;

static int reserved_channel = 0,opened_audio = 0,sound_init = 0;

static int stream_buffer_max;

static int pause_sound;

void saCheckPlayStream( void );

void saSetVolume( int channel, int data )
{
  // For SDL, we mix the sound in software, see update_recording in streams.c
}

void saSetPan( int channel, int data )
{
}

#include "streams.c"

/*******************************************************************************************/
/*  sa???Sound										   */
/*******************************************************************************************/

/******************************************/
/*    update sound			  */
/******************************************/

void saUpdateSound( int nowclock )
{
   if( ! GameSound ) return;
   if( ! RaineSoundCard ) return;
   if( ! audio_sample_rate ) return;
   if( ! SndMachine ) return;

   if( nowclock ){
     //int i;
     // This part is called for each frame, which *should* be 60
  // times/sec, but it can be less (if the game slows down)
      streams_sh_update();
   }
}

int enh_stereo = 0;

extern int max_mixer_volume;
static void my_callback(void *userdata, Uint8 *stream, int len);

/******************************************/
/*    setup sound			  */
/******************************************/
BOOL saInitSoundCard( int soundcard, int sample_rate )
{
   int i;
   if (opened_audio)
     return TRUE;
   RaineSoundCard = soundcard;
   /* install a digital sound driver */
     // Normally, soundcard =0 means no sound in raine.
     // I will try not to break this to keep compatibility with the other
     // sources...
   sound_card_id(soundcard);

/*    if ( SDL_Init(SDL_INIT_AUDIO) < 0 ) { */
/*      fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError()); */
/*      exit(1); */
/*    } */
/*    atexit(SDL_Quit); */

   for( i = 0; i < NUMVOICES; i++ ){

      lpWave[i]  = 0;
      playing[i] = 0;
   }

   stream_buffer_max = STREAM_BUFFER_MAXB;

   //reserved_channel = 0;

   pause_sound = 0;		/* pause flag off */
   if (!opened_audio
#if SDL < 2
	   // For use with normal blits and libefence, it became allergic to opengl and the audio libs !
	   // the only way to use it is to really disable audio and to use normal blits
	   && soundcard
#endif
	   ) {
       SDL_AudioSpec spec;
       // printf("openaudio: samples calculated : %d/%g = %d, pow2 %d\n",sample_rate,fps,len,spec.samples);
#if SDL == 2
       int i = soundcard -1;
       const char *name = SDL_GetAudioDeviceName(i,0);
       printf("%d: %s\n",i,name);
       SDL_GetAudioDeviceSpec(i,0,&spec);
       spec.userdata = NULL;
       spec.callback = my_callback;
       if (sample_rate) {
	   spec.freq = sample_rate;
	   int len = sample_rate/fps;
	   spec.samples = (len); // should be pow2, but doesn't change anything!
       }
       spec.format = AUDIO_S16LSB;
       spec.channels = 2;
       if ( (dev=SDL_OpenAudioDevice(name,0,&spec, &gotspec,0)) < 0 )
#else
	   spec.userdata = NULL;
       spec.callback = my_callback;
       spec.freq = sample_rate ? sample_rate : 44100;
       int len = sample_rate/fps;
       spec.samples = (len); // should be pow2, but doesn't change anything!
       spec.format = AUDIO_S16LSB;
       spec.channels = 2;
       if (SDL_OpenAudio(&spec,&gotspec))
#endif
       {

	   fprintf(stderr,"Couldn't open audio: %s\n", SDL_GetError());
	   RaineSoundCard = 0;
	   return 0;
       }
       printf("openaudio: desired samples %d, got %d freq %d,%d format %x,%x\n",spec.samples,gotspec.samples,spec.freq,gotspec.freq,spec.format,gotspec.format);
       audio_sample_rate = gotspec.freq;
       opened_audio = 1;

       sound_init = 1;
#if SDL == 1
       strcpy(driver_name,"SDL ");
       SDL_AudioDriverName(&driver_name[4], 32);
       print_debug("sound driver name : %s\n",driver_name);
#endif
       // set_sound_variables(0);
   }
   if(!init_sound_emulators()) {
       SDL_PauseAudioDevice(dev,0);
       return 1;  // Everything fine
   }

   return 0;
}

/******************************************/
/*    setup sound			  */
/******************************************/

void init_sound(void)
{
  const SOUND_INFO *sound_src; // games/games.h
  int ta;

  sound_src = current_game->sound;

  if(sound_src){

    saStopSoundEmulators();

    for( ta = 0; ta < SND_CONTROL_MAX; ta++ ){
      SndMachine->init[ta] = SOUND_NONE;
      SndMachine->intf[ta] = NULL;
    }

    SndMachine->first = 0;
    SndMachine->control_max = 0;

    ta = 0;

    while(sound_src[ta].type){

      SndMachine->init[ta] = sound_src[ta].type;
      SndMachine->intf[ta] = sound_src[ta].interface;

      ta++;

    }

    SndMachine->control_max = ta;

    GameSound = 1;

  }
}

/******************************************/
/*    destroy sound			  */
/******************************************/

void saDestroyChannel( int chan )
{
  if( lpWave[chan] ){
    FreeMem( (UINT8*)lpWave[chan] );
    lpWave[chan] = 0;
    playing[chan] = 0;
  }
}

static int callback_busy;

static FILE *fbin;

typedef struct
{
    Uint8 *decoded_ptr;
    Uint32 decoded_bytes;
} playsound_global_state;

static volatile playsound_global_state global_state;


void init_samples() {
    fadeout = 0;
  if (!pause_sound && dev>0) SDL_PauseAudioDevice(dev,0);
}


void start_music_fadeout(double time) {
    fadeout = 1;
    fade_nb = audio_sample_rate/gotspec.samples*time;
    fade_frame = 0;
}

static void close_sample() {


  global_state.decoded_bytes = 0;
  global_state.decoded_ptr = NULL;
  if (fbin) {
    fclose(fbin);
    fbin = NULL;
  }
}

void saDestroySound( int remove_all_resources )
{
   int i;

   print_debug("saDestroySound: Removing SEAL\n");

   //pause_raine_ym3812();

   /* We *MUST* close the audio here because of implicit frequency conversion.
      If you load pacman first then the audio will be opened at 96 Khz, so it must
      be closed at the end in order to open it again at a more normal frequency later. */

   if (remove_all_resources) {
       close_sample();
   }
   if (opened_audio) {
     /* Well for some unknown reason calling Sound_Quit and then Sound_Init
      * later crashes sdl_sound when it was not used the 1st time - on a mixed
      * mode iso for example. Simply not calling ever sound_quit seems fine. */
     // int quit = Sound_Quit();
     // printf("sound_quit %d\n",quit);
#if SDL == 2
     SDL_CloseAudioDevice(dev);
#else
     SDL_CloseAudio();
#endif
     dev = 0;
   }

   if(remove_all_resources){
     saStopSoundEmulators();
   }


   for( i = 0; i < NUMVOICES; i++ ){
      saDestroyChannel(i);

   }
#ifdef USE_COMPENS
   reset_streams();
#endif

#ifdef RAINE_DEBUG
   print_debug("saDestroySound: OK\n");
#endif
   opened_audio = 0;
}

void sa_pause_sound(void)
{
   if (!pause_sound) {
     pause_sound	    = 1;

     //pause_raine_ym3812();
     if (dev>0)
	 SDL_PauseAudioDevice(dev,1);

   }
}

void sa_unpause_sound(void)
{
   if(GameSound && RaineSoundCard){
     if (pause_sound) {
       pause_sound	   = 0;
       if (dev > 0)
	   SDL_PauseAudioDevice(dev,0);

     }
   }
}

/*******************************************************************************************/
/*******************************************************************************************/
/******************************************/
/*    play samples			  */
/******************************************/
#if 0
// This was supposed to resample the voice, but it does not work well at all !!!
INT16 get_average(signed short *din, int distance, double rapport) {
  int start = distance*rapport;
  int len = (distance+1)*rapport - start;
  int nb = 0;
  int i;
  return din[start];
  for (i=start; i<start+len; i++) {
    nb += din[i];
  }
  return nb/len;
}
#endif


// len of the buffer to update in samples
#define LEN_SAMPLES 2048


static void my_callback(void *userdata, Uint8 *stream, int len)
{
    int i,channel;
    short *wstream = (short*) stream;
    if(raine_cfg.show_fps_mode>2) ProfileStart(PRO_SOUND);
    if (pause_sound) {
#if SDL == 2
	memset(stream,0,len);
#endif
	if(raine_cfg.show_fps_mode>2) ProfileStop(PRO_SOUND);
	return;
    }
    if (callback_busy)
	print_debug("entering callback with busy = %d\n",callback_busy);
    callback_busy = 1;
    // printf("callback frame %d\n",cpu_frame_count);
    // int nb=0;

    // 1. Fill the stream with the sample, if available
	memset(stream,0,len);


    len /= 2; // 16 bits from now on

    /* Ideally in this case I would average the buffer.
       But normally this happens only when the sound becomes late because of the OS.
       Either heavy swapping or windows "multitasking" defieciency (saw it even in win2k
       when you change the focus of the window, the sound stops updating !!!). So in
       this case we just need to jump directly to the correct point of update */

    for (channel=0; channel<NUMVOICES; channel++) {
	if (stream_buffer[channel]) {
      int num_sem = channel;
      while (!sem[num_sem]) num_sem--;
	    SDL_SemWait(sem[num_sem]);
	    int volume = SampleVol[channel];
	    int vol_l = (255-SamplePan[channel])*volume/255;
	    int vol_r = (SamplePan[channel])*volume/255;

	    if (stream_buffer_pos[channel] < len/2) {
		// printf("callb: underrun channel %d, wanted %d got %d\n",channel,len/2,stream_buffer_pos[channel]);
		if (stream_callback[channel] || stream_callback_multi[channel])
		    stream_update_channel(channel, len/2-stream_buffer_pos[channel]);
		else {
		    print_debug("buffer underrun channel %d and no callback\n",channel);
		    SDL_SemPost(sem[num_sem]);
		    continue;
		}
	    }
	    // Otherwise it's been initialized already...
	    signed short *din=((signed short*)stream_buffer[channel]);
	    /* normal buffer, no resample */
	    for (i=0; i<len; i+=2) {
		INT16 left = *(din)*vol_l/255;
		INT16 right = *(din++)*vol_r/255;
#ifdef TEST_OVERFLOW
		INT32 sample = wstream[i]+left;
		if (sample > 0x7fff) {
		    printf("overflow left %x\n",sample);
		    sample = 0x7fff;
		} else if (sample < -0x8000) {
		    printf("underflow left %x\n",sample);
		    sample = -0x8000;
		}
		wstream[i] = sample;
		sample = wstream[i+1] + right;
		if (sample > 0x7fff) {
		    printf("overflow right %x\n",sample);
		    sample = 0x7fff;
		} else if (sample < -0x8000) {
		    printf("underflow right %x\n",sample);
		    sample = -0x8000;
		}
		wstream[i+1] = sample;
#else
		wstream[i] += left;
		wstream[i+1] += right;
#endif
	    }
	    if (stream_buffer_pos[channel] == len/2) {
		stream_buffer_pos[channel] = 0;
	    } else {
		// printf("after callback pos = %d instead of %d\n",stream_buffer_pos[channel],len/2);
		memcpy(stream_buffer[channel],stream_buffer[channel]+len,stream_buffer_pos[channel]*2-len);
		stream_buffer_pos[channel] -= len/2;
	    }
	    SDL_SemPost(sem[num_sem]);
	}
    }

 
/*
    if (recording) {
	mixing_buff_len = len;
	mixing_buff = wstream;
	if (f_record)
	    fwrite(mixing_buff,2,len,f_record);
	updated_recording++;
    }*/
    callback_busy = 0;
    if(raine_cfg.show_fps_mode>2) ProfileStop(PRO_SOUND);
}

void saPlayBufferedStreamedSampleBase( int channel, signed char *data, int len, int freq, int volume, int bits , int pan ){
	/* This version works at low level, creating a sample, and following its
		 advancement directly in the voice_position... */
	// fprintf(stderr,"saPlayBuffer %d freq %d bits %d pan %d len %d\n",channel,freq,bits,pan,len);
	if( audio_sample_rate == 0 || channel >= NUMVOICES )	return;
	if( SndMachine == NULL )  return;
	if( !playing[channel] ){

		playing[channel] = 1;	/* use front surface */

	}
}

#ifdef USE_8BITS
/******************************************/
/*    play samples			  */
/******************************************/
void saPlayStreamedSampleBase( int channel, signed char *data, int len, int freq, int volume, int bits , int pan ){
  // This one should leave most of the sync work to allegro
  int pos;
	void *buff; // position in the stream
  unsigned short *dout;
  signed short *din;
  int i;
  if (bits == 8) {
    fprintf(stderr,"error: Can't play 8 bits\n");
    // Just because I don't want to bother with this now.
    return;
  }
  if( audio_sample_rate == 0 || channel >= NUMVOICES )	return;
  if( SndMachine == NULL )  return;
  if( !playing[channel] ){
    if( stream[channel] ){
      stop_audio_stream(stream[channel]);
      free_audio_stream_buffer(stream[channel]);
      stream[channel] = NULL;
    }

    // printf("playing %d at freq %d\n",channel,freq);
    if (!(stream[channel] = play_audio_stream(len,bits,0,freq,volume,pan))){
      return;
    }
    playing[channel] = 1;	/* use front surface */

    // Wait for the buffer to be ready...
    while (!(buff = get_audio_stream_buffer(stream[channel])));
    //print_debug("first stream entry. [%d:%d:%d:%d]\n", channel, len, freq, volume );

  }

  if (!(buff = get_audio_stream_buffer(stream[channel]))) {
    fprintf(stderr,"init stream impossible : buffer NULL\n");
    return;
  }
  //	fprintf(stderr,"len memcpy : %d\n",len);
  dout=buff;
  din = ((signed short*)data);
  for (i=0; i<len; i+=2)
    *(dout++) = *(din++)^0x8000;

  //fprintf(stderr,"set chanel vol = %d\n",volume);
}
#endif

/******************************************************************************/
/*									      */
/*			  SOUND CHANNEL ALLOCATION			      */
/*									      */
/******************************************************************************/

int saGetPlayChannels( int request )
{
   int ret_value = reserved_channel;
   reserved_channel += request;
   return ret_value;
}

void saResetPlayChannels( void )
{
   reserved_channel = 0;
}

/******************************************************************************/
/*									      */
/*			    SOUND CARD INFORMATION			      */
/*									      */
/******************************************************************************/

char *sound_card_name( int num )
{
   int id = sound_card_id(num);

   if (id == 0)
     return "Silence";
   if (!driver_name[0]) {
     strcpy(driver_name,"SDL <autodetect>");
   }
   return driver_name;
}

int sound_card_id( int i )
{
  return i; // for now no id in sdl
}

/******************************* END OF FILE **********************************/

