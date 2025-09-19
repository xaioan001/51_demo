#include	"STC8G_H_GPIO.h"
#include "type_def.h"
#include	"STC8G_H_Delay.h"
#include "BEEP.h"
#define  LONGPRESSTIME  100000
/**
***********************************************************
* @brief   按键初始化
* @param 
* @return  
***********************************************************
*/
void	key_init(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义

	GPIO_InitStructure.Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.Mode = GPIO_PullUp;
	GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);	
}
/**
***********************************************************
* @brief   1*4单按键显示值
* @param 
* @return  返回按键的值
***********************************************************
*/
u8 SingleKey()
{

	u8 KEYVAL1;
	u32 longpressNum=0;
	if(P32 == 0)
	{
		delay_ms(10);
		if(P32 == 0)
		{
			KEYVAL1=1;
			while(!P32)
			{
				if(++longpressNum>LONGPRESSTIME)
				{
					KEYVAL1=11;
					BeepMs(10);
				}
			}				
		}
		BeepMs(10);
		return KEYVAL1;
	}
	if(P33 == 0)
	{
		delay_ms(10);
		if(P33 == 0)
		{
			while(!P33);
		}
		BeepMs(10);
		return 2;
	}
	if(P34 == 0)
	{
		delay_ms(10);
		if(P34 == 0)
		{
			while(!P34);
		}
		BeepMs(10);
		return 3;
	}
	if(P35 == 0)
	{
		delay_ms(10);
		if(P35 == 0)
		{
			while(!P35);
		}
		BeepMs(10);
		return 4;
	}	
	return 0;
}

