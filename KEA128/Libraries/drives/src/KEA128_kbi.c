#include "KEA128_kbi.h"
KBI_Type * kbi[2] = KBI_BASES;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      KBI键盘中断初始化
//  @param      chn             选择kbi通道   可选范围 参看KBI_CHn枚举
//  @return     void
//  @since      v2.0
//  Sample usage:               kbi_init(KBI1_P0,IRQ_RISING);		            //通道选择为KBI1_P0，上升沿触发
//								set_irq_priority(KBI1_IRQn,1);					//设置优先级,根据自己的需求设置 可设置范围为 0 - 3
//								enable_irq(KBI1_IRQn);							//打开KBI1_IRQn的中断开关
//								EnableInterrupts;								//打开总的中断开关
//-------------------------------------------------------------------------------------------------------------------
void kbi_init(KBI_CHn chn, TRIG_CFG cfg)
{
    uint8 kbi_x,kbi_n;
    
    kbi_x = KBIx(chn);      //获取模块号
    kbi_n = KBIn(chn);      //获取引脚号
    
    //开启KBI时钟
    if(0 == kbi_x)  SIM->SCGC |= SIM_SCGC_KBI0_MASK;
    else            SIM->SCGC |= SIM_SCGC_KBI1_MASK;
    
    //屏蔽KBI中断
    kbi[kbi_x]->SC &= ~(uint32)KBI_SC_KBIE_MASK;

    //设置触发模式
    if((IRQ_FALLING == cfg) || (IRQ_FALLING_LOW == cfg))
        kbi[kbi_x]->ES &= ~((uint32)1<<kbi_n);
    else
        kbi[kbi_x]->ES |= ((uint32)1<<kbi_n);
    
    //设置上拉
    port_pull((PTX_n)((uint8)(chn)));
    
    //使能KBI引脚
    kbi[kbi_x]->PE |= (1<<kbi_n);
    
    if(0 == kbi_x)  CLEAN_KBI0_FLAG;                         //清除标志位
    else            CLEAN_KBI1_FLAG;                         //清除标志位
    
    //设置触发模式
    if((IRQ_FALLING == cfg) || (IRQ_RISING == cfg))
    {
        kbi[kbi_x]->SC = 0;                                 //边沿触发模式 0：边沿触发   1：电平触发
    }
    else
    {
        kbi[kbi_x]->SC = KBI_SC_KBMOD_MASK;                 //边沿触发模式 0：边沿触发   1：电平触发
    }
    
    
    
    kbi[kbi_x]->SC |= ( 0
                        | KBI_SC_KBIE_MASK    //KBI中断使能
                        | KBI_SC_RSTKBSP_MASK
                        //| KBI_SC_KBMOD_MASK   //边沿触发模式 0：边沿触发   1：电平触发
                        | KBI_SC_KBSPEN_MASK  //使能KBI_SP寄存器
                        );
}




