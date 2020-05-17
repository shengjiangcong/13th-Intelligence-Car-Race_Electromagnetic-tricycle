#ifndef _KEA128_flash_h
#define _KEA128_flash_h

#include "misc.h"
#include "common.h"
#include "SKEAZ1284.h"
#include "KEA128_port_cfg.h"

#define FTF    				    FTMRE

#define SECTOR_SIZE     		(512)
#define FLASH_SECTOR_NUM        (256)                   //扇区数
#define FLASH_ALIGN_ADDR        4                       //地址对齐整数倍
typedef uint32                  FLASH_WRITE_TYPE;       //flash_write 函数写入 的数据类型




//-------------------------------------------------------------------------------------------------------------------
//  @brief      使用宏定义对flash进行数据读取
//  @param      SectorNum 		需要写入的扇区编号
//  @param      offset	 		地址偏移
//  @param      type		 	读取的数据类型
//  @return     				返回给定地址的数据
//  @since      v1.0
//  Sample usage:               flash_read(20,0,uint32);//读取20号扇区偏移0数据类型为uint32
//-------------------------------------------------------------------------------------------------------------------
#define     flash_read(SectorNum,offset,type)        (*(type *)((uint32)(((SectorNum)*SECTOR_SIZE) + (offset))))


void FLASH_Init(void);
uint32 FLASH_GetSectorSize(void);
uint8 FLASH_EraseSector(uint32 SectorNum);
uint8 FLASH_WriteSector(uint32 SectorNum, const uint8 *buf, uint32 len, uint32 offset);



#endif
