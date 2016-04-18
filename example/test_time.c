#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include"timer.h"
/*
  author cyzheng
 */
int timer_callback(void *param)
{
  printf("hello \r\n");
}
/*
  author cyzheng
*/
int main()
{
  init_timer_module(0,500000,timer_callback,0);
  while(1) ;
}
