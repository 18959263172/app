#ifndef __TICK__
#define __TICK__
/*
  @author cyzheng
*/
int init_timer_module(int sec,int usec,int (*call_fun)(int),void *dat);


#endif
