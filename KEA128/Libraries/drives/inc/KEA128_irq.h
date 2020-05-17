#ifndef _KEA128_irq_h
#define _KEA128_irq_h
#include "misc.h"
#include "common.h"
#include "SKEAZ1284.h"
#include "KEA128_port_cfg.h"
//中断标志位清除
#define CLEAR_IRQ_FLAG   (IRQ->SC |= IRQ_SC_IRQACK_MASK)



void irq_init(void);


#endif
