#include "STC8H.H"
#include "STC8G_H_GPIO.h"
#include "STC8G_H_Delay.h"
#include "config.h"
#include "BEEP.h"
#include "key.h"
#include "type_def.h"
#include "STC8G_H_Exti.h"
#include "Digitalled.h"
#include "STC8G_H_Timer.h"
#include "STC8G_H_UART.h"
#include "uart.h"
#include "STC8G_H_ADC.h"
#include "filtering.h"
#include "STC8G_H_I2C.h"
#include "IIC.h"
#include "touch.h"
u8 code ledNum[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
//u8 xdata arr[30];
void main()
{	
	u8 Touch_TEMP=0;
	//u8 key_val=0,at24dat,writeNum,readNum,clear=255;
	
	
	P_SW2 |= 0x80;/* 扩展寄存器访问使能 */	
	GPIO_config(); 
	beep_init();
	key_init();
	Exti_config();
	Timer_config();
	UART_config();
	ADC_config();
	I2C_config();
	Touch_Config();
	EA=1;

	while(1)
	{
			Touch_TEMP=GetTouchVal();
		//ADC_TEMP = IIC_60S();
    if(Touch_TEMP)
		{
			
			printf("TK_cnt = %bu.\n",Touch_TEMP);
		
		}
	}
}

