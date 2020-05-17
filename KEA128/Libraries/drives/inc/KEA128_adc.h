#ifndef _KEA128_adc_h
#define _KEA128_adc_h

#include "misc.h"
#include "common.h"
#include "SKEAZ1284.h"
#include "KEA128_port_cfg.h"

typedef enum
{
    ADC0_SE0=0,  //A0
    ADC0_SE1,    //A1
    ADC0_SE2,    //A6
    ADC0_SE3,    //A7
    ADC0_SE4,    //B0
    ADC0_SE5,    //B1
    ADC0_SE6,    //B2
    ADC0_SE7,    //B3
    ADC0_SE8,    //C0
    ADC0_SE9,    //C1
    ADC0_SE10,   //C2
    ADC0_SE11,   //C3
    ADC0_SE12,   //F4
    ADC0_SE13,   //F5
    ADC0_SE14,   //F6
    ADC0_SE15    //F7
} ADCn_Ch;



//精度位数
typedef enum ADC_nbit
{
    ADC_8bit   = 0x00,
    ADC_10bit  = 0x01,
    ADC_12bit  = 0x02
} ADC_nbit;


void adc_init(ADCn_Ch adcn_ch);
uint16 adc_once(ADCn_Ch adcn_ch, ADC_nbit bit);
void adc_stop(void);
void ring_control(void);
uint16 ad_ave(ADCn_Ch adcn_ch, ADC_nbit bit,uint8 N);
void Read_ADC(void);
void ErrorGet(void);
void AnnJudge(void);
void AnnSmall(void);


extern float kp;
extern float kd;
extern float kp1;

extern int16 SpdError[8];
extern int AnnularFlag;
extern int32 cnt1;
extern int32 cnt2;
extern int32 cnt3;
extern int32 cntout1;
extern int32 cntout2;
extern int32 cntout3;
extern int   ringflag;
extern float g_fDirectionError[4];
extern float g_fDirectionError_dot[4];
extern int16 g_ValueOfAD[7];
extern int16 g_ValueOfADFilter[6];
extern int16 ADOld[5];
extern int16 KFC;
extern int16 ttttim;
extern int32 angle4ms;
extern int64 anglealltime;
extern int8 aa;
extern int8 bb;
extern int shiziflag;
extern int zhidaoflag;
extern int AnnularWhat; 
extern float g_fDirectionError_dotfabs[2];
extern int anncnt[10];
extern int AnnularCnt;
extern int kpcha;
extern int kpcha2;
extern int huansize;
extern int32   AnnLet;
extern int32   AnnRit;
extern int32 Annmb;
extern int32   angle4mss;
extern int64   anglealltimeV;
extern int16 XieKp;
extern int16 MidKp;
extern int16 AdVKp;
extern int16 tttsim;
extern int16 tttbim;
extern int ganhuangguan[5];
extern int shizibug;
extern int16 XieLv[5];
extern int32 njnutim2;
extern int32 njnutim1;
#endif
