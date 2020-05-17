#ifndef __INIT_H   
#define __INIT_H 
#include "common.h"
#define CLKL0                    gpio_set(H2,0) //H2输出低电平
#define CLKL1                    gpio_set(H2,1) //H2输出高电平
#define CSnL0                    gpio_set(E7,0) //E7输出低电平
#define CSnL1                    gpio_set(E7,1) //E7输出高电平

#define CLKR0                    gpio_set(A0,0)    //A0输出低电平
#define CLKR1                    gpio_set(A0,1)   //A0输出高电平
#define CSnR0                    gpio_set(A1,0)    //A1输出低电平
#define CSnR1                    gpio_set(A1,1)    //A1输出高电平

#define DATEL                   gpio_get(H5)  //读取H5
#define DATER                   gpio_get(C7)  //读取D4

#define ring_on()               gpio_set(E5,1)   //E2输出高电平   
#define ring_off()              gpio_set(E5,0)   //E2输出低电平
void sys_init(void);
void delay_us(unsigned int delay);
int16 Speed_Get(unsigned char select);
#endif  //__INIT_H