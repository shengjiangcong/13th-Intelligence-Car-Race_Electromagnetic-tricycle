#ifndef _misc_h
#define _misc_h
#include "common.h"
void write_vtor (int);                                              //设置中断向量表的地址                                                                                                                                   
#define enable_irq(irq)                 NVIC_EnableIRQ(irq)         //使能IRQ
#define disable_irq(irq)                NVIC_DisableIRQ(irq)        //禁止IRQ
#define set_irq_priority(irq,pri0)      NVIC_SetPriority(irq,pri0)  //设置优先级，优先级范围0-3                                                                                                                                       
#define EnableInterrupts                __enable_irq()              //使能全部中断
#define DisableInterrupts               __disable_irq()             //禁止全部中断
#endif
