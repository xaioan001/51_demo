#include "type_def.h"
#include "STC8G_H_ADC.h"
#include "uart.h"
#include <stdio.h>
#include "STC8G_H_Delay.h"
/**
***********************************************************
* @brief   中值滤波算法
* @param 
* @return  
***********************************************************
*/
u16 Median_Filter(u16 friler_arr[],u8 len)//中智滤波需要从小到大排序
{
	u16 i=0;
  u32 sum=0;
	delay_ms(1);
	for(i=0;i<len;i++)
	{
			friler_arr[i] = Get_ADCResult(0);
	}
		sort(friler_arr,len);//数值排序
    // 累加中间30个值
    for(i = 0; i < 30; i++) {
        sum += friler_arr[10 + i];
    }
    // 计算平均值
		sum = sum / 30;
   //printf("sumaaa: %d\n", sum);
    return (u16)sum;

}






















