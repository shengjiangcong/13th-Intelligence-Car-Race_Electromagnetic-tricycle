#include "misc.h"
//-------------------------------------------------------------------------------------------------------------------
//  @brief      设置中断向量表地址
//  @param      vtor            新的中断向量表地址
//  @return     void
//  @since      v1.0
//  Sample usage:               write_vtor(0x1fff0000);;  
//-------------------------------------------------------------------------------------------------------------------
void write_vtor (int vtor)
{
    // Write the VTOR with the new value
    SCB->VTOR = vtor;
}


