#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//This next line includes one of the two Z80 emulations
//either the RAZE x86 assembly core, or the compiled C KOGEL core
#include "EMUSWITCH.h"
#include "PALEDOS_TEMP.H"

#include "PALESDL.H"
#include "PALESDL_VID.H"
#include "PALESDL_IO.H"

#include "PALETAPS.H"
#include "PALESND.H"
#include "PALESDL_CONFIG.H"
#include "PALEMEM.H"
#include "PALEROM.H"
#include "PALE_KEYS.H"
#include "PALERAWTAPE.H"
//#include "PALEDISK.H"

//Some status info routines and disassembler for the Z80 core
//#include "CORE_STATUS.H"


#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <SDL/SDL.h>
#include "EMUSWITCH.h"


#include "PALESDL_IO.H"
#include "PALESDL.H"
#include "PALE48K.H"
#include "PALE96K.H"
#include "PALE128K.H"
#include "PALESDL_VID.H"
#include "sge_surface.h"
#include "sge_rotation.h"

//#define VIDEO_METHOD SDL_SWSURFACE|SDL_HWPALETTE|SDL_ASYNCBLIT|SDL_DOUBLEBUF
//#define VIDEO_METHOD SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_HWPALETTE
#define VIDEO_METHOD SDL_SWSURFACE|SDL_ASYNCBLIT


//static SDL_Surface *screen;
//static SDL_Surface *surface;
//static SDL_Surface *surface2;

int StretchEnable=0;	//Enables VIdeo Stretch function
unsigned char CRTC_reg[18];
unsigned int crtc_reg=0;
static SDL_Surface *screen;



//  ONLY FOR SCALING
//  ONLY FOR SCALING
//  ONLY FOR SCALING
   /* Create a 32-bit surface with the bytes of each pixel in R,G,B,A order,
       as expected by OpenGL for textures */
    Uint32 rmask, gmask, bmask, amask;



SDL_Color LynxPalette[8] = {{0,0,0,0},{0,0,255,0},{255,0,0,0},{255,0,255,0}, \
	{0,255,0,0},{0,255,255,0},{255,255,0,0},{255,255,255,0}};

void clearcrtc()
{
	for(int f=0;f<18;f++)
		CRTC_reg[f]=0;
}

void video_fullscreen(int x)
{
	if(x)
	{
		screen = SDL_SetVideoMode(512,512, 8,  VIDEO_METHOD|SDL_FULLSCREEN);
		//screen = SDL_SetVideoMode(512,512, 16,  VIDEO_METHOD|SDL_FULLSCREEN);
	}
	else
	{
		set_screenres();
	}
	SDL_DisplayFormat(screen);
	SDL_SetColors(screen, LynxPalette, 0, 8);
}



void set_screenres()
{
	//Initially the screen is NOT resizable
	screen = SDL_SetVideoMode(512,512, 8,  VIDEO_METHOD);
   	if ( screen == NULL )
	{
        printf("Couldnt get Video MODE");
		exit(1);
    }

 	if ( SDL_DisplayFormat(screen)==NULL )
	{
         printf("Couldnt get Video MODE");
	     exit(1);
    }
	// Set palette
	SDL_SetColors(screen, LynxPalette, 0, 8);
}


void initialise_display(void){
    /* Initialize the SDL library (Video/Keyboard)*/
    if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0 ) {
//    if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
         fprintf(stderr,"Couldn't initialize SDL: %s\n", SDL_GetError());
         printf("Couldnt get Video MODE");
        exit(1);
    }
	set_screenres();

//  ONLY FOR SCALING
//  ONLY FOR SCALING
//  ONLY FOR SCALING
    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
//  ONLY FOR SCALING
//  ONLY FOR SCALING
//  ONLY FOR SCALING

 
}




//Returns ZERO if end of screen
int draw_scanline(int scanline)
{
	SDL_Rect retRect;
	Uint8 *bits;
	int memy, memx;
	int ret,hor_disp_pix,hor_disp_bytes,vrt_disp_pix,line;


	if(((video_latch & 0x22)!=0x20))
//	if(((video_latch & 0x60)!=0x20))
	{
		hor_disp_bytes=32;
		vrt_disp_pix=248;

	
		if(scanline>vrt_disp_pix)
		{
			SDL_UpdateRect(screen, 0,0,512,512);
			return(0);//end of frame
		}

		bits=((Uint8 *)screen->pixels)+(scanline*1024); 
		memy=scanline*32;
		for(memx=0;memx<hor_disp_bytes;memx++) {

		*((Uint8 *)(bits++)) = getpixel(memy + memx, 7);
		*((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
		*((Uint8 *)(bits++)) = getpixel(memy + memx, 6);
		*((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
		*((Uint8 *)(bits++)) = getpixel(memy+ memx, 5);
		*((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
		*((Uint8 *)(bits++)) = getpixel(memy+ memx, 4);
		*((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
		*((Uint8 *)(bits++)) = getpixel(memy+ memx, 3);
		*((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
		*((Uint8 *)(bits++)) = getpixel(memy+ memx, 2);
		*((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
		*((Uint8 *)(bits++)) = getpixel(memy+ memx, 1);
		*((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
		*((Uint8 *)(bits++)) = getpixel(memy+ memx, 0);
		*((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));

		}
		for(memx=0;memx<512;memx++)
			*((Uint8 *)(bits++)) = *((Uint8 *)(bits-512));
//		SDL_UpdateRect(screen, 0,scanline,256,1);
	}	
	return(1);
}      


void query_6845(char *emu_query3,char *emu_query4)
{
	int ret,f,g;
return;
}

int get_display_w()
{
	return(screen->w);
}
int get_display_h()
{
	return(screen->h);
}


void check_for_resize()
{
//    if(event.type==SDL_VIDEORESIZE)
//		video_resize(event.resize.w,event.resize.h,1);	
}


#define PALE_REV 0.55555


#define DEBUG 0

//MEMORY IO STUFF
UBYTE	 z80ports_in[0x10000];          /* I/O ports */
UBYTE 	 z80ports_out[0x10000];          /* I/O ports */
UBYTE    bank0[LYNX_MAXMEM];		  /* Rom */
UBYTE    bank1[LYNX_MAXMEM];		  /* User Ram */
UBYTE    bank2[LYNX_MAXMEM];          /* Red 0x0000/Blue 0x2000*/
UBYTE    bank3[LYNX_MAXMEM];    	  /* AltGreen 0x0000/Green 0x2000*/
UBYTE    bank4[LYNX_MAXMEM];

#define EMU_SPEEDS 10
float emuspeeds[EMU_SPEEDS]={25,50,100,200,400,800,1000,2000,5000,32000};
int emu_speed=2;
int hw_type=LYNX_HARDWARE_48;
int mc_type=0;
int ss_emu=0;
int run_emu=1;
int finish_emu=0;
int debug=0;
int SoundEnable=0;
int fps_counter=0;

int trap_pc=0xffff;
double	time_per_fps_disp;
double	last_fps_time;
int newtime;
int framecount;
Uint16 scanline;

long emu_cycles_scanline=256;
long emu_cycles_lineblank=88;
long emu_cycles_vblank=400;
long emu_cycles=13000;

unsigned int sound_cycles=0;
unsigned int tapecyc=0; 
int trace=0;
FILE *tracedump_file;

void setpc()
{

	z80_set_reg(Z80_REG_PC, 0xe000);
}
float get_pale_rev()
{
	return((float)PALE_REV);
}

void start_tracedump()
{
		char lbl[50];
		tracedump_file=fopen("TRACEDUMP.TXT","wt");
        if(tracedump_file==NULL)
        {
                sprintf(lbl,"Cannot open PALE TraceDUMP File for writing");
				gui_error(lbl);
                return;
        }
}
void stop_tracedump()
{
	fclose(tracedump_file);
}

void tracedump(UWORD pc)
{
	char lbl[200];
	static int start=0;
  
	if(z80_get_reg(Z80_REG_PC)==0xe000)
		start=1;
	if(start==1)
	{
		//get_statusregs(lbl);
		fprintf(tracedump_file,lbl);
		fprintf(tracedump_file,"\n");
	}
}

void bit(unsigned char *vari,unsigned char posit,unsigned char valu)
{
        if (valu==0)
                *vari=(*vari & (255-((unsigned char)1 << posit)));
        else
                *vari=(*vari | ((unsigned char)1 << posit));
}


void set_speed(int x)
{
	if(x<0)
		x = 0;
	else if(x>EMU_SPEEDS-1)
		x=EMU_SPEEDS-1;

	emu_speed=x;
//	update_gui_speed(x);
//	saveconfigfile();

	switch(hw_type)
	{
		case LYNX_HARDWARE_48:
			emu_cycles_scanline=(long)(emuspeeds[x]*256)/100; //256 = 64us Scanline Period
			emu_cycles_lineblank=(long)(emuspeeds[x]*88)/100; //88 = 22us LineBlank Period
			emu_cycles_vblank=(long)(emuspeeds[x]*160)/100;  //160= 40us Vblank(IRQ LOW) Period
			emu_cycles=(long)(emuspeeds[x]*13600)/100;  //13600 = 3.4ms Vblank period
			break;
		case LYNX_HARDWARE_96:
			emu_cycles_scanline=(long)(emuspeeds[x]*256)/100; //256 = 64us Scanline Period
			emu_cycles_lineblank=(long)(emuspeeds[x]*88)/100; //88 = 22us LineBlank Period
			emu_cycles_vblank=(long)(emuspeeds[x]*160)/100;  //160= 40us Vblank(IRQ LOW) Period
			emu_cycles=(long)(emuspeeds[x]*13600)/100;  //13600 = 3.4ms Vblank period
			break;
		case LYNX_HARDWARE_128:
			emu_cycles_scanline=(long)(emuspeeds[x]*384)/100; // = 64us Scanline Period
			emu_cycles_lineblank=(long)(emuspeeds[x]*132)/100; // = 22us LineBlank Period
			emu_cycles_vblank=(long)(emuspeeds[x]*240)/100;  //= 40us Vblank(IRQ LOW) Period
			emu_cycles=(long)(emuspeeds[x]*20400)/100;  // = 3.4ms Vblank period
			break;
	}
}



void initialise_Lynx(void)
{
	//gui_error("In Init Lynx");
 	memset(&bank0[0x0000], 0xFF, LYNX_MAXMEM);
 	memset(&bank1[0x0000], 0xFF, LYNX_MAXMEM);
   	memset(&bank2[0x0000], 0xFF, LYNX_MAXMEM);
   	memset(&bank3[0x0000], 0xFF, LYNX_MAXMEM);
   	memset(&bank4[0x0000], 0xFF, LYNX_MAXMEM);
	clearports();
	load_romset(mc_type);
	if(!load_lynx_rom())
	{
		gui_error("Couldn't open the working ROM");
		exit(1);
	}
	//save_memdump();
	initmem();//Must come after ROMset load so we know what the hardware is


	z80_reset(); 
	
}


void set_machine(int x)
{
	mc_type=x;
//	update_gui_mtype(x);

	initialise_Lynx();
	saveconfigfile();

	set_speed(emu_speed);
}


// ------------------------------------------------------------------ 
#undef main
int main(int argc, char *argv[])
{
	FILE *handle;
	char *filenam;
	char TAPfilenam[100];
	char TAPstatus[2000];
	static char scan_lbl[10];
  	static int last_time;
	int f_delay=10;
	int this_time,wait_time,frame_time;
	int loaddelframes = 61;
	
	sprintf(TAPfilenam,"\0");

	if(argc>1)
	{	
		printf("TAP filename:%s\n",argv[1]);
		sscanf("%s",argv[1],&TAPfilenam);
	}

	//MUST BE HERE before Initgui FOR WINXP to WORK
    initialise_display();//Must be here because loading COnfig file will reset the display size

	init_gui();
	init_ROMsets();
	if(!loadROMconfigfile())
	{
		saveROMconfigfile();
 		loadROMconfigfile();
	}


	init_sound();
	initialise_Lynx();

set_machine(0);
set_speed(3);


	post_init_gui();

	scanline = 0;

	gui_loop_more();	//Little dose of GUI to start with - get all the windows open etc.

	//Used for locking emu speed
	//last_time=SDL_GetTicks();
        while (finish_emu==0) 
        {	
		if(run_emu==1)
	        {
			Line_Blank=0;
			sound_cycles+=z80_emulate(emu_cycles_lineblank + emu_cycles_scanline);//22 us Line Blanking Execution
			// and 64 us Scanline execution
		}

		// FRAME BLANKING PERIOD
		// FRAME BLANKING PERIOD
		// FRAME BLANKING PERIOD
		if(draw_scanline(scanline++)==0)	//draw returns zero if its end of frame
		{
			if(run_emu==1)
			{
				update_keyrate(); //Update the keyboard repetition and delay rates for diff emu speeds
				CheckKeys();
			}
			scanline = 0;
			     
	 	
			z80_lower_IRQ();
			//Should be 160 T States with IRQ held low by CURSOR 6845 signal
			if(run_emu==1)	sound_cycles+=z80_emulate(emu_cycles_vblank);

	              	z80_raise_IRQ(0xFF);
  
		   	if(run_emu==1)
			{
				//modded when found in error to be just + when convert to PALEDOS
				sound_cycles+=z80_emulate(emu_cycles);//main impact of speedup
			}
		}
  	}
	//stop_tracedump();
//	kill_disks();
	gui_end();
}

void stop_emu()
{
	run_emu=0;
}
void start_emu()
{
	run_emu=1;
}
void quit_emu()
{
	finish_emu=1;
}
void reset_emu()
{
	initialise_Lynx();
}
