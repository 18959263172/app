#include"record.h"
#include<string.h>
uart_d uart_recorder;
/*
  author cyzheng
*/
void thread_record()
{
  while(uart_recorder->run_stop==1)
    {
	
    }
}
uart_d uart_recorder;
/*
  author cyzheng
*/
void thread_playback()
{
  while(uart_recorder->run_stop==1)
    {
	
    }
}
/*
  author:cyzheng
*/
void start_record()
{
  
  
}
/*
  author:cyzheng
*/
void start_playback(){
  
}


int status_switch(){
  int sec_passed;
  switch(uart_recorder->action_status)
    {
    case IDLE:
      if(uart_recorder->action==IDLE) ;
      if(uart_recorder->action==RECORD)
	{
	  uart_recorder->action_status=IDLE;
	  start_record();
	}
      if(uart_recorder->action==PLAYBACK)
	{
	  uart_recorder->action_status=PLAYBACK;
	  start_playback(); 
	}
      break; 
    case RECORD:
      if(uart_recorder->action==IDLE) 
	{
	  if(uart_stop_record()<0)
	    return -1;
	  uart_recorder->action==IDLE;
	  break;
	}
      break;
    case WAIT:
      break;
    case PLAYBACK:
      if(uart_recorder->action==IDLE)
	{
	  uart_recorder->action_status=PLAYBACK;
	  uart_stop_record();
	}
      break;
    }
}
/*
  @author cyzheng
*/
void uart_start_playback(){
  
}
/*
  @author cyzheng
*/

int init_uart_recorder_module(char *name){
  char dst[50]="/home/root/console/";
  
  strcat(dst,name);
  uart_recorder.file_fd = fopen(dst,"w+");
  memcpy(uart_recorder->file_name,name,strlen(name));

  return 1;
}
int OpenDev(char *Dev)

{
    //Dev 就是设备，设备就是文件，就是给出该设备文件的路径
    int uart_recorder = open(Dev, O_RDWR ); //| O_NOCTTY | O_NDELAY
    if (-1 == fd)
    {
       perror("Can't Open Serial Port");
       return -1;
    }
    else
       return fd;

}
void uart_init(int speed)
{   
    int fd;
    int nread;
    char buff[512];
    char *dev = "/dev/ttyS1"; //串口二
    uart_recorder.fd = OpenDev(dev);
    set_speed(fd, speed);
    if (set_Parity(fd, 8, 1, 'N') == FALSE)
    {
       printf("Set Parity Error\n");
       exit (0);
    }
    
}
