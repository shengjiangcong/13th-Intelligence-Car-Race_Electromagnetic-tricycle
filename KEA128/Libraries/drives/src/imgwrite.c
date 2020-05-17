#include "imgwrite.h"
/******************** (C) COPYRIGHT 2014 njnu Precursors ********************
 * 文件名       ：imgwrite.c
 * 描述         : SD卡写函数
 *              ：BusClock=120MHZ; 
 * 实验平台     ：Precursors board
*****************************************************************************/
//参数写入D_flash
void flashconf_write(void)
{
  int16 i=0;
  FLASH_EraseSector(FlashSector);  //擦除最后一个扇区
  /*for(i=0;i<ConfigNum;i++)
  {
    FLASH_WriteSector(FlashSector,(const uint8 *)(conf[0][i]),2,2*i); 
  }*/
  FLASH_WriteSector(FlashSector,(const uint8 *)conf[0],ConfigNum*2,0);
  
}

//从D_flash读取参数
void flashconf_read(void)
{
  int16 i=0;
  uint32 temp=0;
  for(i=0;i<ConfigNum;i++)
  {
    temp=flash_read(FlashSector,2*i,uint16);
    conf[0][i]=temp;
  }
}
