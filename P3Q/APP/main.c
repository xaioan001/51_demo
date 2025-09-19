#include "STC8H.H"
#include "STC8G_H_GPIO.h"
#include "STC8G_H_Delay.h"
#include "config.h"
#include "BEEP.h"
#include "type_def.h"
#include "STC8G_H_Timer.h"
#include "STC8G_H_UART.h"
#include "touch.h"
void main()
{	
	u32 sysT0Tick;
	u8 Touch_TEMP=0;
	P_SW2 |= 0x80;/* 扩展寄存器访问使能 */	
	GPIO_config(); 
	beep_init();
	Timer_config();
	UART_config();
	Touch_Config();
	EA=1;
	SaveTouchZeroValue(); //保存触摸零点值
	while(1)
	{
			Touch_TEMP=GetTouchVal();
		//ADC_TEMP = IIC_60S();
    if(time0IntNum-sysT0Tick>1000)
		{
			sysT0Tick=time0IntNum;
//			printf("TK1 = %u.\n",TK_cnt[14]);
//			printf("TK1 = %u.\n",TK_cnt[13]);
//			printf("TK1 = %u.\n",TK_cnt[12]);
//			printf("TK1 = %u.\n",TK_cnt[7]);
//			printf("TK1 = %u.\n",TK_cnt[6]);
		
		}
	}
}

