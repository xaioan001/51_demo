#include	"STC8G_H_GPIO.h"
#include	"STC8G_H_Delay.h"
#define  BEEP  P24

/**
***********************************************************
* @brief   BEEP初始化
* @param 
* @return  
***********************************************************
*/
void	beep_init(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义
	GPIO_InitStructure.Pin  = GPIO_Pin_4;
	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);
}
/**
***********************************************************
* @brief   BEEP
* @param 
* @return  
***********************************************************
*/
void BeepMs(u16 ms)
{
	for(ms; ms > 0; ms--)
	{
		BEEP = ~BEEP;
		delay_ms(1);
	}
	BEEP = 0;
}





