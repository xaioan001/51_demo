#include "type_def.h"
#include "STC8G_H_UART.h"
#include <string.h>
#include "STC8G_H_Delay.h"
#include <stdio.h>
u8 code atarr[]={"AT+TIME="};
extern u8 key1;
void sort(u16 Data[],u8 len)
{
    u16 i, j, temp;
    for (i = 0; i < len-1; i++) {
        for (j = 0; j < len-i-1; j++) {
            if (Data[j] > Data[j+1]) {
                // ����arr[j]��arr[j+1]
                temp = Data[j];
                Data[j] = Data[j+1];
                Data[j+1] = temp;
								
            }
        }
    }
}

/**
***********************************************************
* @brief   ����1���� ����2����
* @param 
* @return  
***********************************************************
*/
void uart1tx_uart2rx()
{
		u8 i;

	if(COM1.RX_TimeOut > 0)		//��ʱ����
			{
				if(--COM1.RX_TimeOut == 0)
				{
					if(COM1.RX_Cnt > 0)
					{
			
						TX1_write2buff(COM1.RX_Cnt);  //����2��ȡ����1���ݺ���㴮��1�������ݵ�����
						
						//sort(RX1_Buffer,COM1.RX_Cnt); //ʵ�ִ���1�����������ݣ����������
						
						for(i=0; i<COM1.RX_Cnt; i++)	TX1_write2buff(RX1_Buffer[i]);	//�յ�������ԭ������
					}																//����2���ʹ���1�����������ݷ��ظ�����1
					COM1.RX_Cnt = 0;
				}
			}
	
	if(COM4.RX_TimeOut > 0)		//��ʱ����
			{
				if(--COM4.RX_TimeOut == 0)
				{
					if(COM4.RX_Cnt > 0)
					{
						TX4_write2buff(COM4.RX_Cnt);
						//sort(RX2_Buffer,COM2.RX_Cnt);
						for(i=0; i<COM4.RX_Cnt; i++)	TX4_write2buff(RX4_Buffer[i]);	//�յ�������ԭ������
					}
					COM4.RX_Cnt = 0;
				}
		}
			
			
		
			
}
			


 



