#ifndef __TICK__
#define __TICK__

int set_proc(int (*call_fun)(void *param),void *dat);

int init_timer(int sec,int usec);

void time_callback(int signo);

#endif
