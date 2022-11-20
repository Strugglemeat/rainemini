
#ifdef __cplusplus
extern "C" {
#endif

typedef struct raine_bitmap
{
   int xfull;		// Full bitmap width
   int yfull;		// Full bitmap height
   int xtop;		// X Offset of viewable area
   int ytop;		// Y offset of viewable area
   int xview;		// Viewable bitmap width
   int yview;		// Viewable bitmap height
} raine_bitmap;

extern raine_bitmap GameScreen;
extern al_bitmap *GameBitmap; 	// *Full* Bitmap for generating the game screen (eg. 0,0 to 320+32,240+32)
extern al_bitmap *GameViewBitmap; 	// *Viewable* Bitmap for saving (pcx) the game screen (eg. 16,16 to 320+16,240+16)

extern UINT32 pause_time;

void get_screen_coordinates(int *Xoff2,int *Yoff2, int *Destx, int *Desty, int *Xxx, int *Yyy);

#ifdef TRIPLE_BUFFER

void reset_triple_buffer(void);

#endif

/*

bitmap handling

*/

void SetupScreenBitmap(void);

void DestroyScreenBitmap(void);

void ReClipScreen(void);

void DrawNormal(void);
void DrawPaused(void);


#ifdef __cplusplus
}
#endif
