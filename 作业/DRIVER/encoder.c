//#include	"STC8G_H_GPIO.h"
//#include "type_def.h"
//#include	"STC8G_H_Delay.h"
//#include "BEEP.h"
//#include	"STC8G_H_Exti.h"
//#define PIN_ENCODER_A    P34    
//#define PIN_ENCODER_B    P35
//#define PIN_ENCODER_KEY  P36
//extern u32 count;
//u8 encoder_count1;
//u8 encoder_count2;
//u8 current_A ;
//u8 keyval;
////extern u8 last_A_state ;
///**
//***********************************************************
//* @brief   1*4��������ʾֵ
//* @param 
//* @return  ���ذ�����ֵ
//***********************************************************
//*/
//void encoder()
//{ 	
//	current_A= P34;
//		if (current_A != last_A_state)
//		{
//      // ��A��仯��ʱ�̣���ȡB���״̬
//      if (current_A == 0) 
//				{ // ����������½���
//					if (P35 == 0) 
//						{
//						encoder_count1++; // ˳ʱ�룬B��Ϊ��
//						}
//					else {
//						encoder_count2++; // ��ʱ�룬B��Ϊ��
//					}
//				}
//      // ������һ�ε�״̬
//      last_A_state = current_A;
//    }
//	//	keyval=encoder_count/20;
//		if(encoder_count1>=0)//һֱ��ת
//		{  
//			keyval=encoder_count1/20;
//		}
//		if((encoder_count1>0)&&(encoder_count2>0))//����תxȦ��ת
//		{
//			keyval=(encoder_count1-encoder_count2)/20;
//		}
//		if(encoder_count2>encoder_count1)//ֱ�ӷ�ת
//		{
//			keyval=(encoder_count2-encoder_count1)/20;
//		}
////		else if(encoder_count1<0)
////		  keyval=(encoder_count1)/20;
//		   
////		if(KEY1 == 0)
////		{
////			delay_ms(10);
////			if(KEY1 == 0)
////			{
////				count=0;
////				while(!KEY1);
////			}
////			BeepMs(10);
////		}
//	if(P36 == 0)
//	{
//		delay_ms(10);
//		if(P36 == 0)
//		{
//			encoder_count1=0;
//			encoder_count2=0;
//		}
//		BeepMs(10);
//		
//	}	
//}	