//access from ARM Running linux
#define BCM2708_PERI_BASE	0x3F000000//s macro contains physical adress value at which the peripheral registers start
#define GPIO_BASE 	 (BCM2708_PERI_BASE + 0x200000) //GPIO controller

#include <stdio.h>//standard in/out put
#include <stdlib.h>//memory allocation
#include <fcntl.h>//file control. opening, retriving and changing the permission of file, lock edit...
#include <sys/mman.h>// support for either the memory mapped files, process memory locking or shares memory objects options
#include <unistd.h>//codes entry point to various constants type and function declarations that comprise thr poxi operating system api

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

int mem_fd;
void *gpio_map;

// I/O access
volatile unsigned *gpio;// volitile an indication to the compiler that this value may change in waysthat the program dosn't expect.

//gpio setup macros. always use inp_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
                   //regidter addrrss          //GPFSEL bits
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))//sets pin g as an input
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
//can set pin to function 0,1,...
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  // set bits are 1 ignors bits which are 0
#define GPIO_CLR *(gpio+10) // set bits are 1 ignors bits which are 0

#define GET_GPIO(g) (*(gpio+13)&(1<<g))

#define GPIO_PULL(g)  *(gpio+37)
#define GPIO_PULLCLK0 *(gpio+38)

void  setup_io();

int main(int argc, char **argv){
    int g, rep;
    printf("IN THE MAIN\n");
    setup_io();
    printf("after thr setup\n");
    //pin 7
    INP_GPIO(4);
    OUT_GPIO(4);
    //pin  13
    INP_GPIO(27);
    OUT_GPIO(27);
    //pin 17
    INP_GPIO(22);
    OUT_GPIO(22);




    for(int i=0;i<=3;i = i+1){
        
        GPIO_SET = 1<<4;
        printf("blink\n");
        sleep(1.5);
        GPIO_CLR = 1<<4;
        sleep(1);

        GPIO_SET = 1<<27;
        printf("blink\n");
        sleep(1.5);
        GPIO_CLR = 1<<27;
        sleep(1);
        
        GPIO_SET = 1<<22;
        printf("blink\n");
        sleep(1.5);
        GPIO_CLR = 1<<22;
        sleep(1);
        
    }

    printf("ok done\n");

    return 0;   
}

void setup_io(){
    //open /dev/mem
    if((mem_fd = open("/dev/mem",O_RDWR|O_SYNC)) < 0){
        printf("can't open/mem \n");
        exit(-1);
    }
    
    //mmap GPIO
    gpio_map = mmap(
        NULL,                  //Any address in our space will do 
        BLOCK_SIZE,            //map length
        PROT_READ|PROT_WRITE,  //Enable reading & writting to mapped memory 
        MAP_SHARED,            //Shared with other processes
        mem_fd,                //File to map
        GPIO_BASE              //offset to GPIO peripheral
    );

    close(mem_fd);
    
    if(gpio_map == MAP_FAILED){
        printf("mmap error %d\n", (int)gpio_map);//errno also set
        exit(-1);
    }

    gpio = (volatile unsigned *)gpio_map;
}