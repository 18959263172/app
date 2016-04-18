#ifndef __RECORD__
#define _RECORD__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>


#define IDLE 1
#define RECORD 2
#define PLAYBACK 3
#define  BUF_SIZE 4096
/*
  recvieve data of uart
 */
#include<stdio.h>
typedef struct file_seg
{
	char size[4];
	char data[4092];
}uart_segment;

typedef struct monitor
{
	int d_sec_record;
	int uart_fd;
	int d_status;
	int d_sec_playback;
	int d_action;
	FILE *Filep;
	int change_thing;
	char s_file_name[500];
	int err;
	struct itimerval time_val;
}uart_d;
//record data  
void start_record(int sec);
//playback data 
void play_back(int sec);
//seek seconds
void seek(int sec);

int uart_record_sec(char *file_name,int sec);
int uart_seek_time(int sec);
int uart_set_playback(char *);
int uart_set_idle();
int uart_set_record(char *);
int uart_init_module(int brc_i);
int uart_dump_module();
int uart_status();

#endif
