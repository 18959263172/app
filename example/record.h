#ifndef __RECORD__
#define _RECORD__

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
  int action_status;
  
  int second_passed;
  
  int action;
  
  int change_thing;
  
  char file_name[40];
  
}uart_d;
//record data  
void start_record(int sec);
//playback data 
void play_back(int sec);
//seek seconds
void seek(int sec);

#endif
