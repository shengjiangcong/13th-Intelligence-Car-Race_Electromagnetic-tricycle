#ifndef _KEA128_pit_h
#define _KEA128_pit_h
#include "misc.h"
#include "common.h"
#include "SKEAZ1284.h"
#include "KEA128_port_cfg.h"
//定义PIT模块号
typedef enum
{
    pit0,
    pit1,
} PITn;

#define     PIT_FlAG_CLR(PITn)          PIT->CHANNEL[PITn].TFLG |= PIT_TFLG_TIF_MASK        //清中断标志（写1 清空标志位）

void    pit_init(PITn pitn, uint32 cnt);
void    pit_delay(PITn pitn, uint32 cnt);
void    pit_time_start(PITn pitn);
uint32  pit_time_get(PITn pitn);
void    pit_close(PITn pitn);

//------------------------------------以下代码用于PIT中断------------------------------------
#define     pit_init_ms(PITn_e,ms)          pit_init(PITn_e,ms * bus_clk_khz);                  //初始化PITn，并设置定时时间(单位为 ms)
#define     pit_init_us(PITn_e,us)          pit_init(PITn_e,us * bus_clk_khz/1000);             //初始化PITn，并设置定时时间(单位为 us)
#define     pit_init_ns(PITn_e,ns)          pit_init(PITn_e,ns * bus_clk_khz/1000000);          //初始化PITn，并设置定时时间(单位为 ns)


//------------------------------------以下代码用于PIT延时------------------------------------
#define     pit_delay_ms(PITn_e,ms)          pit_delay(PITn_e,ms * bus_clk_khz);                //PIT延时 ms
#define     pit_delay_us(PITn_e,us)          pit_delay(PITn_e,us * bus_clk_khz/1000);           //PIT延时 us
#define     pit_delay_ns(PITn_e,ns)          pit_delay(PITn_e,ns * bus_clk_khz/1000000);        //PIT延时 ns(40M总线频率时最小单位为25ns)


#endif
