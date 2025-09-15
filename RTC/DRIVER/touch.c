#include "STC8H.H"
#include "type_def.h"
#include "BEEP.h"
#include "touch.h"
u8  xdata B_ReadKeyOk = 0;
u16 xdata TK_cnt[10];
/**
***********************************************************
* @brief   触摸按键获取键值
* @param 
* @return  
***********************************************************
*/
u8 GetTouchVal()
{
	u8  Toucha_val=0;
	u32 Toucha_Longval=0;
	if(TK_cnt[7]>TOUCHKEYVALUETH)
	{
		Toucha_val = 1;
		while(TK_cnt[7]>TOUCHKEYVALUETH)
		{
			if(++Toucha_Longval>TOUCHKEYLONGPRESS)
				{
					Toucha_val=11;
					BeepMs(10);
				}
		}
		BeepMs(10);
		return Toucha_val;
	}
		if(TK_cnt[1]>TOUCHKEYVALUETH)
	{
		Toucha_val = 2;
		while(TK_cnt[1]>TOUCHKEYVALUETH)
		{
		 if(++Toucha_Longval>TOUCHKEYLONGPRESS)
				{
					Toucha_val=22;
					BeepMs(10);
				}
		}
		BeepMs(10);
		return Toucha_val;
	}
		if(TK_cnt[8]>TOUCHKEYVALUETH)
	{
		Toucha_val = 3;
		while(TK_cnt[8]>TOUCHKEYVALUETH)
		{
			if(++Toucha_Longval>TOUCHKEYLONGPRESS)
				{
					Toucha_val=33;
					BeepMs(10);
				}
		}
		BeepMs(10);
		return Toucha_val;
	}
		if(TK_cnt[9]>TOUCHKEYVALUETH)
	{
		Toucha_val = 4;
		while(TK_cnt[9]>TOUCHKEYVALUETH)
		{
			if(++Toucha_Longval>TOUCHKEYLONGPRESS)
				{
					Toucha_val=44;
					BeepMs(10);
				}
		}
		BeepMs(10);		
	}
	return Toucha_val;
}
/**
***********************************************************
* @brief   触摸按键配置
* @param 
* @return  
***********************************************************
*/
void Touch_Config()
{
//	TSCHEN = 0xffff;	//TK0~TK15
	TSCHEN1 = 0x82;		//TK0~TK7
	TSCHEN2 = 0x03;		//TK8~TK15
	TSCFG1  = (7<<4) + 6;	//开关电容工作频率 = fosc/(2*(TSCFG1[6:4]+1)), 放电时间(系统时钟周期数) 0(125) 1(250) 2(500) 3(1000) 4(2000) 5(2500) 6(5000) 7(7500) 最小3
	TSCFG2  = 1;		//配置触摸按键控制器的内部参考电压(AVCC的分压比), 0(1/4)  1(1/2)  2(5/8)  3(3/4)
	TSCTRL = (1<<7) + (1<<5);	//开始扫描, B7: TSGO,  B6: SINGLE,  B5: TSWAIT, B4: TSWUCS, B3: TSDCEN, B2: TSWUEN, B1 B0: TSSAMP
	TSRT = 0x00;		//没有LED分时扫描
	IE2 |= 0x80;		//允许触摸按键中断
}
/**
***********************************************************
* @brief   触摸按键中断
* @param 
* @return  
***********************************************************
*/
void	Touch_ISR(void) interrupt 35
{
			u8	j;
						//用户中断处理代码
			j = TSSTA2;

			if(j & 0x40)	//数据溢出, 错误处理(略)
			{
				TSSTA2 |= 0x40;	//写1清零
			}
			if(j & 0x80)	//扫描完成
			{
				j &= 0x0f;
				TSSTA2 |= 0x80;	//写1清零

				TK_cnt[j] = TSDAT;	//保存某个通道的读数	无低通滤波
				//else				TK_cnt[j] = ((TK_cnt[j] * 3)>>2) + TSDAT/16;	//保存某个通道的读数	低通滤波
				if(j == 9)	B_ReadKeyOk = 1;	//读完一次循环
			}
}





