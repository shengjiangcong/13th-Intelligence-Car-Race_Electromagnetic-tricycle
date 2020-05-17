#include "headfile.h"
#include "main.h"
uint16 speedl, speedr;
int16   conf[3][ConfigNum];

int main(void)
{
    DisableInterrupts ;  
    systick_delay_ms(200);
    get_clk(); 
    sys_init();
    EnableInterrupts; 
    
	while(1)
    {
        ;
		  //1.防撞去掉ok
		 //2.颠簸接十字（小环annularwhat修改到不需要斜电感）
		
		 //4.中环大环进环抖动优化ok
		 //5.改善结构美观
		 //6.调两套速度参数变速和匀速（检测入弯）ok
		 //7.防止误判优化
		 //8.大环加速ok
		
		 //起跑线附近横电感2300电位器调节  竖电感2450  斜电感1900 中间电感1970
		
		
/*准备物品：电脑 充电器 手机充电器 钱包 耳机 鼠标 餐巾纸 水杯 防蚊液
           比赛用品：一字螺丝刀ok  垂直握把ok 机敏螺丝ok 十字板ok 电池 电感对备用ok 主板备用ok 驱动备用ok 运放备用ok 陀螺仪备用ok 干簧管备用（要先焊好）ok
                     与主板对应的fpc线ok 电机备用ok 碳素竿备用（长的）ok 黑白胶带ok 剪刀ok 螺丝螺帽垫片 轮子备用ok 轮子里的插针齿轮等ok 轮轴备用ok
                     漆包线ok 白胶和胶枪ok  万向轮备用ok 杜邦线（缺少公母）ok 502胶ok 704胶ok 电烙铁ok 锡线ok 五项开关ok 插针ok 屏幕ok 开关ok 
                     电池连接的插槽ok 直尺ok 砂纸ok 胎胶ok 日本进口ok 静电液ok 小刀ok 万用表 电池支架ok 电池膀扎带ok 旋转编码器ok 抹布 jlink 
                     路肩ok 各种螺丝刀等等ok 电池充电器多个 赛道ok 电磁线0.5 信号源 粘灰器ok 刷子ok 针筒ok 镊子ok 电源线ok 铜箔ok 

        */
			
			//1.驱动测试了吗？ok
			//2.运放测试了吗？ok
			//3.旋编测试了吗？ok
			//4.陀螺仪测试了吗？
			//5.

           
		
    }
}
