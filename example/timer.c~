#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include"timer.h"

int sec;
int (*g_process_func) (void *);
void *g_dat;
/*
  @author
  @param 
*/
void time_callback(int signo) 
{
  switch(signo) 
    {
    case SIGALRM:
      if(g_process_func(g_dat)<0) printf("error open data\r\n");
      break;
    }
  return;
}
/*
  @author
  @param
  1.second .
  2.usecond.
  3.timer callback function.
  4.parameter be transfered. 
*/

int init_timer_module(int sec,int usec,int (*call_fun)(int),void *da) 
{
  struct itimerval value,ovalue,value2;
  signal(SIGALRM,time_callback);
  if((sec==0)&&(usec==0)) return -1;
  
  value2.it_value.tv_sec = sec;
  value2.it_value.tv_usec = usec;
  value2.it_interval.tv_sec = sec;
  value2.it_interval.tv_usec = usec;
  
  setitimer(ITIMER_REAL, &value2, &ovalue);
  
  
  g_process_func=call_fun;
  g_dat=da;
  return 1;
}
