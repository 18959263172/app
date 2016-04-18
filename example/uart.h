#ifndef __UART_RECORDER__
#define __UART_RECORDER__


#define __RECORD__

#define IDLE 1
#define RECORD 2
#define PLAYBACK 3

/*
  recvieve data of uart
 */
char recv[4096];
/*
  @author cyzheng
*/
typedef struct monitor
{
  FILE* file_fd;
  char *file_name;
  int action_status;
  int second_passed;
  int action;
  int change_thing;
  int run_stop;
  struct termios newtio;  
  int uart_fd;
}uart_d;


//uart start playback data
int uart_start_playback();
//uart stop playback data
int uart_stop_playback();
////uart start record data
int uart_start_record();
///uart stop record data
int uart_stop_record();
///uart start playback data
int uart_playback();
//
int uart_idle();

#endif
