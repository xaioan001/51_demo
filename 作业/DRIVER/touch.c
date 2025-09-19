#include "STC8H.H"
#include "type_def.h"
#include "BEEP.h"
#include "touch.h"
u8  xdata B_ReadKeyOk = 0;
u16 xdata TK_cnt[10];
/**
***********************************************************
* @brief   ����������ȡ��ֵ
* @param 
* @return  
***********************************************************
*/
u8 GetTouchVal()
{
	u8  Toucha_val=0;
	u32 Toucha_Longval=0;
	if(TK_cnt[7]>TOUCHKEYVALUETH)
	{
		Toucha_val = 1;
		while(TK_cnt[7]>TOUCHKEYVALUETH)
		{
			if(++Toucha_Longval>TOUCHKEYLONGPRESS)
				{
					Toucha_val=11;
					BeepMs(10);
				}
		}
		BeepMs(10);
		return Toucha_val;
	}
		if(TK_cnt[1]>TOUCHKEYVALUETH)
	{
		Toucha_val = 2;
		while(TK_cnt[1]>TOUCHKEYVALUETH)
		{
		 if(++Toucha_Longval>TOUCHKEYLONGPRESS)
				{
					Toucha_val=22;
					BeepMs(10);
				}
		}
		BeepMs(10);
		return Toucha_val;
	}
		if(TK_cnt[8]>TOUCHKEYVALUETH)
	{
		Toucha_val = 3;
		while(TK_cnt[8]>TOUCHKEYVALUETH)
		{
			if(++Toucha_Longval>TOUCHKEYLONGPRESS)
				{
					Toucha_val=33;
					BeepMs(10);
				}
		}
		BeepMs(10);
		return Toucha_val;
	}
		if(TK_cnt[9]>TOUCHKEYVALUETH)
	{
		Toucha_val = 4;
		while(TK_cnt[9]>TOUCHKEYVALUETH)
		{
			if(++Toucha_Longval>TOUCHKEYLONGPRESS)
				{
					Toucha_val=44;
					BeepMs(10);
				}
		}
		BeepMs(10);		
	}
	return Toucha_val;
}
/**
***********************************************************
* @brief   ������������
* @param 
* @return  
***********************************************************
*/
void Touch_Config()
{
//	TSCHEN = 0xffff;	//TK0~TK15
	TSCHEN1 = 0x82;		//TK0~TK7
	TSCHEN2 = 0x03;		//TK8~TK15
	TSCFG1  = (7<<4) + 6;	//���ص��ݹ���Ƶ�� = fosc/(2*(TSCFG1[6:4]+1)), �ŵ�ʱ��(ϵͳʱ��������) 0(125) 1(250) 2(500) 3(1000) 4(2000) 5(2500) 6(5000) 7(7500) ��С3
	TSCFG2  = 1;		//���ô����������������ڲ��ο���ѹ(AVCC�ķ�ѹ��), 0(1/4)  1(1/2)  2(5/8)  3(3/4)
	TSCTRL = (1<<7) + (1<<5);	//��ʼɨ��, B7: TSGO,  B6: SINGLE,  B5: TSWAIT, B4: TSWUCS, B3: TSDCEN, B2: TSWUEN, B1 B0: TSSAMP
	TSRT = 0x00;		//û��LED��ʱɨ��
	IE2 |= 0x80;		//�����������ж�
}
/**
***********************************************************
* @brief   ���������ж�
* @param 
* @return  
***********************************************************
*/
void	Touch_ISR(void) interrupt 35
{
			u8	j;
						//�û��жϴ������
			j = TSSTA2;

			if(j & 0x40)	//�������, ������(��)
			{
				TSSTA2 |= 0x40;	//д1����
			}
			if(j & 0x80)	//ɨ�����
			{
				j &= 0x0f;
				TSSTA2 |= 0x80;	//д1����

				TK_cnt[j] = TSDAT;	//����ĳ��ͨ���Ķ���	�޵�ͨ�˲�
				//else				TK_cnt[j] = ((TK_cnt[j] * 3)>>2) + TSDAT/16;	//����ĳ��ͨ���Ķ���	��ͨ�˲�
				if(j == 9)	B_ReadKeyOk = 1;	//����һ��ѭ��
			}
}





