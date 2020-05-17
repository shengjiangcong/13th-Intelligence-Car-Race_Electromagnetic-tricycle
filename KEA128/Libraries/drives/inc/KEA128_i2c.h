#ifndef _KEA128_i2c_h
#define _KEA128_i2c_h
#include "misc.h"
#include "common.h"
#include "SKEAZ1284.h"
#include "KEA128_port_cfg.h"
#include "stdlib.h"

typedef enum
{
    i2c0  = 0,
    i2c1  = 1
} I2Cn_e;

typedef enum MSmode
{
    MWSR =   0x00,  // 主机写模式  
    MRSW =   0x01   // 主机读模式  
} MSmode;

//仅支持 I2C主机模式
extern uint32  i2c_init(I2Cn_e i2cn, uint32 baud);                               //初始化I2C
extern void    i2c_write_reg(I2Cn_e, uint8 SlaveID, uint8 reg, uint8 Data);      //写入数据到寄存器
extern uint8   i2c_read_reg (I2Cn_e, uint8 SlaveID, uint8 reg);                  //读取寄存器的数据
extern uint8   i2c_read_reg_bytes(I2Cn_e i2cn, uint8 SlaveID, uint8 reg, uint8 num, uint8 * addr);







#endif
