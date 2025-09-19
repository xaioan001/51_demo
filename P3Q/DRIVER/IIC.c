#include	"STC8G_H_I2C.h"
#include "stc8h.h"
#include "intrins.h"
#include "filtering.h"
#include "uart.h"
#include "STC8G_H_Delay.h"
#include "STC8G_H_ADC.h"
#include	"STC8G_H_Timer.h"
u32 sysT0tick;
u16 ADC_VAL;
u16 xdata adc_arr[50];
u16 xdata adc_val30[30];
u16 Data;
u8 data_low ;
u8 data_high;
u8 j;
/**
***********************************************************
* @brief   外部IIC存储60s读取数据
* @param 
* @return  
***********************************************************
*/
u16 IIC_60S(void)
{	
		if(time0IntNum-sysT0tick>60000)
		{		sysT0tick=time0IntNum;
				for(j=0;j<50;j++)
				{
					adc_arr[j]=Get_ADCResult(0);
				}
				sort(adc_arr,50);//数值排序
				for(j=0;j<30;j++)
				{
				adc_val30[j]=adc_arr[j+10];
				data_low = (u8)(adc_val30[j] & 0xFF);        // 低字节
				data_high = (u8)((adc_val30[j] >> 8) & 0xFF); // 高字节
				I2C_WriteNbyte(DEV_ADDR, j * 2, &data_low, 1);     // 寄存器地址 j*2
				delay_ms(5); // AT24C02需要写入时间      
				I2C_WriteNbyte(DEV_ADDR, j * 2 + 1, &data_high, 1); // 寄存器地址 j*2+1
				delay_ms(5);
				I2C_ReadNbyte(DEV_ADDR, j * 2, &data_low,1);
				delay_ms(5);
				I2C_ReadNbyte(DEV_ADDR, j * 2 + 1, &data_high,1);
				Data = (u16)data_low|((u16)data_high << 8);
				delay_ms(5);
				printf("result: %d\n", Data);
				
			}
		}
	ADC_VAL=Median_Filter(adc_arr,50);
	return ADC_VAL;
}
/**
***********************************************************
* @brief   开启内部eep功能
* @param 
* @return  
***********************************************************
*/
void IapIdle()//关闭IAP
{
	IAP_CONTR =0;
	IAP_CMD=0;
	IAP_TRIG=0;
	IAP_ADDRH=0x80;
	IAP_ADDRL=0;
}
/**
***********************************************************
* @brief   读取内部eep数据
* @param 
* @return  
***********************************************************
*/
u16 IapRead(u16 addr)//读数据
{		u8 dat;
		IAP_CONTR =0x80;
		IAP_TPS= 24;
		IAP_CMD=0x01;
		IAP_ADDRL=addr;
		IAP_ADDRH=addr>>8;
		IAP_TRIG=0x5a;
		IAP_TRIG=0xa5;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		dat= IAP_DATA;
		IapIdle();
		return dat;
}
/**
***********************************************************
* @brief   写入内部eep数据
* @param 
* @return  
***********************************************************
*/
void lapProgram(u16 addr, u8 dat)//写数据
{
  IAP_CONTR=0x80,
	IAP_TPS=24;
	IAP_CMD =0x02;
	IAP_ADDRL=addr;
	IAP_ADDRH=addr >> 8;
	IAP_DATA=dat;
	IAP_TRIG=0x5a;
	IAP_TRIG =0xa5;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
	IapIdle();
}
/**
***********************************************************
* @brief   擦除内部eep数据
* @param 
* @return  
***********************************************************
*/
void IapErase(u16 addr)//擦除数据
{
		IAP_CONTR=0x80;
		IAP_TPS=24;
		IAP_CMD =0x03;
		IAP_ADDRL =addr;
		IAP_ADDRH=addr>> 8;
		IAP_TRIG=0x5a;
		IAP_TRIG= 0xa5;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		IapIdle();
}











