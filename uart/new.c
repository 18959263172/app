////串口API读写测试程序
///athor:zcy
//2014.3.4
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string>
#include"uart.h"
#include<vector>
#include"terminal.h"

//#ifdef sb
using namespace std;

int main()
{
    CSerial m_uart1;
    vector<string> vect;
        //getFiles("/dev",vect);
    show_file();
    m_uart1.init_serial("/dev/ttyPS0");
    m_uart1.serial_write(16,"welcome wece");
    getchar();
    
    return 0;
}
//#endif




