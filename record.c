
#include"record.h"
#include <string.h>
#include <unistd.h>
#include<stdlib.h>
#include <termios.h>
#include <pthread.h>
#include<fcntl.h>
#include<stdlib.h>

int flag_write=0;
int sec_passed=0;
pthread_t       ntid;

uart_d uart_recorder;
uart_segment uart_recv;
void time_callback(int signo) ;

int uart_finished_record()
{
	char second_passed[4];
	sprintf(second_passed,"%4d",sec_passed-1);
	fseek(uart_recorder.Filep,4,SEEK_SET);
	fwrite(second_passed,1,4,uart_recorder.Filep);
}

int call_on_int(int sig_no)
{
	uart_recorder.d_status=IDLE;
	if(uart_recorder.Filep==NULL) return 1;
	if(sig_no==SIGINT)
	{
		printf("catch SIGINT\r\n");
		fclose(uart_recorder.Filep);
	}

}

void *thread_record()
{
     int ret;
	char temp_buf[4096]={'\0'};
	fprintf(stderr,"thread open OK");

	while(uart_recorder.d_status==RECORD)
	{
		if(flag_write==1)
		{
			flag_write=0;
			continue;
		}
		ret = read(uart_recorder.uart_fd,temp_buf,BUF_SIZE);
		if(ret == -1)
		{
			return -1;
		}
		strcat(uart_recv.data,temp_buf);
		fprintf(stderr,"recv data %s\r\n",uart_recv.data);
		memset(temp_buf,0,4096);
	}

}

int status_switch()
{
  int sec_passed;

  switch(uart_recorder.d_status)
    {
    case IDLE:
      if(uart_recorder.d_action==IDLE) ;
      if(uart_recorder.d_action==RECORD)
	  {
		  uart_recorder.d_status=RECORD;
		  uart_record();
		  return 1;
	  }
      if(uart_recorder.d_action==PLAYBACK) 
	  {
		  uart_recorder.d_status=PLAYBACK;
		  return 1;
	  }
      break;
    case RECORD:
      if(uart_recorder.d_action==IDLE) 
	  {
		  uart_finished_record();
		  uart_idle();
		  uart_recorder.d_status=IDLE;
	  }
      break;
    case PLAYBACK:
	  if(uart_recorder.d_action==IDLE)
	  {
		  uart_recorder.d_status=IDLE;
		  uart_idle();
	  }
      break;
    }
  return 0;
}

int uart_playback()
{
	
}

int uart_status()
{
	return uart_recorder.d_status;
}

int uart_set_record(char *file_name)
{
	struct itimerval ovalue,value2;
	char file_identify[4]="abcd";

	char file_path[50]="/root/";
	if(uart_recorder.d_status==IDLE)
	{
	strcat(file_path,file_name);
	if(!file_name)
		return -1;
	memcpy(uart_recorder.s_file_name,file_name,
		strlen(file_name));
	uart_recorder.Filep = fopen (file_path , "w" );
	if(uart_recorder.Filep==NULL) return -1;
	fwrite(file_identify,1,4,uart_recorder.Filep);
	fseek(uart_recorder.Filep,8,SEEK_SET);

	signal(SIGALRM,time_callback);
	uart_recorder.time_val.it_value.tv_sec = 1;
	uart_recorder.time_val.it_value.tv_usec = 0;
	uart_recorder.time_val.it_interval.tv_sec = 1;
	uart_recorder.time_val.it_interval.tv_usec = 0;
	uart_recorder.d_sec_record=9999;

    uart_recorder.d_action=RECORD;
    status_switch();
    setitimer(ITIMER_REAL, &uart_recorder.time_val, &ovalue);
    uart_dump_module();
    return 1;
	}
}

int uart_set_playback(char *file_name)
{
	struct itimerval ovalue,value2;
	char file_path[50]="/root/";
	char identify[4];
	char sec_recoded[4];
	strcat(file_path,file_name);
	if(!file_name)
		return -1;
	if(uart_recorder.d_status==IDLE)
	{
		memcpy(uart_recorder.s_file_name,file_name,
		strlen(file_name));
		uart_recorder.Filep = fopen (file_path , "r" );
		if(uart_recorder.Filep==NULL) return -1;
		fread(identify,1,4,uart_recorder.Filep);
		fseek(uart_recorder.Filep,4,SEEK_SET);
		fread(sec_recoded,1,4,uart_recorder.Filep);
		uart_recorder.d_sec_playback=atoi(sec_recoded)-1;
		signal(SIGALRM,time_callback);
		uart_recorder.time_val.it_value.tv_sec = 1;
		uart_recorder.time_val.it_value.tv_usec = 0;
		uart_recorder.time_val.it_interval.tv_sec = 1;
		uart_recorder.time_val.it_interval.tv_usec = 0;
		uart_recorder.d_action=PLAYBACK;

		status_switch();
		setitimer(ITIMER_REAL, &uart_recorder.time_val, &ovalue);
		uart_dump_module();
		return 1;
	}
}

int uart_idle()
{
	struct itimerval ovalue,value2;
	sec_passed=0;
	if(uart_recorder.Filep!=NULL)
		{
		uart_recorder.time_val.it_value.tv_sec = 0;
		uart_recorder.time_val.it_value.tv_usec = 0;
		uart_recorder.time_val.it_interval.tv_sec = 0;
		uart_recorder.time_val.it_interval.tv_usec = 0;
		setitimer(ITIMER_REAL, &uart_recorder.time_val, &ovalue);
		fclose(uart_recorder.Filep);
		uart_recorder.Filep=NULL;
		}
}
/*
 *	author cyzheng
 */
int uart_seek_time(int sec)
{
	if(sec<0) return -1;
	if(uart_recorder.d_status==PLAYBACK)
		sec_passed=sec;
	else return -1;
}

int uart_set_idle()
{
	signal(SIGALRM,time_callback);
	sec_passed=0;
	if(	(uart_recorder.d_status==RECORD)||(uart_recorder.d_status==PLAYBACK))
	{
		uart_recorder.d_action=IDLE;
		status_switch();
		uart_dump_module();
		return 1;
	}
	return 0;
}

int uart_record()
{
	int err;
	err = pthread_create(&ntid, NULL, thread_record, NULL);
	return 1;
}

void time_callback(int signo) 
{
	signal(SIGALRM, time_callback);
	 sec_passed++;
	if(signo==SIGALRM) 
	{
	  if(uart_recorder.d_status==RECORD)
	    {
		if(sec_passed>uart_recorder.d_sec_record)
		{
			fprintf(stderr,"recoder finished\r\n");
			uart_recorder.d_action=IDLE;
			pthread_cancel(ntid);
			system("echo shutdown >> /dev/tty");
			status_switch();
		}
	      flag_write=1;
	      sprintf(uart_recv.size,"%d",strlen(uart_recv.data));
	      if(uart_recorder.d_action==RECORD)
	      	    {
	      int i=fwrite(uart_recv.size,1,4,uart_recorder.Filep);
	      if(i!=4)
	    	  {
	    	  	  uart_recorder.err=1;
	    	  	  return ;
	    	  }
	      i=fwrite(uart_recv.data,1,4092,uart_recorder.Filep);
	      if(i!=4092)
	    	  {
	    	  	  uart_recorder.err=1;
	    	  	  return;
	    	  }
	      memset(uart_recv.data,0,4092);
	      	    }
	    }
	  if(uart_recorder.d_status==PLAYBACK)
	  {
		  if(sec_passed>uart_recorder.d_sec_playback)
		  		{
		  			fprintf(stderr,"playback finished\r\n");
		  			uart_recorder.d_action=IDLE;
		  			status_switch();
		  		}
		  if(uart_recorder.d_action==PLAYBACK)
		  {
			  fseek(uart_recorder.Filep,4096*sec_passed+8,SEEK_SET);
			  fread(uart_recv.size,1,4,uart_recorder.Filep);
			  fread(uart_recv.data,1,4092,uart_recorder.Filep);
			  printf("%s",uart_recv.data);
		  }
	  }
	}
}

int uart_init_module(int brc_i)
{
	char cmd_str[100];
	struct termios options;
	signal(SIGINT,call_on_int);
	sprintf(cmd_str,"stty -F /dev/ttyPS1 speed %d cs8 -parenb -cstopb  -echo",brc_i);
	system(cmd_str);
	memset(uart_recv.data,0,4092);
	memset(uart_recv.size,0,4);
	uart_recorder.d_action=IDLE;
	uart_recorder.d_status=IDLE;

	uart_recorder.uart_fd=open("/dev/ttyPS1",O_RDWR | O_NOCTTY);

	if(tcgetattr(uart_recorder.uart_fd,&options)==0){
	cfsetispeed(&options,brc_i);
	cfsetospeed(&options,brc_i);
	if(tcsetattr(uart_recorder.uart_fd,TCSANOW,&options)==0) ;
	else
		return -1;
	}
	if(uart_recorder.uart_fd==NULL)
		return -1;
	flag_write=0;
	return 1;
}

int uart_dump_module()
{
	printf("%d\r\n",uart_recorder.d_action);
	printf("%d\r\n",uart_recorder.d_status);
	return 1;
}

int uart_record_sec(char *file_name,int sec)
{
	struct itimerval ovalue,value2;
	char file_identify[4]="abcd";
	char file_path[50]="/root/";
	strcat(file_path,file_name);
	if(!file_name)
		return -1;

	memcpy(uart_recorder.s_file_name,file_name,
		strlen(file_name));

	uart_recorder.d_sec_record=sec;
	uart_recorder.Filep = fopen (file_path , "w" );
	fwrite(file_identify,1,4,uart_recorder.Filep);
	fseek(uart_recorder.Filep,8,SEEK_SET);

	signal(SIGALRM,time_callback);
	uart_recorder.time_val.it_value.tv_sec = 1;
	uart_recorder.time_val.it_value.tv_usec = 0;
	uart_recorder.time_val.it_interval.tv_sec = 1;
	uart_recorder.time_val.it_interval.tv_usec = 0;

	if(uart_recorder.d_status==IDLE)
	{
		uart_recorder.d_action=RECORD;
		setitimer(ITIMER_REAL, &uart_recorder.time_val, &ovalue);
		status_switch();
		uart_dump_module();
		return 1;
	}

}

