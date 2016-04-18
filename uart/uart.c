#include"uart.h"

//串口写测试程序
int ASerial::serial_write(int count,char *buf)
{
    int n=0;
    n=write(fd,buf,count);
    return 0;
}
//串口读操作函数
int ASerial::serial_read(int count,char*buf)
{
    read(fd,buf,count);
    return 0;
}
//串口初始化函数
void ASerial::init_serial(const char *path)
{
    if(fd=open(path,O_RDWR|O_NOCTTY|O_NONBLOCK)==-1) 
        perror("error");  //打开串口
    m_uart1.c_cflag|=CLOCAL|CREAD;  //设置为读写模式
    cfmakeraw(&m_uart1);   //定制规则
    cfsetispeed(&m_uart1,B115200);  //设波特率
    cfsetospeed(&m_uart1,B115200); //设置接收波特率
    m_uart1.c_cflag&=~CSIZE;  
    m_uart1.c_cflag|=CS8;
    m_uart1.c_cflag&=~CSTOPB;
    m_uart1.c_cc[VTIME]=0;
    m_uart1.c_cc[VMIN]=0;
    tcflush(fd,TCIFLUSH);
    
    if(tcsetattr(fd,TCSANOW,&m_uart1)) perror("set attr error");
    if(tcgetattr(fd,&old_cfg)!=0)
    {
        perror("tcgetattr@error");
    }

}









