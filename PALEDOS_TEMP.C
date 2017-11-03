#include "EMUSWITCH.h"

#include "PALESDL.H"

#include "PALEDOS_TEMP.H"

int emu_display = 0;
int show_sysvars = 0;
int show_memmap = 0;
int show_status = 0;
int show_status2 = 0;
int show_keycodes = 0;
int memmap_bankno = 0;


int show_tapemon = 0;

int show_memscan = 0;

void update_tape_gui(){};
void update_tape_gui_speed(){};
void update_fps_counter(){};


void gui_error(char lbl[])
{
    char name[20];
    char txt[300];
    sprintf(txt,"\n\f2\a0Pete Meditation ERROR:\f7\n%s\f7\n",lbl);
  //  my_input(txt,name);
printf(txt);
};



void update_gui_mtype(){};
void init_gui(){};
void gui_loop_more(){};
void init_sound(){};
void post_init_gui(){};

void update_sysvars(){};
void update_memmap(){};

void update_status()
{
//    draw_overlay();           
};

void _chdir(char *fred)
{


}


void update_disksize_gui(){};
void update_disk_gui(){};


void update_gui_speed(){};
void update_sysvar(){};
void update_tape_monitor(){};
void update_memscan(){};
void gui_loop(){};
void gui_end(){};


void set_memmap_bankno( int j){};
void set_show_memmap(int j){};
void set_show_status( int j){};
void set_show_sysvars( int j){};
void set_display(int y){};
void set_SoundEnable(int y){};
void update_sound(){};
