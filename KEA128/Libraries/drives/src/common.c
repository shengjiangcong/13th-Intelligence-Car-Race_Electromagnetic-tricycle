#include "common.h"
#include "system_SKEAZ1284.h"

#define EX_REF_CLK  16000 //(定义外部参考时钟为16000KHZ)
uint32 ics_clk_khz;
uint32 ftm_clk_khz;
uint32 core_clk_khz;
uint32 bus_clk_khz;



void get_clk(void)
{
    uint16 prescaler_factor[]={1,2,4,8,16,32,64,128,256,512,1024};
    
    if(2 == KEA128_CLOCK)   //内部时钟
    {
        ics_clk_khz = 48000;
        ftm_clk_khz = 48000;
        core_clk_khz = 48000;
        bus_clk_khz = 24000; 
    }
    else                    //外部时钟
    {
        ics_clk_khz  = EX_REF_CLK * 1280 ;
        ics_clk_khz = ics_clk_khz / prescaler_factor[((ICS->C1&ICS_C1_RDIV_MASK) >> ICS_C1_RDIV_SHIFT) + 5];    //计算FLL输出频率
        ics_clk_khz = ics_clk_khz / prescaler_factor[(ICS->C2&ICS_C2_BDIV_MASK) >> ICS_C2_BDIV_SHIFT];          //计算ICSCLKOUT
        
        core_clk_khz = ics_clk_khz  / (((SIM->CLKDIV&SIM_CLKDIV_OUTDIV1_MASK) >> SIM_CLKDIV_OUTDIV1_SHIFT) + 1);
        bus_clk_khz  = core_clk_khz / (((SIM->CLKDIV&SIM_CLKDIV_OUTDIV2_MASK) >> SIM_CLKDIV_OUTDIV2_SHIFT) + 1);
        ftm_clk_khz  = ics_clk_khz  / (((SIM->CLKDIV&SIM_CLKDIV_OUTDIV3_MASK) >> SIM_CLKDIV_OUTDIV3_SHIFT) + 1);
    }
}
