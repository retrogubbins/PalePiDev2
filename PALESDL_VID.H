#ifndef __PALESDL_VID_H__
#define __PALESDL_VID_H__


void initialise_display(void);
Uint8 getpixel(Uint16 offset, Uint8 bit);
int draw_scanline(int scanline);
void query_6845(char *emu_query3,char *emu_query4);
extern unsigned int crtc_reg;
extern unsigned char CRTC_reg[18];
extern void video_resize(int w,int h,int ressizable);
extern int StretchEnable; 
extern void set_screenres();
extern void video_fullscreen(int);

extern int get_display_w();
extern int get_display_h();



#define DISPLAY_CUSTOM 0
#define DISPLAY_1X 1
#define DISPLAY_2X 2
#define DISPLAY_FULLSCREEN 3

           
#endif 

