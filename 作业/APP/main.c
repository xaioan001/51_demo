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
#include	"STC8G_H_SPI.h"
#include "LCD_DISPLAY.h"
#include "LCD_BASE.h"
#include "Picture.h"
#include "StateMachine.h"
u8 code ledNum[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
float VAL=0;
extern bit B_1S;
u16 xdata friler_arr[50];
//u8 hour=12,min = 0,sec=0;
u8 xdata touchKeyNum = 0;
u16 xdata count=0;
u8 state1=0;
void main()
{	
	
 
	
	
	
	
	P_SW2 |= 0x80;/* 扩展寄存器访问使能 */	
	GPIO_config(); 
	beep_init();
	key_init();
	//Exti_config();
	Timer_config();
	UART_config();
	ADC_config();
	I2C_config();
	Touch_Config();
	RTC_config();
	SPI_config();
	EA=1;
	delay_ms(200);
	LCD_Init();
	LCD_Fill_Black(0,0,320,240);
	//Page_Content_1();
	Page_Content_1(YEAR,MONTH,DAY,HOUR,MIN,SEC,ALAHOUR,ALAMIN,ALASEC,VAL);
//LCD_ShowPicture(60,20,IMG_HEIGHT,IMG_WIDTH,IMG_DATA_1);
	while(1)
	{
		VAL=Median_Filter(friler_arr,50)*3.3f/4096;
		touchKeyNum=GetTouchVal();
		state1= Getstate(touchKeyNum,VAL);//获取状态
		StateMachine(state1,touchKeyNum);//改变状态

		if(count>0)
		{
			BeepMs(200);
			LCD_Fill_Black(0,0,320,240);
	//		LCD_ShowPicture(100,50,IMG_HEIGHT,IMG_WIDTH,IMG_DATA);
			if(touchKeyNum)
			{
				LCD_Fill_Black(0,0,320,240);
				count=0;
			}
		}


		
	}
}

