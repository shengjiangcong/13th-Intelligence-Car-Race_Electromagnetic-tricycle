#ifndef __MAIN_H   
#define __MAIN_H 
#include "common.h"
#define ConfigNum       35            //最大可调参数个数
#define FlashSector     255
#define Gyrorate        0.1775f 
extern uint8      imgmode;                  //模式选择
extern uint8      SpeedSelect;              //速度选择
extern uint32  TimeRunCount;
extern uint16  adc[8];
extern int16   conf[3][ConfigNum];
extern uint8      SDOrNormFlag;
extern int32   GyroX,GyroXo,GyroY,GyroYo; 
extern int32   Gyropitchfloat,Gyrorollfloat;                //直立陀螺仪零点,转向陀螺仪零点
extern int32   Anglefloat;   
extern int32   Acc_Z;
#endif  //__INIT_H