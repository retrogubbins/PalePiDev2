#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <io.h>
#include "../EMUSWITCH.h"

#include <stdlib.h>

//#include "../PALEDISK.H"
#include "../PALESDL.H"
#include "../PALESDL_IO.H"
#include "../PALESDL_VID.H"

void  z80_init_memmap(void){};
void  z80_map_fetch(UWORD start, UWORD end, UBYTE *memory){};
void  z80_map_read(UWORD start, UWORD end, UBYTE *memory){};
void  z80_map_write(UWORD start, UWORD end, UBYTE *memory){};
void  z80_add_read(UWORD start, UWORD end, int method, void *data){};
void  z80_add_write(UWORD start, UWORD end, int method, void *data){};
void  z80_set_in(UBYTE (*handler)(UWORD port)){};
void  z80_set_out(void (*handler)(UWORD port, UBYTE value)){};
void  z80_set_reti(void (*handler)(void)){};
void  z80_set_fetch_callback(void (*handler)(UWORD pc)){};
void  z80_end_memmap(void){};
 
unsigned Z80_RDMEM(dword A)
{
	char lbl[100];


	{
		//see if ROM is paged in or not
		if((bank_latch & 0x10)==0 )		//ROMS BANK 0
		{
			//	sprintf(lbl," BANK0 READ PC=%4X  VidLatch=%X BankLatch=%X Addr=%X:( ",get_pc(),video_latch,bank_latch,A);
			if (A<0x6000)
				return(bank0[A]);
			//			if((A>=0x6000) && (A<0x8000))
			//				return(bank0[0xe000+(A-0x6000)]);
			//			if(A>=0x8000 && A<0xc000)
			//				return(bank0[A-0x8000]);
			//			if(A>=0xc000 && A<0xe000)
			//				return(bank0[0x4000+(A-0xc000)]);
			if(bank0[0xe000]!=0xff)// Disk rom is special - can be turned off
			{
//				if((A>=0xe000)   && ((disk_options&0x10)==0))
//				return(bank0[A]);
			}
		}	
		
		if ((bank_latch & 0x20)==0)	//USER RAM
		{

			{
				if(A>=0x6000 && A<0x8000)
					return(bank1[A]);
				if(A>=0xe000 && A<=0x10000)		//Mirror
					return(bank1[A-0x8000]);	
				if(A>=0x8000 && A<0xa000)
					return(bank1[A]);
				if(A>=0x0000 && A<0x2000)
					return(bank1[A+0x8000]);	//mirror
				if(A>=0x2000 && A<0x4000)
					return(bank1[A+0x8000]);	//mirror
				if(A>=0x4000 && A<0x6000)
					return(bank1[A+0x2000]);	//mirror
				if(A>=0xa000 && A<0xc000)
					return(bank1[A-0x2000]);	
				if(A>=0xc000 && A<0xe000)
					return(bank1[A-0x6000]);	//mirror
			}
		}
		if ((bank_latch & 0x40)==0x40)	//vidram
		{
			if ((video_latch & 0x04)==0) 
			{
				if(A>=0xa000 && A<0xe000)
					return(bank2[A]);		//BLUE  RED
				if(A>=0x8000 && A<0xa000)
					return(bank2[A+0x2000]);	//mirror
				if(A>=0x6000 && A<0x8000)
					return(bank2[A+0x6000]);	//mirror
				if(A>=0xe000 && A<0x10000)
					return(bank2[A-0x2000]);	//mirror
				if(A>=0x0000 && A<0x2000)
					return(bank2[A+0xa000]);	//mirror
				if(A>=0x2000 && A<0x4000)
					return(bank2[A+0x8000]);	//mirror
				if(A>=0x4000 && A<0x6000)
					return(bank2[A+0x8000]);	//mirror
			}
			if ((video_latch & 0x08)==0)
			{
				if(A>=0xa000 && A<0xe000)
					return(bank3[A]);//		if((video_latch & 0x20)==0x20 && (bank_latch & 0x02)==0x02)
											//AGREEN  GREEN
				if(A>=0x8000 && A<0xa000)
					return(bank3[A+0x2000]);	//mirror
				if(A>=0x6000 && A<0x8000)
					return(bank3[A+0x6000]);	//mirror
				if(A>=0xe000 && A<0x10000)
					return(bank3[A-0x2000]);	//mirror

				if(A>=0x0000 && A<0x2000)
					return(bank3[A+0xa000]);	//mirror
				if(A>=0x2000 && A<0x4000)
					return(bank3[A+0x8000]);	//mirror
				if(A>=0x4000 && A<0x6000)
					return(bank3[A+0x8000]);	//mirror
			}
		}

	}
	//	sprintf(lbl," ERROR - couldnt find that memory address PC=%4X   VidLatch=%X BankLatch=%X Addr=%X:( ",get_pc(),video_latch,bank_latch,A);
	//	MessageBox(NULL,lbl,"PALE ",MB_YESNOCANCEL | MB_DEFBUTTON1);
	return(0xff);  //  ;>
}

void Z80_WRMEM(dword A,byte V)
{
	char lbl[100];



	{
		if((bank_latch & 0x01)==0)
		{

			{
				if(A>=0x6000 && A<0x8000)
					bank1[A]=V;
				else if(A>=0xe000 && A<=0x10000)	//mirror
					bank1[A-0x8000]=V;
				else if(A>=0x8000 && A<0xa000)
					bank1[A]=V;
				else if(A>=0x0000 && A<0x2000)
					bank1[A+0x8000]=V;
				else if(A>=0x2000 && A<0x4000)
					bank1[A+0x6000]=V;
				else if(A>=0x4000 && A<0x6000)
					bank1[A+0x2000]=V;
				else if(A>=0x0000 && A<0x2000)
					bank1[A+0x8000]=V;
				else if(A>=0xc000 && A<0xe000)
					bank1[A-0x6000]=V;
				else if(A>=0xa000 && A<0xc000)
					bank1[A-0x2000]=V;
			}
		}
		//		if((video_latch & 0x20)==0x20 && (bank_latch & 0x02)==0x02)
		if((bank_latch & 0x02)==0x02)
		{
			if ((video_latch & 0x04)==0) 
			{
				if(A>=0xa000 && A<0xe000)
					bank2[A]=V;				// BLUE RED
				else if(A>=0x8000 && A<0xa000)
					bank2[A+0x2000]=V;				// mirror
				else if(A>=0x6000 && A<0x8000)
					bank2[A+0x6000]=V;				// mirror
				else if(A>=0xe000 && A<0x10000)
					bank2[A-0x2000]=V;				// mirror
				else if(A>=0x0000 && A<0x2000)
					bank2[A+0xa000]=V;				// mirror
				else if(A>=0x2000 && A<0x4000)
					bank2[A+0x8000]=V;				// mirror
				else if(A>=0x4000 && A<0x6000)
					bank2[A+0x8000]=V;				// mirror
				//NOT TESTED YET - WERE MISSING
				//ONE MIRROR OUT OF THE VIDEO READS AND WRITESS
				//		else if(A>=0xa000 && A<0xc000)
				//			bank2[A-0x2000]=V;				// mirror
			}
		}
		//		if((video_latch & 0x20)==0x20 && (bank_latch & 0x04)==0x04)
		if((bank_latch & 0x04)==0x04)
		{
			if ((video_latch & 0x08)==0) 
			{
				if(A>=0xa000 && A<0xe000)
					bank3[A]=V;				//AGREEN  GREEN
				else if(A>=0x8000 && A<0xa000)
					bank3[A+0x2000]=V;				// mirror
				else if(A>=0x6000 && A<0x8000)
					bank3[A+0x6000]=V;				// mirror
				else if(A>=0xe000 && A<0x10000)
					bank3[A-0x2000]=V;				// mirror

				else if(A>=0x0000 && A<0x2000)
					bank3[A+0xa000]=V;				// mirror
				else if(A>=0x2000 && A<0x4000)
					bank3[A+0x8000]=V;				// mirror
				else if(A>=0x4000 && A<0x6000)
					bank3[A+0x8000]=V;				// mirror
			}
		}
	}
}

