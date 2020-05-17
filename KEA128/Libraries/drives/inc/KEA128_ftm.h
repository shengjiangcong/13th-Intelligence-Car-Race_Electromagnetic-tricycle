#ifndef _KEA128_ftm_h
#define _KEA128_ftm_h
#include "common.h"
#include "SKEAZ1284.h"
#include "KEA128_port_cfg.h"
typedef enum
{
    ftm0,
    ftm1,
    ftm2,
} FTMn;


typedef enum
{
    ftm_ch0,
    ftm_ch1,
    ftm_ch2,
    ftm_ch3,
    ftm_ch4,
    ftm_ch5,
    ftm_ch6,
    ftm_ch7,
} FTM_CHn;


//------------------------ PWM ------------------------

#define FTM0_PRECISON 1000u     //定义占空比精度，意思即使把一个周期分成多少分，分多越多这样精度越高，设置占空比的时候duty的范围就是0-FTM0_PRECISON
#define FTM1_PRECISON 1000u     //定义占空比精度，意思即使把一个周期分成多少分，分多越多这样精度越高，设置占空比的时候duty的范围就是0-FTM0_PRECISON
#define FTM2_PRECISON 1000u     //定义占空比精度，意思即使把一个周期分成多少分，分多越多这样精度越高，设置占空比的时候duty的范围就是0-FTM0_PRECISON


void ftm_pwm_init(FTMn ftmn, FTM_CHn ch, uint32 freq, uint32 duty);
void ftm_pwm_duty(FTMn ftmn, FTM_CHn ch, uint32 duty);
void ftm_pwm_freq(FTMn ftmn, uint32 freq) ;
void ftm_count_init(FTMn ftmn);
uint16 ftm_count_get(FTMn ftmn);
void ftm_count_clean(FTMn ftmn);
void SpdGet(void);
void SpdControl(void);
void SpdDuty(void);



extern int16 SpdGetL;
extern int16 SpdGetR;
extern int32 timet;
extern int32 Endtime;
extern int16 Speednow;
extern int32 L_Speednow;
extern int32 R_Speednow;
extern float SpeedControlOutNew;
extern int32 SetSpeedMax;
extern int16 StpFlag;
extern int16 SpdKp;
extern int16 SpdKi;
extern float DeviateInt;
extern int32 DeviateSpeed[2];
extern int16 PoFlag;
extern int16 PoTim;
extern int32 SpdAnnOut;
extern float SpdOutRight;
extern float SpdOutLeft;
extern int16 PoSpd;
extern int32 Endtim;
extern int bisai;
extern int32 RunTim;
extern int32 lowtim1;
extern int32 lowtim2;
extern int   DianBoFlag;
extern int16 DianBoTim;
extern int32 DianBoStop;


#endif
