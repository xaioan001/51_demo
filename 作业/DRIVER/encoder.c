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
//* @brief   1*4单按键显示值
//* @param 
//* @return  返回按键的值
//***********************************************************
//*/
//void encoder()
//{ 	
//	current_A= P34;
//		if (current_A != last_A_state)
//		{
//      // 在A相变化的时刻，读取B相的状态
//      if (current_A == 0) 
//				{ // 如果检测的是下降沿
//					if (P35 == 0) 
//						{
//						encoder_count1++; // 顺时针，B相为低
//						}
//					else {
//						encoder_count2++; // 逆时针，B相为高
//					}
//				}
//      // 更新上一次的状态
//      last_A_state = current_A;
//    }
//	//	keyval=encoder_count/20;
//		if(encoder_count1>=0)//一直正转
//		{  
//			keyval=encoder_count1/20;
//		}
//		if((encoder_count1>0)&&(encoder_count2>0))//先正转x圈后反转
//		{
//			keyval=(encoder_count1-encoder_count2)/20;
//		}
//		if(encoder_count2>encoder_count1)//直接反转
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