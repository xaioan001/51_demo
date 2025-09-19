#include "config.h"
#include "STC8G_H_Delay.h"
#define   SER595  P41
#define   RCK595  P76
#define   SCK595  P77
//extern u8 encoder_count1;
//extern u8 encoder_count2;
u8 i;
u8 code TableDU[]={0x3f,0x06,0x5b,0x4f,
									 0x66,0x6d,0x7d,0x07,
									 0x7f,0x6f,0x77,0x7c,
									 0x39,0x5e,0x79,0x00};
u8 code TableWE[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};	



/**
***********************************************************
* @brief 驱动595，写一个字节
* @param 
* @return 
***********************************************************
*/
void Hc595WriteByte(u8 Data)
{
	u8 k;
	for(k=0;k<8;k++)
	{
		SCK595=0;
		Data=Data<<1;
		SER595=CY;
		SCK595=1;
	}
}
/**
***********************************************************
* @brief 让74H595输出
* @param 
* @return 
***********************************************************
*/
void DisplayNum(u8 num,u8 dat)
{
	
	Hc595WriteByte(TableDU[dat]);//必须先送段
	Hc595WriteByte(TableWE[num-1]);
	RCK595=0;
	RCK595=1;
}
/**
***********************************************************
* @brief 显示任意5位数，65535以内
* @param disnum，要显示的数字
* @return 
***********************************************************
*/
//void DisplayAny1_Num(u32 disnum);
//{
//	long xdata qianwan,baiwan,shiwan,wan,qian,bai,shi,ge;
//	qianwan=disnum/10000000;
//	baiwan=disnum%10000000/1000000;
//	shiwan=disnum%1000000/100000;
//	wan = disnum %100000 /10000;
//	qian = disnum % 10000 / 1000;
//	bai = disnum % 1000 / 100;
//	shi = disnum % 100 / 10;
//	ge = disnum % 10;
//	if(qianwan != 0)
//	{
//		DisplayNum(1,qianwan);
//		delay_ms(1);
//	}
//	if((baiwan != 0)||(shiwan!=0))
//	{
//		DisplayNum(2,baiwan);
//		delay_ms(1);
//	}	
//	if((shiwan != 0)||(baiwan != 0)||(qianwan != 0))
//	{
//		DisplayNum(3,shiwan);
//		delay_ms(1);
//	}
//		
//	if((wan != 0)||(shiwan!=0)||(baiwan != 0)||(qianwan != 0))
//	{			
//			DisplayNum(4,wan);
//			delay_ms(1);
//	}
//	if((qian != 0) ||  (wan != 0)||(shiwan!=0)||(baiwan != 0)||(qianwan != 0))
//	{				
//			DisplayNum(5,qian);
//			delay_ms(1);
//	}
//	if((bai != 0) || (qian != 0) || (wan != 0)||(shiwan!=0)||(baiwan != 0)||(qianwan != 0))
//	{		
//		DisplayNum(6,bai);
//		delay_ms(1);
//	}
//	 if((shi != 0) ||(bai != 0) || (qian != 0) || (wan != 0)||(baiwan != 0)||(shiwan!=0)||(qianwan != 0))
//	 {
//		 DisplayNum(7,shi);
//		 delay_ms(1);
//	 }	
//		
////	  if(ge<0)
////	 {
////		 
////		 DisplayNum(8,ge);
////	 }
//	 	 if(((encoder_count2-encoder_count1)/20)>0)
//		 {
//			 DisplayNum(7,16);
//			 		 delay_ms(1);

//		 }
//		 DisplayNum(8,ge);
//	
//}


 void DisplayAnyNum(u16 disnum)
{
	u8 wan,qian,bai,shi,ge;
	wan = disnum / 10000;
	qian = disnum % 10000 / 1000;
	bai = disnum % 1000 / 100;
	shi = disnum % 100 / 10;
	ge = disnum % 10;	
	if(wan != 0)
	{
		DisplayNum(4,wan);
		delay_ms(1);
	}
		if((qian != 0) ||  (wan != 0))
	{
		DisplayNum(5,qian);
		delay_ms(1);
	}
			if((bai != 0) || (qian != 0) || (wan != 0))
	{
		DisplayNum(6,bai);
		delay_ms(1);
	}
		if((shi != 0) ||(bai != 0) || (qian != 0) || (wan != 0))	
	{
		DisplayNum(7,shi);
		delay_ms(1);
	}
		DisplayNum(8,ge);
		//delay_ms(10);
}

//void test_display(u8 disnum)
//{		
//		i++;
//		DisplayNum(i,disnum);
//		delay_ms(10);		
//		if(i>=8)
//		{
//			i=0;
//			delay_ms(10);			
//		}
//}











