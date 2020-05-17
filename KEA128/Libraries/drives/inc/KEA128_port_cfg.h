#ifndef _KEA128_port_cfg_h
#define _KEA128_port_cfg_h
#define StartTime 220
//-----------------------------------  IRQ  -----------------------------------
//      模块通道        端口      可选范围                   建议
#define IRQ_PIN         I5        //A5 I0 I1 I2 I3 I4 I5 I6  A5不要用（与复位按键冲突）  

//-----------------------------------  ADC  -----------------------------------
#define AD1 ADC0_SE5
#define AD2	ADC0_SE15
#define AD3 ADC0_SE4
#define AD4	ADC0_SE13
#define AD5	ADC0_SE6
#define AD6	ADC0_SE12
#define AD7	ADC0_SE7
//-----------------------------------  UART  -----------------------------------

//      模块通道        端口      可选范围                建议
//在切换引脚时，务必成对切换。编号相邻得两个引脚为一对
#define UART0_RX_PIN    A2        //A2 B0
#define UART0_TX_PIN    A3        //A3 B1
                                       
#define UART1_RX_PIN    F2        //C6 F2
#define UART1_TX_PIN    F3        //C7 F3
                                       
#define UART2_RX_PIN    I0        //D6 I0
#define UART2_TX_PIN    I1        //D7 I1

//-----------------------------------  FTM  -----------------------------------

//      模块通道        端口      可选范围                建议
#define FTM0_CH0_PIN    A0        //B2 A0
#define FTM0_CH1_PIN    A1        //B3 A1

//      模块通道        端口      可选范围                建议
#define FTM1_CH0_PIN    H2        //H2 C4				  C4不要用（与SWD_CLK冲突）
#define FTM1_CH1_PIN    C5        //E7 C5

//      模块通道        端口      可选范围                建议
#define FTM2_CH0_PIN    C0        //C0  H0 F0              
#define FTM2_CH1_PIN    C1        //C1  H1 F1  
#define FTM2_CH2_PIN    C2        //C2  G4 D0  
#define FTM2_CH3_PIN    C3        //C3  G5 D1
#define FTM2_CH4_PIN    B4        //B4  G6  
#define FTM2_CH5_PIN    B5        //B5  G7              


//外部计数模块通道      端口      可选范围                建议
#define FTM0_COUNT_PIN  E0        //E7 A5  E0             A5不要用（与复位按键冲突）                
                                           
#define FTM1_COUNT_PIN  E7        //E0 A5  E7             A5不要用（与复位按键冲突）
                                           
#define FTM2_COUNT_PIN  A5        //E0 E7  A5             A5不要用（与复位按键冲突）


//-----------------------------------  I2C  -----------------------------------
//在切换引脚时，务必成对切换。编号相邻得两个引脚为一对
//      模块通道        端口      可选范围                建议
#define I2C0_SCL_PIN    B7        //A3 B7
#define I2C0_SDA_PIN    B6        //A2 B6
                                       
#define I2C1_SCL_PIN    H4        //E1 H4
#define I2C1_SDA_PIN    H3        //E0 H3


//-----------------------------------  SPI  -----------------------------------
//      模块通道        端口      可选范围              建议
//在切换引脚时，务必成对切换。编号相邻得四个引脚为一对
#define SPI0_SCK_PIN    B2       //E0 B2
#define SPI0_SOUT_PIN   B3       //E1 B3
#define SPI0_SIN_PIN    B4       //E2 B4                        
#define SPI0_PCS0_PIN   B5       //E3 B5
                                      
                                      
#define SPI1_SCK_PIN    D0       //G4 D0
#define SPI1_SOUT_PIN   D1       //G5 D1
#define SPI1_SIN_PIN    D2       //G6 D2
#define SPI1_PCS0_PIN   D3       //G7 D3


//-----------------------------------  CAN  -----------------------------------
//在切换引脚时，务必成对切换。编号相邻得两个引脚为一对   H2与E7为一对
#define CAN0_TX_PIN     C7       //E7 C7
#define CAN0_RX_PIN     C6       //H2 C6



#endif
