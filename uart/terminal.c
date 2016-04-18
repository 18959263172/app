#include"terminal.h"
#include <unistd.h>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include"uart.h"
#include <sys/types.h>
#include <regex.h>
#include<errno.h>
/*
  @brief run a terminal
*/
void terminal::terminal_run()
{


}
/*
  @brief 
*/
void process_thread()
{
    
}
/*
  @brief terminal initialization
*/
void terminal::terminal_init()
{
    printf("enter terminal initialization!!! \r\n");
    printf("select a serial a port\r\n");
    m_uart1.init_serial("/dev");
}
/*
  @brief get file list
*/
void getFiles(char * dir, vector<string>& files)
{
    DIR *dp;
    int cflags=REG_EXTENDED;
    regex_t reg;
    int status;
    struct dirent *entry;
    struct stat statbuf;
    regmatch_t pmatch[1];
    const size_t nmatch=1;
    const char *pattern="ttyPS*";
    int i=0;
    char filename[2048];
        //chdir("..");
        //chdir(".");
    regcomp(&reg,pattern,cflags);
    if((dp = opendir(dir)) == NULL) 
    {
        fprintf(stderr,"%s\r\n", dir);
        return;
    }
        //chdir(dir);
        //The recursive traversal of the directory tree structure
    while(entry=readdir(dp))
    {
        printf("\r\n%d",i++);
            //printf("%s\n", entry->d_name);  
            //statbuf initialization
        lstat(entry->d_name,&statbuf);
            //printf("%s\n", entry->d_name);
        if(S_ISDIR(statbuf.st_mode)) 
        {
                //if it is a catlog???
            if(strcmp(".",entry->d_name) ==0||strcmp("..",entry->d_name)==0) continue;
                //if it is a catlog,rescan it 
                //getFiles(entry->d_name,files);
        }
        else
        {
            lstat(entry->d_name,&statbuf);
                //printf("%s\n", entry->d_name);
            sprintf(filename,"%s/%s",dir,entry->d_name);
            files.push_back(filename);
        }
    }
    if(errno=EBADF)
    {
        printf("a error open when open file !!!\r\n");
    }
        /*for(int i =0;i <files.size();i++)
          {
          printf("%s \n",files[i].c_str());
          status =regexec(&reg,files[i].c_str(),nmatch,pmatch,0);
          if(status==0)
          {
          printf("%s\r\n",files[i].c_str());
          }
        }*/
        /*
          int size = files.size();
          for(int i =0;i < size;i++)
          {
             printf("%s \n",files[i].c_str());
          }
          chdir("..");
        */
    chdir("..");
    printf("change the directory to /mnt \r\n");
    closedir(dp);
}
/*
  @brief 
*/
int show_file()
{
    vector<string>files;
    int size;
    getFiles("/dev/",files);
    size = files.size();
    printf("the length of vector is %d\r\n",size);
    for(int i =0;i <size;i++)
        printf("%s \n",files[i].c_str());
    
}
/*

 */

