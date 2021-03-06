#include  <sys/select.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include"tick.h"

int sec;
//callback function
int (*g_process_func) (void *param);
//
void *g_dat;
///////////////////////////////////////////
/*
  @function
*/
///////////////////////////////////////////
void time_callback(int signo) 
{
    printf("catch a signal!! \r\n");
        //new1.sock_send(buffer,16);
    switch(signo) 
    {
        case SIGALRM:
            printf("Catch a signal -- SIGALRM ");
            break;
        case SIGVTALRM:
            printf("Catch a signal -- SIGVTALRM ");
            break;
    }
        //new1.sock_rcv(buffer,16);
        //g_process_func(g_dat);
    return;
}
///////////////////////////////////////////
/*
  @function
*/
///////////////////////////////////////////
int init_timer() 
{
    printf("process id is %d ",getpid());
    struct itimerval value,ovalue,value2;
    signal(SIGPROF,time_callback);
    value2.it_value.tv_sec = 0;
    value2.it_value.tv_usec = 500000;
    value2.it_interval.tv_sec = 0;
    value2.it_interval.tv_usec = 500000;
    setitimer(ITIMER_PROF, &value2, &ovalue);
}

int set_proc(int (*call_fun)(void *param),void *dat)
{
    g_process_func=call_fun;
    g_dat=dat;
}
