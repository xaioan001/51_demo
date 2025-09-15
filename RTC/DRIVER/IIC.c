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
* @brief   �ⲿIIC�洢60s��ȡ����
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
				sort(adc_arr,50);//��ֵ����
				for(j=0;j<30;j++)
				{
				adc_val30[j]=adc_arr[j+10];
				data_low = (u8)(adc_val30[j] & 0xFF);        // ���ֽ�
				data_high = (u8)((adc_val30[j] >> 8) & 0xFF); // ���ֽ�
				I2C_WriteNbyte(DEV_ADDR, j * 2, &data_low, 1);     // �Ĵ�����ַ j*2
				delay_ms(5); // AT24C02��Ҫд��ʱ��      
				I2C_WriteNbyte(DEV_ADDR, j * 2 + 1, &data_high, 1); // �Ĵ�����ַ j*2+1
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
* @brief   �����ڲ�eep����
* @param 
* @return  
***********************************************************
*/
void IapIdle()//�ر�IAP
{
	IAP_CONTR =0;
	IAP_CMD=0;
	IAP_TRIG=0;
	IAP_ADDRH=0x80;
	IAP_ADDRL=0;
}
/**
***********************************************************
* @brief   ��ȡ�ڲ�eep����
* @param 
* @return  
***********************************************************
*/
u16 IapRead(u16 addr)//������
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
* @brief   д���ڲ�eep����
* @param 
* @return  
***********************************************************
*/
void lapProgram(u16 addr, u8 dat)//д����
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
* @brief   �����ڲ�eep����
* @param 
* @return  
***********************************************************
*/
void IapErase(u16 addr)//��������
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











