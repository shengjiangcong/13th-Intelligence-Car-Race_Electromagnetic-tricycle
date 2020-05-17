#include "init.h"
#include "isr.h"
#define CoderDelay 10
/*
  adc_init(ADC0_SE4);//B0
  adc_init(ADC0_SE5);//B1
  adc_init(ADC0_SE6);//B2
  adc_init(ADC0_SE7);//B3
  adc_init(ADC0_SE12);//F4
  adc_init(ADC0_SE13);//F5
  adc_init(ADC0_SE14);//F6
  adc_init(ADC0_SE15);//F7
*/

//编码器指针获取（内部调用）
 unsigned int encoder_get(unsigned char select)
{
  unsigned char k;
  unsigned int dat1=0;
  if(select==0) 
  {
    CSnR0;
    delay_us(CoderDelay);  
    for(k=0;k<10;k++)
    { 
      CLKR0;
      delay_us(CoderDelay);
      CLKR1;
      delay_us(CoderDelay);
      dat1=(dat1<<1)+DATER;
    }  
    for(k=0;k<6;k++)
    {
      CLKR0;
      delay_us(CoderDelay);
      CLKR1;
      delay_us(CoderDelay);
    }
    CSnR1;
  }
  else 
  {
    CSnL0;
    delay_us(CoderDelay);  
    for(k=0;k<10;k++)
    {
      CLKL0;
      delay_us(CoderDelay);
      CLKL1;
      delay_us(CoderDelay);
      dat1=(dat1<<1)+DATEL;
    }  
    for(k=0;k<6;k++)
    {
      CLKL0;
      delay_us(CoderDelay);
      CLKL1;
      delay_us(CoderDelay);
    }     
    CSnL1;
  }
  return dat1;
}

//返回当前速度值
 int16 Speed_Get(unsigned char select)
{
  static int16 L_num[2]={0},N_num[2]={0} ;  //存放速度指针数据（内部调用）
  int16 V;
  L_num[select]=N_num[select]; //上传上次位移数据
  N_num[select]=encoder_get(select);  //读取当前位移数据 
  V = (N_num[select]-L_num[select]);  
  if(V>512) 
   V = V-1023;
  if(V<-512)
   V = V+1023;
  if(select==0) V=-1*V;
  return V;
}

void delay_us(unsigned int delay)
{
	while(delay--)
	{
		asm("NOP");
	}
}





void sys_init(void)
{ 
  gpio_init (E5,GPO,0);//蜂鸣器
  
  gpio_init (E4,GPI,1);//干簧管
  
  //gpio_init (I3,GPI,0);
  
  FLASH_Init();//FLASH初始化
 
  ///////////////按键///////////
  gpio_init (H6,GPI,0);//上
  gpio_init (D0,GPI,0);//下
  gpio_init (H7,GPI,0);//左
  gpio_init (G1,GPI,0);//右
  gpio_init (G3,GPI,0);//按下
  
  ///////////adc口/////////////
  /*adc_init(ADC0_SE4);//B0
  adc_init(ADC0_SE5);//B1
  adc_init(ADC0_SE7);//F5
  adc_init(ADC0_SE15);//F7*/
  
  adc_init(ADC0_SE4);//B0
  adc_init(ADC0_SE5);//B1
  adc_init(ADC0_SE6);//B2
  adc_init(ADC0_SE7);//B3
  adc_init(ADC0_SE12);//F4
  adc_init(ADC0_SE13);//F5
  adc_init(ADC0_SE14);//F6
  adc_init(ADC0_SE15);//F7
  
  OLED_Init();//显示屏
  
  uart_init(DEBUG_PORT,DEBUG_BAUD);//初始化蓝牙
  
  ftm_pwm_init(ftm2,ftm_ch0,17000,0);//PWM0 PTH0左正zuofan
  ftm_pwm_init(ftm2,ftm_ch1,17000,0);//PWM1 PTH1左反youfan
  ftm_pwm_init(ftm2,ftm_ch2,17000,0);//PWM0 PTB4右正youzhen
  ftm_pwm_init(ftm2,ftm_ch3,17000,0);//PWM1 PTB5右反zupozhen
  
  gpio_init(H5,GPI,1);//输入   旋编初始化
  gpio_init(H2,GPO,1);//输出
  gpio_init(E7,GPO,1);//输出
  gpio_init(C7,GPI,1);//输入
  gpio_init(A0,GPO,1);//输出
  gpio_init(A1,GPO,1);//输出
  
  Speed_Get(0);
  Speed_Get(1);
  Speed_Get(0);
  Speed_Get(1);
  
  InitMPU6050();//陀螺仪
  
  systick_delay_ms(200);
  
  pit_init(pit0,4);//4ms中断
  set_irq_priority(PIT_CH0_IRQn,1);//设置优先级1
  enable_irq(PIT_CH0_IRQn);//使能中断

  welcome();
  
  bisai       =    conf[SpeedSelect][1 ];//105-120
  SetSpeedMax =    conf[SpeedSelect][2 ];//110-120
  PoSpd       =    conf[SpeedSelect][3 ];
  anncnt[0]   =    conf[SpeedSelect][4 ];
  anncnt[1]   =    conf[SpeedSelect][5 ];
  anncnt[2]   =    conf[SpeedSelect][6 ];
  anncnt[3]   =    conf[SpeedSelect][7 ];
  anncnt[4]   =    conf[SpeedSelect][8 ];
  XieKp       =    conf[SpeedSelect][9 ];
  MidKp       =    conf[SpeedSelect][10];
  AdVKp  	  =    conf[SpeedSelect][11];
  tttsim      =    conf[SpeedSelect][12];//70
  ttttim      =    conf[SpeedSelect][13]; //220
  tttbim      =    conf[SpeedSelect][14];//70
  AnnLet      =    conf[SpeedSelect][15];
  AnnRit      =    conf[SpeedSelect][16];
  Annmb       =    conf[SpeedSelect][17];
  PoHuan      =    conf[SpeedSelect][18];//1是防误判
  shizibug    =    conf[SpeedSelect][19];//0，1是颠簸接十字bug时使用      
  kpcha2      =    conf[SpeedSelect][20];//1为检测终点线
  Endtim      =    conf[SpeedSelect][21];//延时检测干簧管
  RunTim      =    conf[SpeedSelect][22];//时间
  lowtim1     =    conf[SpeedSelect][23];//减速时间
  lowtim2     =    conf[SpeedSelect][24];//减速时间
  aa          =    conf[SpeedSelect][25];//wandaojiansu
  kp          =    conf[SpeedSelect][26];
  kd          =    conf[SpeedSelect][27];
  njnutim2    =    conf[SpeedSelect][28];
  njnutim1    =    conf[SpeedSelect][29];
 /* kp          =    conf[SpeedSelect][1 ];100
  kd          =    conf[SpeedSelect][2 ];110
  Endtime     =    conf[SpeedSelect][3 ];
  SetSpeedMax =    conf[SpeedSelect][4 ];280
  SpdKp       =    conf[SpeedSelect][5 ];190
  SpdKi       =    conf[SpeedSelect][6 ];5
  AnnKp       =    conf[SpeedSelect][7 ];
  AnnKd       =    conf[SpeedSelect][8 ];21
  Vkp         =    conf[SpeedSelect][9 ];160
  Vkd         =    conf[SpeedSelect][10];140
  KFC         =    conf[SpeedSelect][11]; 50
  ttttim      =    conf[SpeedSelect][12];38
  SpdAnnOut   =    conf[SpeedSelect][13];
  aa          =    conf[SpeedSelect][14];13
  bb          =    conf[SpeedSelect][15];3
  anncnt1     =    conf[SpeedSelect][16];
  anncnt2     =    conf[SpeedSelect][17];
  anncnt3     =    conf[SpeedSelect][18];
  anncnt4     =    conf[SpeedSelect][19];
  anncnt5     =    conf[SpeedSelect][20];
  moluntai    =    conf[SpeedSelect][21];*/
}
