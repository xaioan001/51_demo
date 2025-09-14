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
u8 code ledNum[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
u8 xdata arr[30];
void main()
{	
	u16 ADC_TEMP;
	u8 key_val=0,at24dat,writeNum,readNum,clear=255;
	
	
	P_SW2 |= 0x80;/* 扩展寄存器访问使能 */	
	GPIO_config(); 
	beep_init();
	key_init();
	Exti_config();
	Timer_config();
	UART_config();
	ADC_config();
	I2C_config();
	EA=1;

	while(1)
	{
	
			ADC_TEMP = IIC_60S();
		
		key_val=SingleKey();
		if(key_val==1)
		{
			IapErase(arr[30]);
			for(writeNum=0;writeNum<10;writeNum++)
			{
				at24dat=rand();
				lapProgram(arr[writeNum], at24dat);
//				I2C_WriteNbyte(DEV_ADDR, writeNum,&at24dat, 1);				
				printf("writeNum %bu rand = %bu\n",writeNum,at24dat);
				delay_ms(1000);
			}
		 if(writeNum>=10)
			{
					BeepMs(100);
			}
		}
		if(key_val==2)
		{
					for(readNum=0;readNum<10;readNum++)
					{			
								at24dat=IapRead(arr[readNum]);
								//I2C_ReadNbyte(DEV_ADDR, readNum, &at24dat,1);
								printf("readNum %bu rand = %bu\n",readNum,at24dat);	
//								for( i = 0; i < 100; i++)   // 刷新100次，大约1秒
//								{
//										DisplayAnyNum(at24dat); // 显示数字
//										delay_ms(10);           // 短暂延迟
//								}
							
								delay_ms(1000);						
					}			
					if(readNum>=10)
					{
						BeepMs(100);
					}
		}							
		if(key_val==3)
			{
				readNum=0;
				writeNum=0;
			}
		if(key_val==4)
		{
			for(writeNum=0;writeNum<10;writeNum++)
			{
				I2C_WriteNbyte(DEV_ADDR, writeNum,&clear, 1);
				printf("writeNum %bu rand = %bu\n",writeNum,clear);
			}
		}
		
		delay_ms(1);
//		uart1tx_uart2rx();
		
		DisplayAnyNum(ADC_TEMP);
	}
}

