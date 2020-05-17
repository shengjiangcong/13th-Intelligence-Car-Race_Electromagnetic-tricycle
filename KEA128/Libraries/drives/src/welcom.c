#include "welcom.h"
#include "KEA128_adc.h"
#include "math.h"
#include "KEA128_ftm.h"
uint8    imgmode=0;                   //模式选择--->Runmode  Showmode
uint8    SpeedSelect=0;               //速度档位--High-Speed   Mid-Speed  Low-Speed
uint8    SaveMenu[ConfigNum][10];     //菜单存储数组
int16 SaveStep[ConfigNum];         //步存储数组
void Main_Menu(void);             //速度档位显示主函数
void Add_Menu(uint8 *menu,int16 step);//增加参数
void Next_Menu(uint8 pos);            //第二界面
void strcopy(uint8 *str1,uint8 *str2);   //字符串拷贝
uint8 read_key(void)
{
  uint8 num=0,count=0;
  if(!gpio_get(H6)) {num+=1;count++;}//上
  if(!gpio_get(D0)) {num+=2;count++;}//下
  if(!gpio_get(H7)) {num+=3;count++;}//左
  if(!gpio_get(G1)) {num+=4;count++;}//右
  if(!gpio_get(G3)) {num+=5;count++;}//按下
  if(count>=2) return 0;
  else return num; 
}
void welcome(void)                
{
  precursors_logo();
  systick_delay_ms(200);
  int16  pos=0;                 //*位置
  int16  disppos=0;             //显示页数
  int16  DelayTime=0;           //按键延时时间
  uint8  Keycount=0;            //确认键计数
  uint8  Key=0;                 //按键读取变量
  uint8  NextFlag=0;            //确认标志
  uint8  ReadMode=0;            //0------SD_Read,1------Flash_Read
  
    Add_Menu("1.bisai",1); //0或1             
    Add_Menu("2.SetSpd",1); //285（260-290）            
    Add_Menu("3.PoSpd",5); //220              
    Add_Menu("4.huan1",1);              
    Add_Menu("5.huan2",1);            
    Add_Menu("6.huan3",1);              
    Add_Menu("7.huan4",1);               
    Add_Menu("8.huan5",1);              
    Add_Menu("9.XieKp",2);               
    Add_Menu("10.MidKp",2);          
    Add_Menu("11.AdVKp",2);        
    Add_Menu("12.tttsim",2);//60           
    Add_Menu("13.ttttim",2);//68         
    Add_Menu("14.tttbim",2);//70         
    Add_Menu("15.AnnLet",1);//20
    Add_Menu("16.AnnRit",1);//50          
    Add_Menu("17.Annmb",1);//35             
    Add_Menu("18.PoHuan",1);//1防误检              
    Add_Menu("19.shzbug",1);//0
    Add_Menu("20.stpcar",1); //1（0为不停车）
    Add_Menu("21.ghgtim",100);          
    Add_Menu("22.RunTim",50);               
    Add_Menu("23.lowtm1",100);               
    Add_Menu("24.lowtm2",100);               
    Add_Menu("25.aa",1);//6              
    Add_Menu("26.kp",5);//120          
    Add_Menu("27.kd",5);//110              
    Add_Menu("28.PoDly",10);//450
    Add_Menu("dbstptim",10);//70
  
    
  //调参界面添加参数-----------------  
	 flashconf_read();
	 XieKp   =    conf[SpeedSelect][9];
	 MidKp   =    conf[SpeedSelect][10];
	 AdVKp   =    conf[SpeedSelect][11];
    Main_Menu();                  //电感值and主菜单  
  while(!NextFlag)
 {
  Key=read_key();//读取按键
  if(Key==0)continue;//继续读取
  else
  {
    switch(Key)
    {
    case 1:pos--;if(pos<0)pos=0;OLED_fill(6,8,0x00);OLED_P6x8Str(0,pos*2,"*");break;
    case 2:pos++;if(pos>3)pos=3;OLED_fill(6,8,0x00);OLED_P6x8Str(0,pos*2,"*");break;
    case 5:if(pos<3)SpeedSelect=pos;else ReadMode=1;NextFlag=1;pos=0;break;
    }
    systick_delay_ms(200);
  }
 }

 //主参数界面-------------------------------------------
  NextFlag=0;
  Next_Menu(disppos);
  OLED_P6x8Str(0,0,"*");
  while(!NextFlag)
  {
    Key=read_key();
    if(Key==0) {DelayTime=150;continue;}
    else
    {
      switch(Key)
      {
        case 2:Keycount=0;pos++;if(pos>7){pos=7;disppos++;if(disppos>(ConfigNum-8)) disppos=(ConfigNum-8);Next_Menu(disppos);}OLED_fill(6,8,0x00);OLED_P6x8Str(0,pos,"*");break;
        case 1:Keycount=0;pos--;if(pos<0){pos=0;disppos--;if(disppos<0)  disppos=0; Next_Menu(disppos);}OLED_fill(6,8,0x00);OLED_P6x8Str(0,pos,"*");break;
        case 4:Keycount=0;conf[SpeedSelect][pos+disppos]+=SaveStep[pos+disppos];Next_Menu(disppos);OLED_P6x8Str(0,pos,"*");break;
        case 3:Keycount=0;conf[SpeedSelect][pos+disppos]-=SaveStep[pos+disppos];if(conf[SpeedSelect][pos+disppos]<0) conf[SpeedSelect][pos+disppos]=0;Next_Menu(disppos);OLED_P6x8Str(0,pos,"*");break;
        case 5:Keycount++;if(Keycount>=2) {NextFlag=1;OLED_Fill(0x00);break;}     
      }
      systick_delay_ms(DelayTime);       //按键延时
      DelayTime-=20;
      if(DelayTime<50) DelayTime=50;
    }
  } 
  flashconf_write();
}

//电感值主菜单
uint16 adc[8]={0};
uint16 xianshicanshu[8];
void Main_Menu(void)
{
  OLED_Fill(0x00);//清屏
  while(1)
  {
    adc[0]=adc_once(ADC0_SE4,ADC_12bit)/100.0f*AdVKp;//zuoxie
    adc[1]=adc_once(ADC0_SE5,ADC_12bit);//
    adc[2]=adc_once(ADC0_SE6,ADC_12bit)/100.0f*XieKp;//zuoshu
    adc[3]=adc_once(ADC0_SE7,ADC_12bit)/100.0f*MidKp;
    adc[4]=adc_once(ADC0_SE12,ADC_12bit)/100.0f*XieKp;//youxie
    adc[5]=adc_once(ADC0_SE13,ADC_12bit)/100.0f*AdVKp;//youheng
    adc[6]=adc_once(ADC0_SE14,ADC_12bit);//youshu
    adc[7]=adc_once(ADC0_SE15,ADC_12bit);//
	
	xianshicanshu[0]=fabs(1000.0f*(adc[2]-adc[7])/(adc[2]+adc[7]));
    xianshicanshu[1]=fabs(1000.0f*(adc[0]-adc[4])/(adc[2]+adc[7]));
	OLED_Print_Num(0,0,adc[1]);
    OLED_Print_Num(0,2,adc[0]);//
    OLED_Print_Num(0,4,adc[3]);//
    OLED_Print_Num(0,6,adc[2]);//
    OLED_Print_Num(56,0,adc[7]);//
    OLED_Print_Num(56,2,adc[5]);//
   // OLED_Print_Num(56,4,adc[6]);//
    OLED_Print_Num(56,6,adc[4]);//
	
	//xie shu heng
	
   if(5==read_key()) break; //读按键，按下则进入下个界面
   systick_delay_ms(50);
  }
   systick_delay_ms(200);
   OLED_Fill(0x00);
  while(1)
  {
    adc[0]=gpio_get(I3);
    adc[1]=adc_once(ADC0_SE5,ADC_12bit);
    adc[2]=adc_once(ADC0_SE6,ADC_12bit);
    adc[3]=adc_once(ADC0_SE7,ADC_12bit);
    adc[4]=adc_once(ADC0_SE12,ADC_12bit);//斜电感真实值
    adc[5]=adc_once(ADC0_SE13,ADC_12bit);
    adc[6]=adc_once(ADC0_SE14,ADC_12bit);
    adc[7]=adc_once(ADC0_SE15,ADC_12bit);
	  
	xianshicanshu[0]=gpio_get(E4);
    xianshicanshu[1]=1900.0f/adc[4] * 100.0f;
	
	 xianshicanshu[2]=1970.0f/adc[3] * 100.0f;
	 xianshicanshu[3]=2450.0f/adc[5] * 100.0f;
    OLED_Print_Num(0,0,xianshicanshu[0]);
    OLED_Print_Num(0,2,xianshicanshu[1]);//倍数
    OLED_Print_Num(0,4,xianshicanshu[2]);
    OLED_Print_Num(0,6,xianshicanshu[3]);
    //OLED_Print_Num(56,0,xianshicanshu[3]);
    //OLED_Print_Num(56,2,xianshicanshu[5]);
    //OLED_Print_Num(56,4,xianshicanshu[6]);
    //OLED_Print_Num(56,6,xianshicanshu[7]);
	
	if(5==read_key()) break; //读按键，按下则进入下个界面
    systick_delay_ms(50);
  
  }
}
//添加菜单
void Add_Menu(uint8 *menu,int16 step)
{
   static uint8 num=0;
   if(num==0) {strcopy(SaveMenu[num],"0.go!!!!");SaveStep[num]=1;num++;}
   strcopy(SaveMenu[num],menu);
   SaveStep[num]=step;
   num++;
}

//第二级菜单
void Next_Menu(uint8 pos)
{
    uint8 i=0;
    char ch[10];
    OLED_Fill(0);
    for(i=pos;i<pos+8;i++)
    {
      if(SaveMenu[i][0]==0) break;                  //全部显示完成，终止
      else 
      {
        OLED_P6x8Str(15,(i-pos),SaveMenu[i]);//显示参数名称
        if(i==0) 
        {
          if(conf[SpeedSelect][i]>1)       conf[SpeedSelect][i]=1;
          else if(conf[SpeedSelect][i]<0) conf[SpeedSelect][i]=0;
          if(conf[SpeedSelect][i]) OLED_P6x8Str(92,(i-pos),"SD");
          else OLED_P6x8Str(92,(i-pos),"NORM"); 
        }
        else 
        {
          sprintf(ch, "%d", conf[SpeedSelect][i]);       
          OLED_P6x8Str(92,(i-pos),ch);//显示参数变量
        }
      }
    }
}   

int16 SpdL=0,SpdR=0;
void precursors_logo(void)
{
  unsigned char x=20,y=0;//x,y位置变量
  unsigned char ch[]={"南京师范大学"};  
  uint8    NextFlag=0;
  while(NextFlag==0)
  {
    SpdL=Speed_Get(0);//读取左旋编
    SpdR=Speed_Get(1);//读取右旋编
    if(SpdL<0) SpdL=-SpdL;
	if(SpdR<0) SpdR=-SpdR;
	
	GyroX=GetData(GYRO_XOUT_H);//读取Roll（水平方向)陀螺仪角速度信号
    GyroY=GetData(GYRO_YOUT_H);//读取Pitch(竖直方向)陀螺仪角速度信号
    if(GyroX<32768) GyroX+=65536;//数据处理
    if(GyroY<32768) GyroY+=65536;//数据处理
	GyroX-=62000;//减小值，方便OLED显示
    GyroY-=62000;//减小值，方便OLED显示
    x=10;
    y=0;
    OLED_P14x16Str(x,y,ch); 
    x=0;
	y=7;
    OLED_P6x8Str( x, y,"SpdL");
    x+=24;
    OLED_Print_Num1( x, y,SpdL);
    x+=40;
    OLED_P6x8Str( x, y,"SpdR");
    x+=24;
    OLED_Print_Num1( x, y,SpdR);
	x=0;
	y=5;
	OLED_P6x8Str( x, y,"GyrY");
	x=24;	                    
	OLED_Print_Num1( x, y,GyroY);
	x=50;
	y=2;
	OLED_P8x16Str(x,y,"SJC"); 
    for(int16 j=0;j<35;j++)
    {
      if(5==read_key()) {NextFlag=1;break;} //按下则进入下个界面
      systick_delay_ms(1);
    }
  }
}

//字符串拷贝函数
void strcopy(uint8 *str1,uint8 *str2)
{
  int16 i;
  for(i=0;i<30;i++)
  {
    str1[i]=str2[i];
    if(str2[i]=='\0') break;
  }
}