
#ifndef __KOGELMEM_H__
#define __KOGELMEM_H__



#define LYNX_MAXMEM 65536
#define LYNX_VIDMEM 65536

unsigned Z80_RDMEM(dword A);
void Z80_WRMEM(dword A,byte V);


extern byte lynx_rom[LYNX_MAXMEM];// lynx ROM copy - updated to allow for many roms
extern  byte bank0[LYNX_MAXMEM]; //rom bank
extern  byte bank1[LYNX_MAXMEM]; //user ram bank
extern  byte bank2[LYNX_MAXMEM]; //video memory (all colors in here for 128k version)
extern  byte bank3[LYNX_MAXMEM]; //expanded video memory	(for 48 & 96, green/alt green in here
extern  byte bank4[LYNX_MAXMEM]; //expanded user memory (for 128)
extern  byte vid_mem[262144];

extern unsigned char speccy;

//FROM RAZE
void  z80_init_memmap(void);
void  z80_map_fetch(UWORD start, UWORD end, UBYTE *memory);
void  z80_map_read(UWORD start, UWORD end, UBYTE *memory);
void  z80_map_write(UWORD start, UWORD end, UBYTE *memory);
void  z80_add_read(UWORD start, UWORD end, int method, void *data);
void  z80_add_write(UWORD start, UWORD end, int method, void *data);
void  z80_set_in(UBYTE (*handler)(UWORD port));
void  z80_set_out(void (*handler)(UWORD port, UBYTE value));
void  z80_set_reti(void (*handler)(void));
void  z80_set_fetch_callback(void (*handler)(UWORD pc));
void  z80_end_memmap(void);
#define Z80_MAP_HANDLED 1

void clearmem();

//extern  byte disk_rom_enabled;


#endif
