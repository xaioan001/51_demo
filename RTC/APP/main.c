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
#include	"STC8H_RTC.h"
u8 code ledNum[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
//u8 xdata arr[30];
extern bit B_1S;
void main()
{	
	u8 Touch_TEMP=0;
	static u8 display_mode = 0; // 0:显示时间, 1:显示日期
	//u8 key_val=0,at24dat,writeNum,readNum,clear=255;
	
	u8 hour=0,min = 0,sec=0;;
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
	RTC_config();
	EA=1;

	while(1)
	{
		Touch_TEMP=GetTouchVal();
		if(Touch_TEMP != 0) // 按下时有值
		{
				// 切换显示模式
			if(Touch_TEMP==1)display_mode = 1;
			if(Touch_TEMP==2)display_mode = 2;	
				// 等待按键释放（防抖）
				while(GetTouchVal() != 0) {
        delay_ms(10);
			}
		}
		// 根据模式显示相应内容
		if(display_mode == 1) {
				Display_time(HOUR, MIN, SEC);
		} else if(display_mode == 2) {
				Display_Day(YEAR, MONTH, DAY);
		}
		printf("Touch_TEMP = %bd\r\n",Touch_TEMP);
		printf("display_mode = %bd\r\n",display_mode);
//    if(Touch_TEMP)
//		{
//			
//			printf("TK_cnt = %bu.\n",Touch_TEMP);
//		
//		}
//		if(B_1S)
//		{
//			B_1S = 0;
			printf("20%bd/%bd/%bd,/%bd:%bd:%bd\r\n",YEAR,MONTH,DAY,HOUR,MIN,SEC);
//		}


		
	}
}

