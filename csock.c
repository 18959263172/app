#include"csock.h"
#include<stdio.h>

/*
  @param:
  type: upd or tcp
  port: portnum
  ip: working ip 
*/
int Sock_Ctrl::sock_init(int type,unsigned short port,char *ip,int isserv)
{
    this->type=type;
    this->isserv=isserv;
    if(type==SOCK_DGRAM)
    {
        printf("config as udp mode");
        cfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    }
    else
    {
        cfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    }
    if(-1 == cfd)
    {
      printf("socket fail ! \r\n");
      return -1;
    }
    if(isserv==CLIENT)
    {
        printf("socket ok !\r\n");
        bzero(&s_add,sizeof(struct sockaddr_in));
        s_add.sin_family=AF_INET;
        s_add.sin_addr.s_addr= inet_addr(ip);
        s_add.sin_port=htons(port);
        
        printf("s_addr = %#x ,port : %d \r\n",s_add.sin_addr.s_addr,s_add.sin_port);
        
        if(type==SOCK_STREAM)
        {
            if(-1 == connect(cfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
            {    
                printf("connect fail !\r\n");
                return -1;
            }
            printf("connect ok !\r\n");
        }
    }
    if(isserv==SERVER)
    {
            if(type==SOCK_DGRAM)
            {
                printf("socket ok !\r\n");
                bzero(&s_add,sizeof(struct sockaddr_in));
                s_add.sin_family=AF_INET;
                s_add.sin_addr.s_addr = htonl(INADDR_ANY);
                s_add.sin_port= htons(9000);
                if(bind(cfd, (struct sockaddr *)&s_add, sizeof(s_add)) < 0)
                {
                    perror("bind");
                    exit(1);
                }
             }
            if(type==SOCK_STREAM)
            {
                printf("socket ok !\r\n");
                bzero(&s_add,sizeof(struct sockaddr_in));
                s_add.sin_family=AF_INET;
                s_add.sin_addr.s_addr = htonl(INADDR_ANY);
                s_add.sin_port= htons(9000);
                if(bind(cfd, (struct sockaddr *)&s_add, sizeof(s_add)) < 0)
                {
                    perror("bind");
                    exit(1);
                }
             }
    }
}
/////////////////////////////////////////////
/*
  @param:
*/
/////////////////////////////////////////////
void Sock_Ctrl::sock_send(char *buf,int count)
{
    int addr_len=sizeof(struct sockaddr_in);
    char *test_buffer="test transfer!!!! \r\n";
    memcpy(buf,test_buffer,strlen(test_buffer));
    if(isserv==CLIENT)
    {
        if(type==SOCK_STREAM)
        {
            send(cfd,buf,count,0);
        }
        if(type==SOCK_DGRAM)
        {
            sendto(cfd,buf,26,0,(struct sockaddr*)&s_add,(socklen_t )addr_len);
        }
    }
    if(isserv==SERVER)
    {
        if(type==SOCK_STREAM)
        {
            send(cfd,buf,count,0);
        }
        if(type==SOCK_DGRAM)
        {
            sendto(cfd,buf,26,0,(struct sockaddr*)&s_add,(socklen_t )addr_len);
        }
    }
}
/////////////////////////////////////////////
/*
  @param:
*/
/////////////////////////////////////////////
void Sock_Ctrl::sock_rcv(char *buf,int count)
{
    int n;
    int addr_len=sizeof(struct sockaddr_in);
 if(isserv==CLIENT)
    {
        if(type==SOCK_DGRAM)
        {
            recvfrom(cfd,buf,sizeof(buf),0,(struct sockaddr*)&s_add,(socklen_t *)&addr_len);
            printf("receieved: %s\r\n",buf);
        }
    }
}
/////////////////////////////////////////////
/*
  @param:
*/
/////////////////////////////////////////////
void Sock_Ctrl::sock_close()
{
    close(cfd);
}


