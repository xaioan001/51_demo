#include <STC8H.H>
#include "type_def.h"
#include  "Beep.h"
#include 	"Touch.h"
#include	"STC8G_H_Delay.h"

u8 B_ReadKeyOk = 0;
u16 TK_cnt[15] = 0;
u16 TK_zero[15] = 0;

/**
***********************************************************
* @brief  触摸按键的配置函数
* @param  
* @param  
* @return 
***********************************************************
*/

void Touch_config()
{
	TSCHEN1 = 0xC0;		//1100 0000  TK6、7
	TSCHEN2 = 0x70;		//0111 0000    TK12、13、14
	TSCFG1  = (1<<4) + 6;	//开关电容工作频率 = fosc/(2*(TSCFG1[6:4]+1)), 放电时间(系统时钟周期数) 0(125) 1(250) 2(500) 3(1000) 4(2000) 5(2500) 6(5000) 7(7500) 最小3
	TSCFG2  = 1;		//配置触摸按键控制器的内部参考电压(AVCC的分压比), 0(1/4)  1(1/2)  2(5/8)  3(3/4)
//	TSCTRL = (1<<7) + (1<<5);	//开始扫描, B7: TSGO,  B6: SINGLE,  B5: TSWAIT, B4: TSWUCS, B3: TSDCEN, B2: TSWUEN, B1 B0: TSSAMP
	TSRT = 0x00;		//没有LED分时扫描
	IE2 |= 0x80;		//允许触摸按键中断	
}

/**
***********************************************************
* @brief   获取触摸按键的键值
* @param  
* @param  
* @return  返回u8 型对应的键值序号，1，2，3，4
***********************************************************
*/
u8 GetTouchVal()
{
	u8 touchKeyValue = 0;
	u32 touchLongPressCount = 0;
	u16 tkChaVal = 0;
	if(B_ReadKeyOk)
	{
		B_ReadKeyOk = 0;
		tkChaVal = TK_zero[14] - TK_cnt[14];
		if((tkChaVal > TOUCHKEYVALUETH)&&(tkChaVal < TOUCHKEYMAX))
		{
			touchKeyValue = 1;
			while((TK_zero[14] - TK_cnt[14]) > TOUCHKEYVALUETH);		
			BeepMs(10);
			return touchKeyValue;
		}
		tkChaVal = TK_zero[13] - TK_cnt[13];
		if((tkChaVal > TOUCHKEYVALUETH)&&(tkChaVal < TOUCHKEYMAX))
		{
			touchKeyValue = 2;
			while((TK_zero[13] - TK_cnt[13]) > TOUCHKEYVALUETH)
			{
				if(++touchLongPressCount > TOUCHKEYLONGPRESS)
				{
					touchKeyValue = 22;
					BeepMs(10);
				}
			}				
			BeepMs(10);
			return touchKeyValue;
		}		
		tkChaVal = TK_zero[12] - TK_cnt[12];
		if((tkChaVal > TOUCHKEYVALUETH)&&(tkChaVal < TOUCHKEYMAX))
		{
			touchKeyValue = 3;
			while((TK_zero[12] - TK_cnt[12]) > TOUCHKEYVALUETH);		
			BeepMs(10);
			return touchKeyValue;
		}		
		tkChaVal = TK_zero[7] - TK_cnt[7];
		if((tkChaVal > TOUCHKEYVALUETH)&&(tkChaVal < TOUCHKEYMAX))
		{
			touchKeyValue = 4;
			while((TK_zero[7] - TK_cnt[7]) > TOUCHKEYVALUETH);		
			BeepMs(10);
			return touchKeyValue;
		}
		tkChaVal = TK_zero[6] - TK_cnt[6];
		if((tkChaVal > TOUCHKEYVALUETH)&&(tkChaVal < TOUCHKEYMAX))
		{
			touchKeyValue = 5;
			while((TK_zero[6] - TK_cnt[6]) > TOUCHKEYVALUETH)
			{
				if(++touchLongPressCount > TOUCHKEYLONGPRESS)
				{
					touchKeyValue = 55;
					BeepMs(10);
				}
			}				
			BeepMs(10);
			return touchKeyValue;
		}			
	}
	return touchKeyValue;
}

/**
***********************************************************
* @brief 保存上电时，没有按下触摸时的零点值
* @param  
* @param  
* @return 
***********************************************************
*/

void SaveTouchZeroValue()
{
	u8 i = 0;
	for(i = 0; i < 20; i++)
	{
		TSCTRL = (1<<7) + (1<<6);
		delay_ms(20);
	}
	for(i = 0; i < 15; i++)
	{
		TK_zero[i] = TK_cnt[i];//保存零点
		printf("TK%bu = %u.\n",i,TK_zero[i]);
	}	
	
}


/**
***********************************************************
* @brief   触摸按键的中断服务程序
* @param  
* @param  
* @return 
***********************************************************
*/
void	Touch_ISR(void) interrupt 35
{
	u8	j;
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
		if(j == 14)	B_ReadKeyOk = 1;	//读完一次循环
	}
}

