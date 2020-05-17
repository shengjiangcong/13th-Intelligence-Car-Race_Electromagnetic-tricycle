#ifndef _KEA128_systick_h
#define _KEA128_systick_h
#include "misc.h"
#include "common.h"
#include "SKEAZ1284.h"
#include "KEA128_port_cfg.h"


void    systick_delay(uint32 time);
void    systick_delay_ms(uint32 ms);
void    systick_timing(uint32 time);
uint32  systick_getval(void);









#endif 
