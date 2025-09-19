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
u16 Median_Filter(u16 friler_arr[],u8 len)//中值滤波需要从小到大排序
{
	u16 i=0;
  u32 total_sum=0;
	delay_ms(1);
	for(i=0;i<len;i++)
	{
			friler_arr[i] = Get_ADCResult(0);
	}
	sort(friler_arr,len);//数值排序
  // 累加中间30个值
  for(i = 0; i < 30; i++)
	{
      total_sum += friler_arr[10 + i];
			//printf("sumaaa: %u\n", friler_arr[10 + i]);
			//printf("total_sum1: %lu\n", total_sum);
  }
		
    // 计算平均值
		total_sum = total_sum / 30;
	 
   //printf("total_sum2: %lu\n", total_sum);
    return (u16)total_sum;

}






















