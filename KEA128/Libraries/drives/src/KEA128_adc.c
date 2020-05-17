#include "KEA128_adc.h"
#include "math.h"
#include "KEA128_ftm.h"
#include "init.h"
#include "isr.h"
#define RollPARA         8.0f 
float g_fDirectionError[4];		//方向偏差
float g_fDirectionError_dot[4];//方向偏差微分	
int16 g_ValueOfAD[7]={0};		//获取的电感值
int16 ADOld[5]={0};		//获取的电感值
int16 g_ValueOfADFilter[6]={0};	//阶梯滤波的电感值（未使用）
int16 XieLv[5]={0};
float kp=0;
float Xiekp=0;
float kp1=0;
float kd=0;
int kpcha=0;//根据陀螺仪减少kp
int kpcha2=0;//停车标志位
float g_fDirectionError_dotfabs[2]=0;
int16 SpdError[8]={0};
int AnnularFlag=0;
int32 cnt1=0;
int32 cnt2=0;
int32 cnt3=0;
int32 cntout1=0;
int32 cntout2=0;
int32 cntout3=0;
int32 cntout4=0;
int   ringflag=0;
int32 njnutim1=0;
int32 njnutim2=0;
int16 KFC=0;
int16 ttttim=0;
int16 tttsim=0;
int16 tttbim=0;
int32   angle4ms=0;//水平方向角速度
int32   angle4mss=0;//竖直方向角速度
int64   anglealltime=0;//水平方向角度
int64   anglealltimeV=0;//竖直方向角度
int8 aa=0;
int8 bb=0;
int16 zhidaotime=0;
int shiziflag=0;
int zhidaoflag=0;
int AnnularWhat=0;//疑似环
int AnnularCnt=0;
int anncnt[10]={0};
int16 GyroXLast=0;
int16 admiddle=0;
int   huansize=0;
int32 AnnLet=0;
int32 AnnRit=0;
int32 Annmb=0;
int16 XieKp=0;//斜电感倍数
int16 MidKp=0;
int16 AdVKp=0;
int ganhuangguan[5]={1};
int icx=0;
int shizibug=0;
void ErrorGet(void)
{
	static float g_fDirectionErrorTemp[4][5];
	static float RollSetDiff=0;

	
	ADOld[0] = admiddle ;
	ADOld[1] = g_ValueOfAD[0];
	ADOld[2] = g_ValueOfAD[1];
	Read_ADC();		//获取电感值
	g_ValueOfAD[0] = (g_ValueOfAD[0] < 10? 10:g_ValueOfAD[0]);	//6个电感值限幅
	g_ValueOfAD[1] = (g_ValueOfAD[1] < 10? 10:g_ValueOfAD[1]);
	g_ValueOfAD[2] = (g_ValueOfAD[2] < 10? 10:g_ValueOfAD[2]);
	g_ValueOfAD[3] = (g_ValueOfAD[3] < 10? 10:g_ValueOfAD[3]);
	g_ValueOfAD[4] = (g_ValueOfAD[4] < 10? 10:g_ValueOfAD[4]);
	g_ValueOfAD[5] = (g_ValueOfAD[5] < 10? 10:g_ValueOfAD[5]);
	   
	
	g_ValueOfAD[6] = adc_once(ADC0_SE7,ADC_12bit)/100.0f*MidKp;//限幅2000后的中间电感值
	admiddle = g_ValueOfAD[6];//中间电感值
	if(g_ValueOfAD[6]>2000)g_ValueOfAD[6]=2000;
	
	XieLv[0] = admiddle - ADOld[0] ;
	XieLv[1] = g_ValueOfAD[0] - ADOld[1] ;
	XieLv[2] = g_ValueOfAD[0] - ADOld[2] ;
	
	g_fDirectionError[0] = (float)(g_ValueOfAD[0] - g_ValueOfAD[1])/(g_ValueOfAD[0] + g_ValueOfAD[1]);//水平电感的差比和作为偏差
	g_fDirectionError[0] = (g_fDirectionError[0]>= 1? 1:g_fDirectionError[0]);	//偏差限幅
	g_fDirectionError[0] = (g_fDirectionError[0]<=-1?-1:g_fDirectionError[0]);
	
	
	g_fDirectionError[1] = (float)(g_ValueOfAD[2] - g_ValueOfAD[3])/(g_ValueOfAD[2] + g_ValueOfAD[3]);//垂直电感的差比和作为偏差
	g_fDirectionError[1] = (g_fDirectionError[1]>= 1? 1:g_fDirectionError[1]);	//偏差限幅
	g_fDirectionError[1] = (g_fDirectionError[1]<=-1?-1:g_fDirectionError[1]);
	
	g_fDirectionError[2] = (float)(g_ValueOfAD[2] - g_ValueOfAD[3])/(g_ValueOfAD[0] + g_ValueOfAD[1]);//垂直水平电感的差比和作为偏差
	g_fDirectionError[2] = (g_fDirectionError[2]>= 1? 1:g_fDirectionError[2]);	//偏差限幅
	g_fDirectionError[2] = (g_fDirectionError[2]<=-1?-1:g_fDirectionError[2]);
	
	g_fDirectionError[3] = (float)(g_ValueOfAD[4] - g_ValueOfAD[5])/(g_ValueOfAD[4] + g_ValueOfAD[5]);//八字水平电感的差比和作为偏差
	g_fDirectionError[3] = (g_fDirectionError[3]>= 1? 1:g_fDirectionError[3]);	//偏差限幅
	g_fDirectionError[3] = (g_fDirectionError[3]<=-1?-1:g_fDirectionError[3]);
	  
	g_fDirectionErrorTemp[0][4] = g_fDirectionErrorTemp[0][3];
	g_fDirectionErrorTemp[0][3] = g_fDirectionErrorTemp[0][2];
	g_fDirectionErrorTemp[0][2] = g_fDirectionErrorTemp[0][1];
	g_fDirectionErrorTemp[0][1] = g_fDirectionErrorTemp[0][0];
	g_fDirectionErrorTemp[0][0] = g_fDirectionError[0];
	g_fDirectionError_dot[0] = 5*(g_fDirectionErrorTemp[0][0]-g_fDirectionErrorTemp[0][3]);//水平电感的偏差微分
	g_fDirectionError_dot[0] = (g_fDirectionError_dot[0]> 0.7? 0.7:g_fDirectionError_dot[0]);//偏差微分限幅
	g_fDirectionError_dot[0] = (g_fDirectionError_dot[0]<-0.7?-0.7:g_fDirectionError_dot[0]);

	g_fDirectionError_dotfabs[0] = 5*(fabs(g_fDirectionErrorTemp[0][0])-fabs(g_fDirectionErrorTemp[0][3]));

	g_fDirectionErrorTemp[1][4] = g_fDirectionErrorTemp[1][3];
	g_fDirectionErrorTemp[1][3] = g_fDirectionErrorTemp[1][2];
	g_fDirectionErrorTemp[1][2] = g_fDirectionErrorTemp[1][1];
	g_fDirectionErrorTemp[1][1] = g_fDirectionErrorTemp[1][0];
	g_fDirectionErrorTemp[1][0] = g_fDirectionError[1];
	g_fDirectionError_dot[1] = 5*(g_fDirectionErrorTemp[1][0]-g_fDirectionErrorTemp[1][3]);//垂直电感的偏差微分
	g_fDirectionError_dot[1] = (g_fDirectionError_dot[1]> 0.7? 0.7:g_fDirectionError_dot[1]);//偏差微分限幅
	g_fDirectionError_dot[1] = (g_fDirectionError_dot[1]<-0.7?-0.7:g_fDirectionError_dot[1]);
	
	g_fDirectionErrorTemp[2][4] = g_fDirectionErrorTemp[2][3];
	g_fDirectionErrorTemp[2][3] = g_fDirectionErrorTemp[2][2];
	g_fDirectionErrorTemp[2][2] = g_fDirectionErrorTemp[2][1];
	
	g_fDirectionErrorTemp[2][1] = g_fDirectionErrorTemp[2][0];
	g_fDirectionErrorTemp[2][0] = g_fDirectionError[2];
	g_fDirectionError_dot[2] = 5*(g_fDirectionErrorTemp[2][0]-g_fDirectionErrorTemp[2][3]);//垂直电感的偏差微分
	g_fDirectionError_dot[2] = (g_fDirectionError_dot[2]> 0.7? 0.7:g_fDirectionError_dot[2]);//偏差微分限幅
	g_fDirectionError_dot[2] = (g_fDirectionError_dot[2]<-0.7?-0.7:g_fDirectionError_dot[2]);
	
	g_fDirectionErrorTemp[3][4] = g_fDirectionErrorTemp[3][3];
	g_fDirectionErrorTemp[3][3] = g_fDirectionErrorTemp[3][2];
	g_fDirectionErrorTemp[3][2] = g_fDirectionErrorTemp[3][1];
	g_fDirectionErrorTemp[3][1] = g_fDirectionErrorTemp[3][0];
	g_fDirectionErrorTemp[3][0] = g_fDirectionError[3];
	g_fDirectionError_dot[3] = 5*(g_fDirectionErrorTemp[3][0]-g_fDirectionErrorTemp[3][3]);//垂直电感的偏差微分
	g_fDirectionError_dot[3] = (g_fDirectionError_dot[3]> 0.7? 0.7:g_fDirectionError_dot[3]);//偏差微分限幅
	g_fDirectionError_dot[3] = (g_fDirectionError_dot[3]<-0.7?-0.7:g_fDirectionError_dot[3]);
			
///////////*****************陀螺仪******************//////////////////	
     GyroXLast=GyroX;
	 GyroXo=GyroX;  
     GyroX=GetData(GYRO_XOUT_H);
     if(GyroX<32768) GyroX+=65535;
     GyroX=GyroX-18+5;
     if((GyroX-GyroXo)>32768) GyroX-=65535;
     else if((GyroXo-GyroX)>32768) GyroX+=65535; 
	
	if(timet>=375)//起跑1秒后检测坡道
	{
	 
	 GyroYo=GyroY;  
     GyroY=GetData(GYRO_YOUT_H);
     if(GyroY<32768) GyroY+=65535;
     GyroY=GyroY-11;
     if((GyroY-GyroYo)>32768) GyroY-=65535;
     else if((GyroYo-GyroY)>32768) GyroY+=65535;
	 
	  angle4mss=GyroY/100;
	 anglealltimeV+=angle4mss;
	 
	 
	 if(admiddle>2400)
		 DianBoFlag=5;
	 if(DianBoFlag==5)
		 DianBoTim++;
	 if(DianBoTim>33)
	 {
		 DianBoTim=0;
	     DianBoFlag=0;
	 }
	 
	 
		 if(fabs(GyroY)>3000&&PoFlag==0)
		 {
		  if(DianBoFlag==0)
			  PoFlag=1;//颠簸
		  else if(DianBoFlag==5)
			  PoFlag=2;//坡道
	   
		 }
	   if(PoFlag==1||PoFlag==2)
	   {
		   PoTim++;
	   }
	   if(PoTim>=njnutim2)//坡道检测一秒钟延时
	   {
		   PoTim=0;
		   PoFlag=0;
	   }
	 	 
	}
	
///////////*****************陀螺仪******************//////////////////
//////////**************十字***********/////////////	
	if(g_ValueOfAD[3]>1600&&g_ValueOfAD[2]>1600)
		shiziflag=1;
	if(shiziflag==1)
		cnt3++;
	if(cnt3>80)
	{cnt3=0;shiziflag=0;}
//////////**************十字***********/////////////
	
//////////**************直道***********/////////////		
	if(GyroX<=1500&&GyroX>=-1500)
	zhidaotime++;
	if(zhidaotime>20)
		zhidaoflag=1;
	if(GyroX>1500||GyroX<-1500)
	{
		zhidaotime=0;
		zhidaoflag=0;
	}
	
	/*	if(GyroX>1500&&InAnn==0)
			njnutim1++;
	if(njnutim1>125)
		InAnn=1;
	if(GyroX<500||InAnn==1)
		    njnutim1=0;*/
		   
		

//////////**************直道***********/////////////

    kp1 = kp + 18 * (1000-fabs(GyroX))/1000.0f;
	Xiekp = 55 + 12 * (1000-fabs(GyroX))/1000.0f;

	if((AnnularWhat==1||AnnularFlag>0)&&(huansize==0||huansize==1||huansize==5||huansize==6))
	{
		kp1=kp;
	}
	
	SpdError[0] = g_fDirectionError[0] * kp1 + g_fDirectionError_dot[0] * kd;//横差比和
		
	SpdError[1] = g_fDirectionError[1] * 160 + g_fDirectionError_dot[1] * 140;//竖差比和
	
	SpdError[2] = g_fDirectionError[2] * kp1 + g_fDirectionError_dot[2] * kd;//横竖差比和
	
	if(g_ValueOfAD[3]>1600&&g_ValueOfAD[2]>1600)//十字

	SpdError[2]=0;
	
	SpdError[3] = g_fDirectionError[3]*Xiekp + g_fDirectionError_dot[3]*55;//斜差比和变Kp
	
	SpdError[4] = g_fDirectionError[0]*140 + g_fDirectionError_dot[0]*180;
	
	SpdError[5] = g_fDirectionError[3]*55+ g_fDirectionError_dot[3]*55;//斜差比和定Kp
	
    //SpdError[6] = (g_fDirectionError[0]>0? 2000-g_ValueOfAD[6]:g_ValueOfAD[6]-2000)/(ADOld[0]*2 )*moluntai;
	
	AnnJudge();//环岛识别

	SpdError[7] = 10*1.0f/10*SpdError[0]+23*1.0f/10*SpdError[2];//正常偏差
	
	huansize = anncnt[AnnularCnt%4];//环岛大小设置
	
	if(PoFlag>0&&PoTim<180)//坡道0.7秒偏差
		
	SpdError[7] = SpdError[0];
	   
	if(AnnularWhat==1)//预检环偏差
	{
		if(huansize==1||huansize==5)
			SpdError[7] = 0*SpdError[3] + 2*SpdError[0] + 0.0f*(huansize>3?-3:3)*(-120+(Speednow<120?120:Speednow))/180.0f;
	    else if(huansize==0||huansize==6)
			SpdError[7] = 0*SpdError[3] + 3*SpdError[0] + 0.0f*(huansize>3?-3:3)*(-120+(Speednow<120?120:Speednow))/180.0f;
		else if(huansize==2)
			SpdError[7] = 0.9*SpdError[5] + 0.9*SpdError[0]+(20.0f*(huansize>3?-3:3)-(huansize-4)*AnnLet-(huansize-2)*AnnRit)*(-120+(Speednow<120?120:Speednow))/180.0f;
	    else if(huansize==4)
			//SpdError[7] = 0.9*SpdError[5] + 0.9*SpdError[0]+(30.0f*(huansize>3?-3:3)-(huansize-4)*AnnLet-(huansize-2)*AnnRit)*(-120+(Speednow<120?120:Speednow))/180.0f;
	         SpdError[7] = 0.9*SpdError[5] + 0.0*SpdError[0]+0*(20.0f*(huansize>3?-3:3)-(huansize-4)*AnnLet-(huansize-2)*AnnRit)*(-120+(Speednow<120?120:Speednow))/180.0f;
	}
	if(AnnularFlag==1)//打角进环
	{
		if(huansize==1||huansize==5)
			SpdError[7] = 0.9*SpdError[3] + 0.9*SpdError[0] + 36.0f*(huansize>3?-3:3)*(-120+(Speednow<120?120:Speednow))/180.0f;
		else if(huansize==0||huansize==6)
			SpdError[7] = 0.9*SpdError[3] + 0.9*SpdError[0] + Annmb*(huansize>3?-3:3)*(-120+(Speednow<120?120:Speednow))/180.0f;
		else if(huansize==2)
			SpdError[7] =((10*1.0f/10*SpdError[0]+23*1.0f/10*SpdError[2])*1.1-(huansize-4)*AnnLet-(huansize-2)*AnnRit)*(-100+(Speednow<120?120:Speednow))/180.0f;
	    else if(huansize==4)
			//SpdError[7] =((10*1.0f/10*SpdError[0]+23*1.0f/10*SpdError[2])*1.1-(huansize-4)*AnnLet-(huansize-2)*AnnRit)*(-90+(Speednow<120?120:Speednow))/180.0f;
	        SpdError[7] = 0.9*SpdError[3] + 0.9*SpdError[0] + AnnRit*(huansize>3?-2:2)*(-120+(Speednow<120?120:Speednow))/180.0f;
	}
	
	if(AnnularFlag==2)//环内
	{   
		if(huansize==0||huansize==1||huansize==5||huansize==6)
		SpdError[7] = (SpdError[3] + 0.9*SpdError[0]);
		else if(huansize==4)
		{
		if(Speednow<200)
		SpdError[7] = (10*1.0f/10*SpdError[0]+13*1.0f/10*SpdError[2])*(-100+(Speednow<120?120:Speednow))/220.0f;
		else
		SpdError[7] = (10*1.0f/10*SpdError[0]+20*1.0f/10*SpdError[2])*(-100+(Speednow<120?120:Speednow))/120.0f;//小环内
		}
		else
		{
		if(Speednow<200)
		SpdError[7] = (10*1.0f/10*SpdError[0]+4*1.0f/10*SpdError[2])*(-100+(Speednow<120?120:Speednow))/220.0f;
		else
		SpdError[7] = (10*1.0f/10*SpdError[0]+20*1.0f/10*SpdError[2])*(-100+(Speednow<120?120:Speednow))/120.0f;//小环内
		}	
	}
	
    
	if(AnnularFlag==2&&fabs(anglealltime)>10000&&(huansize==0||huansize==6))//大环出环前
		    SpdError[7] = 2*SpdError[5] + 0.9*SpdError[0];
	else if(AnnularFlag==2&&fabs(anglealltime)>9700&&(huansize==1||huansize==5))//中环出环前
		    SpdError[7] = 1.5*SpdError[5] + 0.93*SpdError[0];
	else if(huansize==2&&AnnularFlag==2&&fabs(anglealltime)>10000)//小环左出环前
		    SpdError[7]=SpdError[0]+14/10.0f * SpdError[5];
	else if(huansize==4&&AnnularFlag==2&&fabs(anglealltime)>9700)//小环右出环前
	        SpdError[7]=SpdError[0]+14/10.0f * SpdError[5];
		
	if(AnnularFlag==3)//出环时
	{
		if(huansize==2||huansize==4)
            SpdError[7]=(SpdError[4]-(0.5-0.5*cntout3/ttttim)*SpdError[1])*0.7f;	
		else if(huansize==1||huansize==5)
			SpdError[7]=(SpdError[4]-(0.6-0.4*cntout3/ttttim)*SpdError[1])*0.7f;
		else
			SpdError[7]=(SpdError[4]-(0.6-0.35*cntout3/tttbim)*SpdError[1])*0.7f;
	}
	if(timet>(Endtim*2.5f))
	{
	for(icx=0;icx<3;icx++)
	{	
		ganhuangguan[icx]=gpio_get(E4);
	}
	}

///////////*****************蜂鸣器**************////////////
	if(AnnularFlag>0&&AnnularFlag<4)
       ringflag=1;
	/*else if(AnnularWhat==1)
	   ringflag=1;*/
	else if(timet<StartTime)
	   ringflag=1;
	else if(PoFlag==1&&PoTim<250)
	   ringflag=2;
	else if(PoFlag==2&&PoTim<250)
	   ringflag=3;
	/*else if(zhidaoflag==1)
		ringflag=1;*/
	/*if(Speednow<200)
		ringflag=1;
	
	/*else if((g_ValueOfAD[3]>1600&&g_ValueOfAD[2]>1600))
		ringflag=1;*/
	else ringflag=0;
	
	/*if(StpFlag==1)
	ringflag=1;*/

    ring_control();
///////////*****************蜂鸣器******************////////////

	
//*/*/*/*/*/*/*/********偏差限幅************/*/*/*/*/*/*/*/*//
	if(SpdError[7]>600)SpdError[7]=600;
	if(SpdError[7]<-600)SpdError[7]=-600;
	SpdError[7]=-10*SpdError[7];
//*/*/*/*/*/*/*/********偏差限幅************/*/*/*/*/*/*/*/*//
}

void AnnJudge(void)
{	
	if(huansize==2||huansize==4)
	{
	if((((g_ValueOfAD[0]>1100&&g_ValueOfAD[1]>1100)||(g_ValueOfAD[0]+g_ValueOfAD[1]>3200))&&((g_ValueOfAD[2]+g_ValueOfAD[3])<2000)))	//1200 1200 3500 1600 
    AnnularWhat=1;
    else 
    AnnularWhat=0;
	}
	else 
	{
	if((((g_ValueOfAD[0]>1300&&g_ValueOfAD[1]>1300)||(g_ValueOfAD[0]+g_ValueOfAD[1]>3600))&&((g_ValueOfAD[2]+g_ValueOfAD[3])<5000)))	//1200 1200 3500 1600 
    AnnularWhat=1;
    else 
    AnnularWhat=0;
	}	

	if(shizibug==1)
	{
		if(PoFlag>0&&PoTim<200)
		AnnularWhat=0; 
	}


if(huansize==0||huansize==1||huansize==5||huansize==6)
{
	if(((g_ValueOfAD[0]+g_ValueOfAD[1])>2600)&&AnnularFlag==0&&g_ValueOfAD[2]<800&&g_ValueOfAD[3]<800&&(g_ValueOfAD[4]>1500||g_ValueOfAD[5]>1500||g_ValueOfAD[0]>3000))
{
	AnnularFlag=1;
}
}
else
{
	if(((g_ValueOfAD[0]+g_ValueOfAD[1])>2600)&&AnnularFlag==0&&(g_ValueOfAD[4]>1800||g_ValueOfAD[5]>1800||g_ValueOfAD[0]>3000)&&(g_ValueOfAD[2]<600||g_ValueOfAD[3]<600))
{
	AnnularFlag=1;
}
	
	
}
if(AnnularFlag==1&&((g_ValueOfAD[0]+g_ValueOfAD[1])<2800))
AnnularFlag=2;

if(AnnularFlag==2)
 cntout1++;
if(cntout1>300)cntout1=300;
if(AnnularFlag==0)
 cntout1=0;

if(AnnularFlag==1||AnnularFlag==2)
{ 
     angle4ms=GyroX/100;
	 anglealltime+=angle4ms;
}
if(huansize==0||huansize==6)
{	
if(AnnularFlag==2&&(fabs(anglealltime)>13000))//14000
{
	AnnularFlag=3;
}
}
else if(huansize==1||huansize==5)
{	
if(AnnularFlag==2&&(fabs(anglealltime)>12800))//14000
{
	AnnularFlag=3;
}
}
else if(huansize==4)
{
if(AnnularFlag==2&&(fabs(anglealltime)>(12500)))//zuo12500
{
	AnnularFlag=3;
}
}
else
{
if(AnnularFlag==2&&(fabs(anglealltime)>12500))//zuo12500
{
	AnnularFlag=3;
}
}

if(AnnularFlag==3)

{ 
     angle4ms=0;
	 anglealltime=0;
}

if(AnnularFlag==3)
     cntout3++;
if(huansize==1||huansize==5)
{
     if(cntout3>ttttim)
     {
         cntout3=0;
	     AnnularFlag=0;
		 AnnularCnt++;
     }
}
else if(huansize==0||huansize==6)
{
     if(cntout3>tttbim)
     {
         cntout3=0;
	     AnnularFlag=0;
		 AnnularCnt++;
     }
}
else
{
	if(cntout3>tttsim)
     {
         cntout3=0;
	     AnnularFlag=0;
		 AnnularCnt++;
     }
}
	//if(PoFlag==1&&AnnularFlag>0&&AnnularFlag<3)
    /*if(PoHuan==1)
	{
		if(PoFlag==1)
		{
			if(huansize==2||huansize==4)
			{
				if(((g_ValueOfAD[0]+g_ValueOfAD[1])>2600)&&AnnularFlag==0&&(g_ValueOfAD[4]>1900||g_ValueOfAD[5]>1900||admiddle>3000)&&(g_ValueOfAD[2]<600||g_ValueOfAD[3]<600))
			    AnnularFlag==0;
			}
		}
	}*/
	 if(PoHuan==1)
	 {
	 if(AnnularFlag==2)//误检清除
	 {
		 if((huansize<3&&angle4ms>0)||(huansize>3&&angle4ms<0))
		 {
			 AnnularFlag=0;
			 cntout1=0;
			 angle4ms=0;
			 anglealltime=0;
		 }
	 }
	 }
		

}





void Read_ADC(void)
{
     int16  i,j,k,temp;
     int16  ad_valu[6][5],ad_valu1[6],ad_sum[6];
	 int16 ValueOfADOld[6],ValueOfADNew[6];

     for(i=0;i<5;i++)
     {
         ad_valu[0][i]=ad_ave(AD1, ADC_12bit, 5);// AD1水平左
         ad_valu[1][i]=ad_ave(AD2, ADC_12bit, 5);// AD2水平右
         ad_valu[2][i]=ad_ave(AD3, ADC_12bit, 5)/100.0f*AdVKp;// AD3垂直左
         ad_valu[3][i]=ad_ave(AD4, ADC_12bit, 5)/100.0f*AdVKp;// AD4垂直右
		 ad_valu[4][i]=ad_ave(AD5, ADC_12bit, 5)/100.0f*XieKp;// AD4垂直右
		 ad_valu[5][i]=ad_ave(AD6, ADC_12bit, 5)/100.0f*XieKp;// AD4垂直右
     }
/*=========================冒泡排序升序==========================*///舍弃最大值和最小值
     for(i=0;i<6;i++)
     {
        for(j=0;j<4;j++)
        {
           for(k=0;k<4-j;k++)
           {
              if(ad_valu[i][k] > ad_valu[i][k+1])
              {
                 temp = ad_valu[i][k+1];
                 ad_valu[i][k+1] = ad_valu[i][k];
                 ad_valu[i][k] = temp;
              }
           }
        }
     }
/*===========================中值滤波=================================*/
     for(i=0;i<6;i++)    //求中间三项的和
     {
        ad_sum[i] = ad_valu[i][1] + ad_valu[i][2] + ad_valu[i][3];
        ad_valu1[i] = ad_sum[i] / 3;
     }

	
	 for(i=0;i<6;i++)            //将数值中个位数除掉
	 {
	 	g_ValueOfAD[i] = (int16)(ad_valu1[i]/10*10);

		//采集梯度平滑，每次采集最大变化40
		ValueOfADOld[i] = g_ValueOfADFilter[i];
		ValueOfADNew[i] = g_ValueOfAD[i];
		
		if(ValueOfADNew[i]>=ValueOfADOld[i])
			g_ValueOfADFilter[i] = ((ValueOfADNew[i]-ValueOfADOld[i])>50?(ValueOfADOld[i]+50):ValueOfADNew[i]);
		else
			g_ValueOfADFilter[i] = ((ValueOfADNew[i]-ValueOfADOld[i])<-60?(ValueOfADOld[i]-60):ValueOfADNew[i]);
	 }	 
}


uint16 ad_ave(ADCn_Ch adcn_ch, ADC_nbit bit,uint8 N) //均值滤波
{
    uint32 tmp = 0;
    uint8  iccd;
    uint8  jccd;

    for(iccd = 0; iccd < N; iccd++)
	{
        tmp += adc_once(adcn_ch, bit);
		jccd = 20;
		while(jccd--);
	
	}
    tmp = tmp / N;
    return (uint16)tmp;
}


__ramfunc void ring_control(void)
{
    static int ringcount=0;
    if(ringflag==0)
    {
        ring_off();
        ringcount=0;
    }
    else if(ringflag==1)
    {
        ring_on();
        ringcount=0;
    }
    else if(ringflag==2)
    {
        ringcount++;
        if(ringcount<=25)   ring_on();
        else                ring_off();
        if(ringcount>=50)  ringcount=0;
    }
    else if(ringflag==3)
    {
        ringcount++;
        if(ringcount<=50)  ring_on();
        else                ring_off();
        if(ringcount>=100)  ringcount=0;
    }
    else if(ringflag==4)
    {
        ringcount++;
        if(ringcount<=50)  ring_on();
        else                ring_off();
        if(ringcount>=250)  ringcount=0;
    }
}


void adc_init(ADCn_Ch adcn_ch)
{
    SIM->SCGC |= SIM_SCGC_ADC_MASK;         //开启ADC时钟
    
    ADC->APCTL1 |= 1<<adcn_ch;              //使能ADC引脚
    
    ADC->SC2 = ADC_SC2_REFSEL(1);           //基准电压选择
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC采集
//  @param      adcn_ch         选择ADC通道
//  @param      bit             选择精度ADC_8bit、ADC_10bit、ADC_12bit
//  @return     void
//  @since      v2.0
//  Sample usage:               uint16 dat = adc_once(ADC0_SE8,ADC_12bit);//采集ADC0_SE8电压，精度12位
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_once(ADCn_Ch adcn_ch, ADC_nbit bit)
{
    if(1 == KEA128_CLOCK)
    {
        //超频后，设置ADC的CLK为总线时钟/2
        ADC->SC3 = (0
                    | ADC_SC3_ADIV(1)           //分频系数
                    | ADC_SC3_MODE(bit)         //分辨率
                    | ADC_SC3_ADICLK(0)         //使用总线时钟做为ADC得时钟源
                    //| ADC_SC3_ADLSMP_MASK       //1：长采样时间  0：短采样时间   注释为0 长采样时间采集更稳定
                    );
    }
    else
    {
        //未超频，设置ADC的CLK为总线时钟
        ADC->SC3 = (0
                    | ADC_SC3_ADIV(0)           //分频系数
                    | ADC_SC3_MODE(bit)
						//分辨率
                    | ADC_SC3_ADICLK(0)         //使用总线时钟做为ADC得时钟源
                    //| ADC_SC3_ADLSMP_MASK       //1：长采样时间  0：短采样时间   注释为0 长采样时间采集更稳定
                    );
    }
    

    ADC->SC1 = ADC_SC1_ADCH(adcn_ch);       //启动转换
    
    while(!(ADC->SC1 & ADC_SC1_COCO_MASK)); //等待转换完成
    return (ADC->R & ADC_R_ADR_MASK);       //返回结果
    
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC停止采集
//  @param      adcn_ch         选择ADC通道
//  @param      bit             选择精度ADC_8bit、ADC_10bit、ADC_12bit
//  @return     void
//  @since      v2.0
//  Sample usage:               adc_stop(adc0);
//-------------------------------------------------------------------------------------------------------------------
void adc_stop(void)
{
    ADC->SC1 = ADC_SC1_ADCH(0xFF); 
}
