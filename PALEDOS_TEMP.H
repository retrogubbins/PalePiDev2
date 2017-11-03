
#ifndef __PALEDOS_TEMP_H__
#define __PALEDOS_TEMP_H__



extern int emu_display ;
extern int show_sysvars ;
extern int show_memmap ;
extern int show_status ;
extern int show_status2 ;
extern int show_keycodes ;
extern int memmap_bankno ;


extern int show_tapemon ;

extern int show_memscan;


extern void update_tape_gui();
extern void update_tape_gui_speed();
extern void update_fps_counter();


extern void gui_error(char lbl[]);



extern void update_gui_mtype();
extern void init_gui();
extern void gui_loop_more();
extern void init_sound();
extern void post_init_gui();

extern void update_sysvars();
extern void update_memmap();

extern void update_status();

extern void _chdir(char *fred);

extern void update_disksize_gui();
extern void update_disk_gui();


extern void update_gui_speed();
extern void update_sysvar();
extern void update_tape_monitor();
extern void update_memscan();
extern void gui_loop();
extern void gui_end();


extern void set_memmap_bankno( int j);
extern void set_show_memmap(int j);
extern void set_show_status( int j);
extern void set_show_sysvars( int j);
extern void set_display(int y);
extern void set_SoundEnable(int y);
extern void update_sound();


#endif
