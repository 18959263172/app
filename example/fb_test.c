#include <fcntl.h> 
#include <sys/ioctl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/mman.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <linux/types.h> 
#include <linux/fb.h> 
#include <linux/videodev2.h>

int main(int argc ,char *argv[]) 
{ 
    int fbfd = 0; 
    struct fb_var_screeninfo vinfo; 
    struct fb_fix_screeninfo finfo; 
    long int screensize = 0; 
    char *fbp = NULL; 
    int x = 0 , y = 0; 
    long int location = 0 ; 
    int sav = 0;

//open framebuffer device 
    fbfd = open("/dev/fb0",O_RDWR); 
    if(!fbfd){ 
            printf("Error:cannot open the framebuffer device!\n"); 
            exit(1); 
        }    
    printf("well you open the framebuffer sucessful!\n"); 
//get the fixed screen information 
    if(ioctl(fbfd,FBIOGET_FSCREENINFO,&finfo)){ 
            printf("Error reading fixed information\n"); 
            exit(2); 
        } 
//get the variable screen information 
    if(ioctl(fbfd,FBIOGET_VSCREENINFO,&vinfo)){ 
            printf("Error reading variable information\n"); 
            exit(3); 
        } 
//show these information 
    printf("vinfo.xres=%d\n",vinfo.xres); 
    printf("vinfo.yres=%d\n",vinfo.yres); 
    printf("vinfo.bit_per_bits=%d\n",vinfo.bits_per_pixel); 
    printf("vinfo.xoffset=%d\n",vinfo.xoffset); 
    printf("vinfo.yoffset=%d\n",vinfo.yoffset); 
    printf("finfo.line_length=%d\n",finfo.line_length);    
    screensize = vinfo.xres*vinfo.yres*vinfo.bits_per_pixel/8;

//map the device to memory 
    fbp = (char *)mmap(0,screensize,PROT_READ|PROT_WRITE,MAP_SHARED,fbfd,0); 
    if((int)fbp == -1){ 
        printf("Error:failed to map framebuffer device to memory\n"); 
        exit(4); 
    } 
    memset(fbp,0,screensize); 
//plot the screen the colour for black 
    for(x=0;x<vinfo.xres;x++) 
        for(y=0;y<vinfo.yres;y++){ 
            location =(x+vinfo.xoffset)*(vinfo.bits_per_pixel/8)+(y+vinfo.yoffset)*finfo.line_length; //scan per lines
            *(fbp+location)=0xff; 
            *(fbp+location+1)=0x00; 
            }    
    sleep(2); 
    for(x=0;x<vinfo.xres;x++) 
        for(y=0;y<vinfo.yres;y++){ 
            location =(x+vinfo.xoffset)*(vinfo.bits_per_pixel/8)+(y+vinfo.yoffset)*finfo.line_length; //scan per lines
            *(fbp+location)=0x00; 
            *(fbp+location+1)=0xff; 
            }    
            sleep(2); 
    for(x=0;x<vinfo.xres;x++) 
        for(y=0;y<vinfo.yres;y++){ 
            location =(x+vinfo.xoffset)*(vinfo.bits_per_pixel/8)+(y+vinfo.yoffset)*finfo.line_length; //scan per lines
            *(fbp+location)=0x00; 
            *(fbp+location+1)=0x00; 
            *(fbp+location+2)=0xff; 
            }    
//release the memory 
    munmap(fbp,screensize); 
    close(fbfd); 
    return 0; 
}	
