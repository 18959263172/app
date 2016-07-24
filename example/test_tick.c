#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "csock.h"
#include <arpa/inet.h>
#include <sys/time.h>
#include <time.h>
#include "tick.h"
zcsock new1;
char buffer[1024]={0};   
int irq_call(void * )
{
    printf("irq called \r\n");
}
int main()
{
    int exit=0;
    int stop=1;
    printf("Hello,welcome to client !\r\n");
    set_proc(irq_call,NULL);
    new1.sock_init(SOCK_DGRAM,8000,"127.0.0.1");
    init_timer();
    while(!exit)
    {   
        new1.sock_send(buffer,16);
            //printf("send one time");
        new1.sock_rcv(buffer,16);
    }
    
    new1.sock_close();
    
    return 0;
}

