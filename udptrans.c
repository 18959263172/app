#include <stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include"csock.h"
#include<arpa/inet.h>
#include<sys/time.h>
#include<time.h>
int main()
{
  int exit=0;

  int stop=1;

  zcsock new1;

  char buffer[1024]={0};   
  
  printf("Hello,welcome to client !\r\n");
 
  new1.sock_init(SOCK_DGRAM,8000,"192.168.100.123");
  
  while(!exit)
    {
            //printf("send one time");
        new1.sock_rcv(buffer,16);
            //new1.sock_send(buffer,16);
        
    }

  new1.sock_close();
  
  return 0;

}

