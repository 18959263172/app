#ifndef C_SOCK

#define CS_SOCK

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
///////////////////////////////////////////
/*
  @author 
  @function
  @type
*/
////////////////////////////////////////////
typedef class Sock_Ctrl
{
private:
    unsigned short portnum;
    int cfd;
    struct sockaddr_in s_add,c_addr;
    int type;
public:
    int sock_init(int type,unsigned short port,char *ip);
    void sock_send(char *buf,int count);
    void sock_rcv(char *buf,int count);
    void sock_close();
}zcsock;

#endif
