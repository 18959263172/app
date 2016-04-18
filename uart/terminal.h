#ifndef _TERMINAL_
#define _TERMINAL_
#include<vector>
#include<string>
#include "uart.h"

/*
  @function
  @brief  
*/
using namespace std;
/*
  @brief
  @function
*/
typedef class terminal
{
    CSerial m_uart1;
public:
    void terminal_run();
    
    unsigned char *buff;
    
    void terminal_init();
}TerCtrl;

int show_file();

void getFiles(char * dir, vector<string>& files);

#endif
