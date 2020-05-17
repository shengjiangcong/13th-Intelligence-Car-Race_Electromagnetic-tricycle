#ifndef _KEA128_uart_h
#define _KEA128_uart_h
#include "misc.h"
#include "common.h"
#include "SKEAZ1284.h"
#include "KEA128_port_cfg.h"
#include "stdio.h"




typedef enum
{
    uart0,
    uart1,
    uart2,
} UARTn;


#define DEBUG_PORT  uart2
#define DEBUG_BAUD  115200



uint32 uart_init(UARTn uartn, uint32 baud);
void uart_putchar (UARTn uartn, uint8 ch);
void uart_putbuff (UARTn uartn, uint8 *buff, uint32 len);
void uart_putstr (UARTn uartn, const uint8 *str);
void uart_getchar (UARTn uartn, uint8 *ch);
void uart_rx_irq_en(UARTn uartn);
void uart_txc_irq_en(UARTn uartn);
void uart_rx_irq_dis(UARTn uartn);
void uart_txc_irq_dis(UARTn uartn);


#endif
