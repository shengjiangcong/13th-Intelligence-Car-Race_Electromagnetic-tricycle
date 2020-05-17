#include "KEA128_port.h"
#define PTX(PTX_n)  (PTX_n>>5)  //获取模块号 PTX_n/32
#define PTn(PTX_n)  (PTX_n&0x1f)//获取引脚号 PTX_n%32

//-------------------------------------------------------------------------------------------------------------------
//  @brief      IO上拉
//  @param      ptx_n           选择端口
//  @return     void
//  @since      v2.0
//  Sample usage:               port_pull(E0);			//E0 上拉电阻开启
//-------------------------------------------------------------------------------------------------------------------
void port_pull(PTX_n ptx_n)
{
    uint8 ptx,ptn;
    ptx = PTX(ptx_n);//记录模块号    //A,B......
    ptn = PTn(ptx_n);//记录引脚号    //0,1,2,3......
    
    switch(ptx)
    {
        case 0:
        {
            PORT->PUE0 |= (uint32)(1<<ptn);
        }break;
        
        case 1:
        {
            PORT->PUE1 |= (uint32)(1<<ptn);
        }break;
        
        case 2:
        {
            PORT->PUE2 |= (uint32)(1<<ptn);
        }break;
    }
}

