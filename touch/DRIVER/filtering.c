#include "type_def.h"
#include "STC8G_H_ADC.h"
#include "uart.h"
#include <stdio.h>
#include "STC8G_H_Delay.h"
/**
***********************************************************
* @brief   ��ֵ�˲��㷨
* @param 
* @return  
***********************************************************
*/
u16 Median_Filter(u16 friler_arr[],u8 len)//�����˲���Ҫ��С��������
{
	u16 i=0;
  u32 sum=0;
	delay_ms(1);
	for(i=0;i<len;i++)
	{
			friler_arr[i] = Get_ADCResult(0);
	}
		sort(friler_arr,len);//��ֵ����
    // �ۼ��м�30��ֵ
    for(i = 0; i < 30; i++) {
        sum += friler_arr[10 + i];
    }
    // ����ƽ��ֵ
		sum = sum / 30;
   //printf("sumaaa: %d\n", sum);
    return (u16)sum;

}






















