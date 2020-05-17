#include "KEA128_ftm.h"
#include "KEA128_adc.h"
#include "math.h"
#include "init.h"
#include "isr.h"
int32 L_Speednow=0;
int32 R_Speednow=0;
int16 Speednow=0;
int16 SpdKp=190;
int16 SpdKi=5;
float SpdOutRight=0;
float SpdOutLeft=0;
int32 timet=0;
int32 Endtime=0;
int32 SetSpeed=0;                                       // 速度控制依据的设定速度
int32 SpdAnnOut=0;
int32 SetSpeedMax=0;                                      // 设定速度              （可调参数）
float SpeedControlOutOld=0.0;                           // 增量式速度控制参数 每100ms刷新
float SpeedControlOutNew=0.0;                           // 增量式速度控制参数 每10ms计算
float SpeedControlOut=0.0;                              // 速度输出值
int32 DeviateSpeed[2]={0};
int16 StpFlag=0;
float DeviateIntMax = 0;                             //速度控制积分上限
float DeviateIntMin = 0;                             //速度控制积分下限
float DeviateInt = 0;                                //速度积分
int16 PoFlag=0;
int   DianBoFlag=0;
int16 DianBoTim=0;
int16 PoTim=0;
int16 ChuJieTim=0;
int16 PoSpd=0;
int32 Endtim=0;
int bisai=0;
int32 RunTim=0;
int32 lowtim1=0;
int32 lowtim2=0;
int32 DianBoStop=0;
int8  tttiiimmm=0;


void SpdGet(void)
{		
	   
	
		
	
	
	   
///////////////**************速度设定************////////////////
	
	    SetSpeed=SetSpeedMax;//-fabs(GyroX)/1000.0f*aa;// - aa*10.0f * g_fDirectionError_dotfabs[0]/0.7f-bb*10.0f*(2000-g_ValueOfAD[6])/2000.0f;// + moluntai*(fabs(GyroX))/1000.0f;	
	      if(zhidaoflag==1)
	      SetSpeed=SetSpeedMax+15;
		  if(PoFlag>0&&PoTim<250)
			SetSpeed=PoSpd;
		if(timet>(lowtim1*2.5f+125)&&timet<(lowtim2*2.5f+125))
			SetSpeed=SetSpeedMax-80;
		
		

		if(AnnularWhat==1||AnnularFlag==1||(AnnularFlag==2&&cntout1<40))
		{
			if(huansize==0||huansize==6)
			SetSpeed=235;
			else if(huansize==1||huansize==5)
			SetSpeed=235;	
			else if(huansize==2)
			SetSpeed=180;
			else
			SetSpeed=160;

		}
		if((AnnularFlag==2)&&(cntout1>=40)&&(huansize==0||huansize==6))
			SetSpeed=310;
		if((AnnularFlag==2)&&(cntout1>=40)&&(huansize==1||huansize==5))
			SetSpeed=285;
		if((AnnularFlag==2)&&(cntout1>=40)&&(huansize==2||huansize==4))
			SetSpeed=275;

		if(AnnularFlag==3)
			SetSpeed=SetSpeedMax;
        

///////////////**************速度设定************////////////////	   
	   
        L_Speednow=-Speed_Get(0);
	    R_Speednow=-Speed_Get(1);
	
        Speednow=(int)(L_Speednow+R_Speednow);
	
		if(Speednow>1000)Speednow=1000;
	    if(Speednow<-1000)Speednow=-1000;
	
	    DeviateSpeed[1] = DeviateSpeed[0];
	    DeviateSpeed[0] = SetSpeed - Speednow;                     //计算出速度偏差信号
	    DeviateInt = DeviateInt + DeviateSpeed[0] * SpdKi*0.001;        //积分减少稳态误差
	
	    DeviateIntMax = 800;
	    DeviateIntMin = -800;
	    if (DeviateInt > DeviateIntMax)
		    DeviateInt = DeviateIntMax;
	    else if (DeviateInt < DeviateIntMin)
		    DeviateInt = DeviateIntMin;
	
	    SpeedControlOutOld=SpeedControlOutNew;
	    SpeedControlOutNew =  SetSpeed+SpdKp*DeviateSpeed[0]*0.01 + DeviateInt;    //PI计算本次速度控制量
		/*if(AnnularFlag==0&&AnnularWhat==0)
		{
		if( Speednow>(SetSpeedMax+30))
			SpeedControlOutNew=0;
		}*/
		if( Speednow>(SetSpeed+30))
			SpeedControlOutNew=0;
		/*if(DianBoStop==1)
		{
		if(PoFlag==1&&PoTim<70)
			SpeedControlOutNew=(PoTim-70)*8;
		}*/
		/*if(PoTim<105&&PoFlag==1)
		    SpeedControlOutNew=0;*/
		if(PoFlag==1&&PoTim<=njnutim1&&AnnularFlag==0&&AnnularWhat==0)
		{
			SpeedControlOutNew = (PoTim-njnutim1)*aa;
			if(SpeedControlOutNew>PoSpd)
				SpeedControlOutNew=PoSpd;
		}
		else if(PoFlag==2&&PoTim<=njnutim1&&AnnularFlag==0&&AnnularWhat==0)
		{
			SpeedControlOutNew = 0;
		}	
		
		if(timet<StartTime)
			SpeedControlOutNew=(SpeedControlOutNew<900?900:SpeedControlOutNew);
}

void SpdControl(void)
{	
	
	if(kpcha2==1)
	{
	if(ganhuangguan[0]==0&&ganhuangguan[1]==0&&ganhuangguan[2]==0)
		StpFlag=2;
	if(StpFlag==2)
		tttiiimmm++;
	if(tttiiimmm==12)
		StpFlag=1;
	if((g_ValueOfAD[0]<40&&g_ValueOfAD[1]<30))
		StpFlag=1;

	}

			/*if(AnnularFlag==2&&fabs(anglealltime)>(anncnt[5]*100)&&(huansize==4||huansize==2))
StpFlag=1;*/
			/*if(AnnularFlag==3&&(huansize==4||huansize==2))
StpFlag=1;*/
			/*if(AnnularFlag==2)
StpFlag=1;*/
	/*if(timet>500)
	{
	if(gpio_get(E4)==0)
	    StpFlag=1;
	}*/
	/*if(AnnularCnt==1)
		StpFlag=1;*/
	/*if(AnnularFlag==3)
		StpFlag=1;*/
	/*if(huansize==2&&AnnularFlag==2&&fabs(anglealltime)>10000)
	    StpFlag=1;*/
	/*if(AnnularFlag==2&&fabs(anglealltime)>10300&&(huansize==0||huansize==6))
		StpFlag=1;*/
	

	if(StpFlag==1)
	{
	ChuJieTim++;
	if(ChuJieTim>200)
		ChuJieTim=200;
	}

   if(SpdError[7]>0)
	{
    SpdOutLeft=SpeedControlOutNew+1*SpdError[7];
	SpdOutRight=SpeedControlOutNew-SpdError[7];
	
	}
	else
	{
	SpdOutLeft=SpeedControlOutNew+SpdError[7];
	SpdOutRight=SpeedControlOutNew-1*SpdError[7];
	}
	
	/*if(L_Speednow<80&&SpdOutLeft<=0)SpdOutLeft=1;
	if(R_Speednow<80&&SpdOutRight<=0)SpdOutRight=1;*/
	
	
    
  //////////////////死区//////////////////// 
    if(SpdOutLeft>0)SpdOutLeft+=60;
    if(SpdOutRight>0)SpdOutRight+=30;
	if(SpdOutLeft<0)SpdOutLeft=SpdOutLeft-60;
	if(SpdOutRight<0)SpdOutRight=SpdOutRight-30;
  //////////////////死区////////////////////  
	
	if(bisai==1)
		Endtime=RunTim;
	else
		Endtime=500;
	if(StpFlag==1&&ChuJieTim<125&&timet<(Endtime*10/4+250))
	 {
	SpdOutLeft=-400;
	SpdOutRight=-400;
	 }
	else if((StpFlag==1&&ChuJieTim>=125)||timet<=125||timet>=(Endtime*10/4+250))
	{
	SpdOutLeft=0;
	SpdOutRight=0;
	}
	else if(timet>(Endtime*10/4+125)&&timet<(Endtime*10/4+250))
    {
	SpdOutLeft=-400;
	SpdOutRight=-400;
	}
	
	
	
}





//*******************************速度输出*********************//
void SpdDuty(void)
{
	timet++;
	//***********************************限幅******************************************//
	if(SpdOutLeft<=-900)SpdOutLeft=-900;
	if(SpdOutRight<=-900)SpdOutRight=-900;
	if(SpdOutLeft>=980)SpdOutLeft=980;
	if(SpdOutRight>=980)SpdOutRight=980;
	//***********************************限幅******************************************//

	//**********速度输出***********//
			
	if(SpdOutLeft>0)
	{
		ftm_pwm_duty(ftm2,ftm_ch3,0);//左反
		ftm_pwm_duty(ftm2,ftm_ch0,(SpdOutLeft));//左正
	}
	else if(SpdOutLeft<0)
	{
		ftm_pwm_duty(ftm2,ftm_ch0,0);//左正
		ftm_pwm_duty(ftm2,ftm_ch3,fabs(SpdOutLeft));//左反
	}
	else
	{
	    ftm_pwm_duty(ftm2,ftm_ch3,0);//左正
		ftm_pwm_duty(ftm2,ftm_ch0,0);//左反
	}

	if(SpdOutRight>0)
	{
		ftm_pwm_duty(ftm2,ftm_ch2,0);//右反
		ftm_pwm_duty(ftm2,ftm_ch1,fabs(SpdOutRight));//右正
	}
	else if(SpdOutRight<0)
	{
		ftm_pwm_duty(ftm2,ftm_ch1,0);//右正
		ftm_pwm_duty(ftm2,ftm_ch2,fabs(SpdOutRight));//右反
	}
	else
	{
	    ftm_pwm_duty(ftm2,ftm_ch2,0);
		ftm_pwm_duty(ftm2,ftm_ch1,0);
	}
	
}
	 
	 
	 



static FTM_Type * const FTMX[] = FTM_BASES;

void ftm_pwm_mux(FTMn ftmn, FTM_CHn ch)
{
    switch(ftmn)
    {
        case ftm0:
        {
            SIM->SCGC |= SIM_SCGC_FTM0_MASK;                //开启FTM外设时钟
            switch(ch)
            {
                case ftm_ch0:
                {
                    if(FTM0_CH0_PIN == A0)
                    {
                        SIM->PINSEL &= ~SIM_PINSEL_FTM0PS0_MASK;
                    }
                    else if(FTM0_CH0_PIN == B2)
                    {
                        SIM->PINSEL |= SIM_PINSEL_FTM0PS0_MASK;
                    }
                }break;
                
                case ftm_ch1:
                {
                    if(FTM0_CH1_PIN == A1)
                    {
                        SIM->PINSEL &= ~SIM_PINSEL_FTM0PS1_MASK;
                    }
                    else if(FTM0_CH1_PIN == B3)
                    {
                        SIM->PINSEL |= SIM_PINSEL_FTM0PS1_MASK;
                    }
                }break;
            }
        }break;
        
        case ftm1:
        {
            SIM->SCGC |= SIM_SCGC_FTM1_MASK;                //开启FTM外设时钟
            switch(ch)
            {
                case ftm_ch0:
                {
                    if(FTM1_CH0_PIN == C4)
                    {
                        SIM->PINSEL &= ~SIM_PINSEL_FTM1PS0_MASK;
                    }
                    else if(FTM1_CH0_PIN == H2)
                    {
                        SIM->PINSEL |= SIM_PINSEL_FTM1PS0_MASK;
                    }
                }break;

                case ftm_ch1:
                {
                    if(FTM1_CH1_PIN == C5)
                    {
                        SIM->PINSEL &= ~SIM_PINSEL_FTM1PS1_MASK;
                    }
                    else if(FTM1_CH1_PIN == E7)
                    {
                        SIM->PINSEL |= SIM_PINSEL_FTM1PS1_MASK;
                    }
                }break;
            }
        }break;
        
        case ftm2:
        {
            SIM->SCGC |= SIM_SCGC_FTM2_MASK;                //开启FTM外设时钟
            switch(ch)
            {
                case ftm_ch0:
                {
                    SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS0_MASK;       
                    if(FTM2_CH0_PIN == C0)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(0);
                    }
                    else if(FTM2_CH0_PIN == H0)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(1);
                    }
                    else if(FTM2_CH0_PIN == F0)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(2);
                    }
                }break;
                
                case ftm_ch1:
                {
                    SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS1_MASK;       
                    if(FTM2_CH1_PIN == C1)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(0);
                    }
                    else if(FTM2_CH1_PIN == H1)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(1);
                    }
                    else if(FTM2_CH1_PIN == F1)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(2);
                    }
                }break;
                
                case ftm_ch2:
                {
                    SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS2_MASK;       
                    if(FTM2_CH2_PIN == C2)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(0);
                    }
                    else if(FTM2_CH2_PIN == D0)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(1);
                    }
                    else if(FTM2_CH2_PIN == G4)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(2);
                    }
                }break;
                
                case ftm_ch3:
                {
                    SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS3_MASK;       
                    if(FTM2_CH3_PIN == C3)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(0);
                    }
                    else if(FTM2_CH3_PIN == D1)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(1);
                    }
                    else if(FTM2_CH3_PIN == G5)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(2);
                    }
                }break;
                
                case ftm_ch4:
                { 
                    if(FTM2_CH4_PIN == B4)
                    {
                        SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS4_MASK; 
                    }
                    else if(FTM2_CH4_PIN == G6)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS4_MASK;
                    }
                }break;
                
                case ftm_ch5:
                {
                    if(FTM2_CH5_PIN == B5)
                    {
                        SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS5_MASK;     
                    }
                    else if(FTM2_CH5_PIN == G7)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS5_MASK;
                    }
                }break;
            }
 
        }break;
    }
}


uint16 period[3];
//-------------------------------------------------------------------------------------------------------------------
//  @brief      FTM初始化
//  @param      ftmn            选择模块
//  @param      ch              选择通道
//  @param      freq            需要设置的频率（单位HZ）
//  @param      duty            需要设置的占空比
//  @return     void
//  @since      v2.0
//  Sample usage:               ftm_pwm_init(ftm0,ftm_ch0,50,500);		//ftm0模块，0通道，50HZ，百分之50的占空比
//-------------------------------------------------------------------------------------------------------------------
void ftm_pwm_init(FTMn ftmn, FTM_CHn ch, uint32 freq, uint32 duty)
{
    uint32 clk_hz ;
    uint16 mod;
    uint8  ps;
    uint16 cv;
    
    ftm_pwm_mux(ftmn,ch);
    
    // 以 CPWMS = 0 ，边沿对齐
    clk_hz = ftm_clk_khz*1000;
    //clk_hz/(ps*mod) = freq        =>>     clk_hz/freq = (ps*mod)      =>>
    //clk_hz/freq < ((1<<n)*65536)  =>>    (clk_hz/freq)/65536 < (1>>n) =>> ((clk_hz/freq)/65536)>>n < 1
    mod = (clk_hz >> 16 ) / freq ;          // 临时用 mod 缓存一下
    ps = 0;
    while((mod >> ps) >= 1)                 // 等 (mod >> ps) < 1 才退出 while 循环 ，即求 PS 的最小值
        ps++;
    if(ps>0x07) return ;                    //超出设置范围，直接不设置跳出本函数，原因一般是由于PWM频率太低，或者总线频率太高导致
    
    mod = (clk_hz >> ps) / freq;            // 求 MOD 的值
    period[ftmn] = mod;
    switch(ftmn)                            // 初值 CNTIN 设为0 ，脉冲宽度：CnV - CNTIN ，即 CnV 就是 脉冲宽度了。
    {
        // EPWM的周期 ： MOD - CNTIN + 0x0001 == MOD - 0 + 1
        // 则 CnV = (MOD - 0 + 1) * 占空比 = (MOD - 0 + 1) * duty/ FTM_PRECISON
    case ftm0:
        cv = (duty * (mod - 0 + 1)) / FTM0_PRECISON;
        break;

    case ftm1:
        cv = (duty * (mod - 0 + 1)) / FTM1_PRECISON;
        break;

    case ftm2:
        cv = (duty * (mod - 0 + 1)) / FTM2_PRECISON;
        break;
    default:
        break;
    }
    
    FTMX[ftmn]->MOD = mod;                  //设置PWM周期
    
    FTMX[ftmn]->CONTROLS[ch].CnSC &= ~FTM_CnSC_ELSA_MASK;
    FTMX[ftmn]->CONTROLS[ch].CnSC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
    
    // set FTM clock to system clock 
    FTMX[ftmn]->SC = ( 0
                       //| FTM_SC_CPWMS_MASK       //0：边沿对齐 ，1： 中心对齐 （注释了表示 0）
                       | FTM_SC_PS(ps)             //分频因子，分频系数 = 2^PS
                       | FTM_SC_CLKS(1)            //时钟选择， 0：没选择时钟，禁用； 1：系统时钟； 2：固定时钟； 3：外部时钟
                       //| FTM_SC_TOIE_MASK        //溢出中断使能（注释了表示 禁止溢出中断）
                     );

    if(ftm2 == ftmn)FTMX[ftmn]->CNTIN = 0;         //设置计数器初值，一般没特殊用途就清零
    FTMX[ftmn]->CONTROLS[ch].CnV = cv;             //设置占空比
    FTMX[ftmn]->CNT = 0;                           //计数器，写任意值都会加载CNTIN的值
    
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      占空比设置
//  @param      ftmn            选择模块
//  @param      ch              选择通道
//  @param      duty            需要设置的占空比
//  @return     void
//  @since      v2.0
//  Sample usage:               ftm_pwm_duty(ftm0,ftm_ch0,500);		//ftm0模块，0通道，百分之50的占空比
//-------------------------------------------------------------------------------------------------------------------
void ftm_pwm_duty(FTMn ftmn, FTM_CHn ch, uint32 duty)
{
    uint32 cv;
    //占空比 = (CnV-CNTIN)/(MOD-CNTIN+1)
    switch(ftmn)
    {
    case ftm0:
        cv = (duty * (period[ftmn] - 0 + 1)) / FTM0_PRECISON;
        break;

    case ftm1:
        cv = (duty * (period[ftmn] - 0 + 1)) / FTM1_PRECISON;
        break;

    case ftm2:
        cv = (duty * (period[ftmn] - 0 + 1)) / FTM2_PRECISON;
        break;

    default:
        break;
    }
    
    FTMX[ftmn]->CONTROLS[ch].CnV = cv;      //设置占空比
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      频率设置
//  @param      ftmn            选择模块
//  @param      freq            需要设置的频率（单位HZ）
//  @return     void
//  @since      v2.0
//  Sample usage:               ftm_pwm_freq(ftm0,50);		//ftm0模块，50HZ
//-------------------------------------------------------------------------------------------------------------------
void ftm_pwm_freq(FTMn ftmn, uint32 freq)
{
    uint32 clk_hz;        //bus频率/2
    uint32 mod;
    uint8 ps;

    // 以 CPWMS = 0 ，边沿对齐
    clk_hz = ftm_clk_khz * 1000 ;
    
    //clk_hz/(ps*mod) = freq        =>>     clk_hz/freq = (ps*mod)      =>>
    //clk_hz/freq < ((1<<n)*65536)  =>>    (clk_hz/freq)/65536 < (1>>n) =>> ((clk_hz/freq)/65536)>>n < 1
    mod = (clk_hz >> 16 ) / freq ;          // 临时用 mod 缓存一下
    ps = 0;
    while((mod >> ps) >= 1)                 // 等 (mod >> ps) < 1 才退出 while 循环 ，即求 PS 的最小值
        ps++;
    if(ps>0x07) return ;                    //超出设置范围，直接不设置跳出本函数，原因一般是由于PWM频率太低，或者总线频率太高导致
    
    mod = (clk_hz >> ps) / freq;            // 求 MOD 的值
    period[ftmn] = mod;
    
    
    FTMX[ftmn]->MOD = mod;                  //设置PWM周期
    
    // set FTM clock to system clock 
    FTMX[ftmn]->SC = ( 0
                       //| FTM_SC_CPWMS_MASK       //0：边沿对齐 ，1： 中心对齐 （注释了表示 0）
                       | FTM_SC_PS(ps)             //分频因子，分频系数 = 2^PS
                       | FTM_SC_CLKS(1)            //时钟选择， 0：没选择时钟，禁用； 1：系统时钟； 2：固定时钟； 3：外部时钟
                       //| FTM_SC_TOIE_MASK        //溢出中断使能（注释了表示 禁止溢出中断）
                     );

    
    if(ftm2 == ftmn)FTMX[ftmn]->CNTIN = 0;  //设置计数器初值，一般没特殊用途就清零
    FTMX[ftmn]->CNT = 0;                    //计数器，写任意值都会架在CNTIN的值
}


void ftm_count_mux(FTMn ftmn)
{
    
    switch(ftmn)
    {
        case ftm0:
        {
            SIM->SCGC |= SIM_SCGC_FTM0_MASK;                //开启FTM外设时钟
            SIM->PINSEL &= ~SIM_PINSEL_FTM0CLKPS_MASK;      //清除外部时钟引脚选择
            if(FTM0_COUNT_PIN == A5)
            {
                port_pull(A5);
                SIM->PINSEL |= SIM_PINSEL_FTM0CLKPS(0);     //选择外部时钟输入引脚 A5
            }
            
            else if(FTM0_COUNT_PIN == E0)
            {
                port_pull(E0);
                SIM->PINSEL |= SIM_PINSEL_FTM0CLKPS(1);     //选择外部时钟输入引脚 E0
            }
            
            else if(FTM0_COUNT_PIN == E7)
            {
                port_pull(E7);
                SIM->PINSEL |= SIM_PINSEL_FTM0CLKPS(2);     //选择外部时钟输入引脚 E7
            }
        }break;
        
        case ftm1:
        {
            SIM->SCGC |= SIM_SCGC_FTM1_MASK;                //开启FTM外设时钟
            SIM->PINSEL &= ~SIM_PINSEL_FTM1CLKPS_MASK;      //清除外部时钟引脚选择
            if(FTM1_COUNT_PIN == A5)
            {
                port_pull(A5);
                SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(0);     //选择外部时钟输入引脚 A5
            }
            
            else if(FTM1_COUNT_PIN == E0)
            {
                port_pull(E0);
                SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(1);     //选择外部时钟输入引脚 E0
            }
            
            else if(FTM1_COUNT_PIN == E7)
            {
                port_pull(E7);
                SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(2);     //选择外部时钟输入引脚 E7
            }
        }break;
        
        case ftm2:
        {
            SIM->SCGC |= SIM_SCGC_FTM2_MASK;                //开启FTM外设时钟
            SIM->PINSEL &= ~SIM_PINSEL_FTM2CLKPS_MASK;      //清除外部时钟引脚选择
            FTM2->CNTIN = 0;
            if(FTM2_COUNT_PIN == A5)
            {
                port_pull(A5);
                SIM->PINSEL |= SIM_PINSEL_FTM2CLKPS(0);     //选择外部时钟输入引脚 A5
            }
            
            else if(FTM2_COUNT_PIN == E0)
            {
                port_pull(E0);
                SIM->PINSEL |= SIM_PINSEL_FTM2CLKPS(1);     //选择外部时钟输入引脚 E0
            }
            
            else if(FTM2_COUNT_PIN == E7)
            {
                port_pull(E7);
                SIM->PINSEL |= SIM_PINSEL_FTM2CLKPS(2);     //选择外部时钟输入引脚 E7
            }
        }break;
        
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      外部计数初始化  获取计数值、用于编码器测速，无法识别方向只能计数，建议使用带方向输出的编码器
//  @param      ftmn            选择模块
//  @return     void
//  @since      v2.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void ftm_count_init(FTMn ftmn)
{
    ftm_count_mux(ftmn);                                    //引脚复用 开启上拉 开启对应外设时钟
    
    FTMX[ftmn]->SC |= FTM_SC_PS(0);	                        //分频系数	
    FTMX[ftmn]->SC |= FTM_SC_CLKS(3);                       //选择外部时钟作为FTM输入时钟
                
    FTMX[ftmn]->CNT = 0;                                    //加载初始化值
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取计数值      用于编码器测速，无法识别方向只能计数，建议使用带方向输出的编码器
//  @param      ftmn            选择模块
//  @return     uint16          返回计数值
//  @since      v2.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
uint16 ftm_count_get(FTMn ftmn)
{
    return FTMX[ftmn]->CNT ;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      清除计数值      用于编码器测速，无法识别方向只能计数，建议使用带方向输出的编码器
//  @param      ftmn            选择模块
//  @since      v2.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void ftm_count_clean(FTMn ftmn)
{
    FTMX[ftmn]->CNT = 0;
}

