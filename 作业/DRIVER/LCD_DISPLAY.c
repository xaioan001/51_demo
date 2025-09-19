#include "LCD_DISPLAY.h"
#include "LCD_BASE.h"
#include "STC8H.H"
#include "STC8G_H_Delay.h"
#include	"STC8H_RTC.h"
#include	"STC8G_H_SPI.h"
#include "type_def.h"
#include "config.h"
#include <stdio.h>
//extern u8 hour,min,sec;
/******************************************************************************
      函数说明：LCD初始化函数
      入口数据：无
      返回值：  无
******************************************************************************/
void LCD_Init(void)
{
	LCD_RES=0;    // 复位液晶屏
	delay_ms(200);
	LCD_RES=1;	
	delay_ms(200);
	
	LCD_WR_REG(0x11);           //Sleep out 
	delay_ms(120);              //Delay 120ms 
	LCD_WR_REG(0x36);
//	if(USE_HORIZONTAL==2)  // 横屏 ,如果想反过来显示，可激活这条语句
//		LCD_WR_DATA8(0x70);
  if(USE_HORIZONTAL==3)
	{
		LCD_WR_DATA8(0xA0);  // 横屏 
	}
	
	LCD_WR_REG(0x3A);			
	LCD_WR_DATA8(0x05);

	LCD_WR_REG(0xB2);			
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x0C); 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x33); 
	LCD_WR_DATA8(0x33); 			

	LCD_WR_REG(0xB7);			
	LCD_WR_DATA8(0x35);

	LCD_WR_REG(0xBB);			
	LCD_WR_DATA8(0x32); //Vcom=1.35V
					
	LCD_WR_REG(0xC2);
	LCD_WR_DATA8(0x01);

	LCD_WR_REG(0xC3);			
	LCD_WR_DATA8(0x15); //GVDD=4.8V  颜色深度
				
	LCD_WR_REG(0xC4);			
	LCD_WR_DATA8(0x20); //VDV, 0x20:0v

	LCD_WR_REG(0xC6);			
	LCD_WR_DATA8(0x0F); //0x0F:60Hz        	

	LCD_WR_REG(0xD0);			
	LCD_WR_DATA8(0xA4);
	LCD_WR_DATA8(0xA1); 

	LCD_WR_REG(0xE0);
	LCD_WR_DATA8(0xD0);   
	LCD_WR_DATA8(0x08);   
	LCD_WR_DATA8(0x0E);   
	LCD_WR_DATA8(0x09);   
	LCD_WR_DATA8(0x09);   
	LCD_WR_DATA8(0x05);   
	LCD_WR_DATA8(0x31);   
	LCD_WR_DATA8(0x33);   
	LCD_WR_DATA8(0x48);   
	LCD_WR_DATA8(0x17);   
	LCD_WR_DATA8(0x14);   
	LCD_WR_DATA8(0x15);   
	LCD_WR_DATA8(0x31);   
	LCD_WR_DATA8(0x34);   

	LCD_WR_REG(0xE1);     
	LCD_WR_DATA8(0xD0);   
	LCD_WR_DATA8(0x08);   
	LCD_WR_DATA8(0x0E);   
	LCD_WR_DATA8(0x09);   
	LCD_WR_DATA8(0x09);   
	LCD_WR_DATA8(0x15);   
	LCD_WR_DATA8(0x31);   
	LCD_WR_DATA8(0x33);   
	LCD_WR_DATA8(0x48);   
	LCD_WR_DATA8(0x17);   
	LCD_WR_DATA8(0x14);   
	LCD_WR_DATA8(0x15);   
	LCD_WR_DATA8(0x31);   
	LCD_WR_DATA8(0x34);
	LCD_WR_REG(0x21); 

	LCD_WR_REG(0x29);
} 
/******************************************************************************
      函数说明：状态4设置选项 进入闹钟或者时间
      入口数据：无
      返回值：  无
******************************************************************************/
//void ClockorTime(u8 state)
//{
//	if(state==5)
//		Show_StringandChinese(X_Position+20,60, "设置页面1-时间设置",WHITE,BLUE,24,0);
//	  Show_StringandChinese(X_Position+20,150,"设置页面2-闹钟设置",WHITE,BLUE,24,0);
//}
/******************************************************************************
      函数说明：状态7设置界面 设置时间
      入口数据：无
      返回值：  无
******************************************************************************/
void Page_Content1_2_3(mode)  // 主界面1-2-3下的第三层
{		

		if(mode==7)
		{
			Show_StringandChinese(X_Position+20,60, "设置页面1-时间设置",WHITE,BLUE,24,0);
			LCD_ShowIntNum(X_Position+50,Y_Position+100,YEAR,2,WHITE,RED,24);
			Show_StringandChinese(X_Position+74,Y_Position+100,"年",WHITE,RED,24,0);
			LCD_ShowIntNum(X_Position+98,Y_Position+100,MONTH,2,WHITE,RED,24);
			Show_StringandChinese(X_Position+122,Y_Position+100,"月",WHITE,RED,24,0);
			LCD_ShowIntNum(X_Position+144,Y_Position+100,DAY,2,WHITE,RED,24);
			Show_StringandChinese(X_Position+168,Y_Position+100,"日",WHITE,RED,24,0);
			
			LCD_ShowIntNum(X_Position+32+38,Y_Position+150,HOUR,2,WHITE,RED,24);//状态1下显示时分秒 年月日
			LCD_ShowChar(X_Position+56+38,Y_Position+150,':',WHITE,RED,24,0);
			LCD_Fill(X_Position+56+38+12,Y_Position+150,X_Position+56+24+38,Y_Position+150+24,RED);			
			LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,MIN,2,WHITE,RED,24);
			LCD_ShowChar(X_Position+80+12+12+38,Y_Position+150,':',WHITE,RED,24,0);
		  LCD_Fill(X_Position+80+24+12+38,Y_Position+150,X_Position+80+24+12+38+12,Y_Position+150+24,RED);			
			LCD_ShowIntNum(X_Position+124+38,Y_Position+150,SEC,2,WHITE,RED,24);
		}
		
		
		if((mode>=9)&&(mode<=14))
		{		
				Show_StringandChinese(X_Position+20,60, "设置页面1-时间设置",WHITE,BLUE,24,0);
				Show_StringandChinese(X_Position+74,Y_Position+100,"年",WHITE,RED,24,0);
				Show_StringandChinese(X_Position+122,Y_Position+100,"月",WHITE,RED,24,0);
				Show_StringandChinese(X_Position+168+2,Y_Position+100,"日",WHITE,RED,24,0);
				LCD_ShowChar(X_Position+56+38,Y_Position+150,':',WHITE,RED,24,0);
				LCD_ShowChar(X_Position+80+12+12+38,Y_Position+150,':',WHITE,RED,24,0);
				LCD_Fill(X_Position+56+12+38,Y_Position+150,X_Position+56+24+38,Y_Position+150+24,RED);		
				LCD_Fill(X_Position+80+24+12+38,Y_Position+150,X_Position+80+24+12+38+8,Y_Position+150+24,RED);			
			if(mode==9)
				{	
					LCD_ShowIntNum(X_Position+50,Y_Position+100,YEAR,2,BLUE,BLACK,24);
					LCD_ShowIntNum(X_Position+98,Y_Position+100,MONTH,2,WHITE,RED,24);		
					LCD_ShowIntNum(X_Position+146,Y_Position+100,DAY,2,WHITE,RED,24);										
					LCD_ShowIntNum(X_Position+32+38,Y_Position+150,HOUR,2,WHITE,RED,24);//状态1下显示时分秒 年月日											
					LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,MIN,2,WHITE,RED,24);									
					LCD_ShowIntNum(X_Position+124+38,Y_Position+150,SEC,2,WHITE,RED,24);
				}
					if(mode==10)
				{					
					LCD_ShowIntNum(X_Position+50,Y_Position+100,YEAR,2,WHITE,RED,24);				
					LCD_ShowIntNum(X_Position+98,Y_Position+100,MONTH,2,BLUE,BLACK,24);	
					LCD_ShowIntNum(X_Position+146,Y_Position+100,DAY,2,WHITE,RED,24);									
					LCD_ShowIntNum(X_Position+32+38,Y_Position+150,HOUR,2,WHITE,RED,24);//状态1下显示时分秒 年月日								
					LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,MIN,2,WHITE,RED,24);						
					LCD_ShowIntNum(X_Position+124+38,Y_Position+150,SEC,2,WHITE,RED,24);
				}
				if(mode==11)
				{					
					LCD_ShowIntNum(X_Position+50,Y_Position+100,YEAR,2,WHITE,RED,24);		
					LCD_ShowIntNum(X_Position+98,Y_Position+100,MONTH,2,WHITE,RED,24);					
					LCD_ShowIntNum(X_Position+146,Y_Position+100,DAY,2,BLUE,BLACK,24);									
					LCD_ShowIntNum(X_Position+32+38,Y_Position+150,HOUR,2,WHITE,RED,24);//状态1下显示时分秒 年月日							
					LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,MIN,2,WHITE,RED,24);							
					LCD_ShowIntNum(X_Position+124+38,Y_Position+150,SEC,2,WHITE,RED,24);
				}
						if(mode==12)
				{					
					LCD_ShowIntNum(X_Position+50,Y_Position+100,YEAR,2,WHITE,RED,24);					
					LCD_ShowIntNum(X_Position+98,Y_Position+100,MONTH,2,WHITE,RED,24);			
					LCD_ShowIntNum(X_Position+146,Y_Position+100,DAY,2,WHITE,RED,24);										
					LCD_ShowIntNum(X_Position+32+38,Y_Position+150,HOUR,2,BLUE,BLACK,24);//状态1下显示时分秒 年月日					
					LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,MIN,2,WHITE,RED,24);						
					LCD_ShowIntNum(X_Position+124+38,Y_Position+150,SEC,2,WHITE,RED,24);
				}
						if(mode==13)
				{					
					LCD_ShowIntNum(X_Position+50,Y_Position+100,YEAR,2,WHITE,RED,24);	
					LCD_ShowIntNum(X_Position+98,Y_Position+100,MONTH,2,WHITE,RED,24);					
					LCD_ShowIntNum(X_Position+146,Y_Position+100,DAY,2,WHITE,RED,24);							
					LCD_ShowIntNum(X_Position+32+38,Y_Position+150,HOUR,2,WHITE,RED,24);//状态1下显示时分秒 年月日								
					LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,MIN,2,BLUE,BLACK,24);								
					LCD_ShowIntNum(X_Position+124+38,Y_Position+150,SEC,2,WHITE,RED,24);
				}
						if(mode==14)
				{					
					LCD_ShowIntNum(X_Position+50,Y_Position+100,YEAR,2,WHITE,RED,24);				
					LCD_ShowIntNum(X_Position+98,Y_Position+100,MONTH,2,WHITE,RED,24);				
					LCD_ShowIntNum(X_Position+146,Y_Position+100,DAY,2,WHITE,RED,24);										
					LCD_ShowIntNum(X_Position+32+38,Y_Position+150,HOUR,2,WHITE,RED,24);//状态1下显示时分秒 年月日						
					LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,MIN,2,WHITE,RED,24);								
					LCD_ShowIntNum(X_Position+124+38,Y_Position+150,SEC,2,BLUE,BLACK,24);
				}
		}
		if(mode==8)
		{
			Show_StringandChinese(X_Position+20,60, "设置页面2-闹钟设置",WHITE,BLUE,24,0);
			LCD_ShowIntNum(X_Position+32+38,Y_Position+150,ALAHOUR,2,WHITE,RED,24);//状态1下显示时分秒 年月日
			LCD_ShowChar(X_Position+56+38,Y_Position+150,':',WHITE,RED,24,0);
			LCD_Fill(X_Position+56+12+38,Y_Position+150,X_Position+56+24+38,Y_Position+150+24,RED);			
			LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,ALAMIN,2,WHITE,RED,24);
			LCD_ShowChar(X_Position+80+12+12+38,Y_Position+150,':',WHITE,RED,24,0);
		  LCD_Fill(X_Position+80+24+12+38,Y_Position+150,X_Position+80+24+12+38+12,Y_Position+150+24,RED);			
			LCD_ShowIntNum(X_Position+124+38,Y_Position+150,ALASEC,2,WHITE,RED,24);
		}
		if((mode>=15)&&(mode<=17))
		{
			Show_StringandChinese(X_Position+20,60, "设置页面2-闹钟设置",WHITE,BLUE,24,0);
			
			LCD_ShowChar(X_Position+56+38,Y_Position+150,':',WHITE,RED,24,0);
			LCD_Fill(X_Position+56+12+38,Y_Position+150,X_Position+56+24+38,Y_Position+150+24,RED);
			LCD_ShowChar(X_Position+80+12+12+38,Y_Position+150,':',WHITE,RED,24,0);
			LCD_Fill(X_Position+80+24+12+38,Y_Position+150,X_Position+80+24+12+38+12,Y_Position+150+24,RED);
			if(mode==15)
			{	
					LCD_ShowIntNum(X_Position+32+38,Y_Position+150,ALAHOUR,2,BLUE,BLACK,24);//状态1下显示时分秒 年月日								
					LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,ALAMIN,2,WHITE,RED,24);										
					LCD_ShowIntNum(X_Position+124+38+4,Y_Position+150,ALASEC,2,WHITE,RED,24);
			}
			if(mode==16)
			{
					LCD_ShowIntNum(X_Position+32+38,Y_Position+150,ALAHOUR,2,WHITE,RED,24);//状态1下显示时分秒 年月日								
					LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,ALAMIN,2,BLUE,BLACK,24);								
					LCD_ShowIntNum(X_Position+124+38+4,Y_Position+150,ALASEC,2,WHITE,RED,24);
			}
			if(mode==17)
			{
					LCD_ShowIntNum(X_Position+32+38,Y_Position+150,ALAHOUR,2,WHITE,RED,24);//状态1下显示时分秒 年月日								
					LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,ALAMIN,2,WHITE,RED,24);		
					LCD_ShowIntNum(X_Position+124+38+4,Y_Position+150,ALASEC,2,BLUE,BLACK,24);
			}
		}
}
/******************************************************************************
      函数说明：状态4设置界面 设置闹钟，设置时间
      入口数据：无
      返回值：  无
******************************************************************************/
void Page_Content1_2(void)  // 主界面1下的第二层
{	
	Show_StringandChinese(X_Position+20,60, "设置页面1-时间设置",WHITE,BLUE,24,0);
	Show_StringandChinese(X_Position+20,150,"设置页面2-闹钟设置",WHITE,BLUE,24,0);			
}
/******************************************************************************
      函数说明：LCD固定页面显示函数  状态1
      入口数据：无
      返回值：  无
******************************************************************************/
void Page_Content_1(u16 year,u16 month,u16 day,u16 hour,u16 min,u16 sec,u16 shi_val,u16 fen_val,u16 miao_val,float val)  // 固定页面_1，显示一些可变的内容
{ 
	//sprintf函数对应的是u16类型，所以参数值都是u16类型
	u8 str[30];
	Show_StringandChinese(95,0,"迷你小闹钟",WHITE,RED,24,0);
	LCD_DrawLine(0,30,320,30,WHITE);    //分割线
	
	sprintf(str, "%02u", year);
	Show_StringandChinese(X_Position+4,50,"日期",WHITE,RED,24,0);	
	Show_StringandChinese(X_Position+110,50,str,WHITE,RED,24,0);
	Show_StringandChinese(X_Position+134,50,"年",WHITE,RED,24,0);
	sprintf(str, "%02u", month);
	Show_StringandChinese(X_Position+4,Y_Position+60,"时间",WHITE,RED,24,0);
	Show_StringandChinese(X_Position+158,50,str,WHITE,RED,24,0);
	Show_StringandChinese(X_Position+182,50,"月",WHITE,RED,24,0);
	sprintf(str, "%02u", day);
	Show_StringandChinese(X_Position+4,Y_Position+96,"闹钟",WHITE,RED,24,0);
	Show_StringandChinese(X_Position+206,50,str,WHITE,RED,24,0);
	Show_StringandChinese(X_Position+230,50,"日",WHITE,RED,24,0);
	Show_StringandChinese(X_Position+4,Y_Position+156,"电源电压",WHITE,RED,24,0);
	
	sprintf(str, "%02u", hour);//显示时间
  Show_StringandChinese(X_Position+110, Y_Position+60, str, WHITE, RED, 24, 0);
  Show_StringandChinese(X_Position+134, Y_Position+60, ":", WHITE, RED, 24, 0);    
  sprintf(str, "%02u", min);
  Show_StringandChinese(X_Position+158, Y_Position+60, str, WHITE, RED, 24, 0);
  Show_StringandChinese(X_Position+182, Y_Position+60, ":", WHITE, RED, 24, 0); 
  sprintf(str, "%02u", sec);
  Show_StringandChinese(X_Position+206, Y_Position+60, str, WHITE, RED, 24, 0);
	
	sprintf(str, "%02u", shi_val);//显示闹钟
  Show_StringandChinese(X_Position+110, Y_Position+96, str, WHITE, RED, 24, 0);
  Show_StringandChinese(X_Position+134, Y_Position+96, ":", WHITE, RED, 24, 0);    
  sprintf(str, "%02u", fen_val);
  Show_StringandChinese(X_Position+158, Y_Position+96, str, WHITE, RED, 24, 0);
  Show_StringandChinese(X_Position+182, Y_Position+96, ":", WHITE, RED, 24, 0); 
  sprintf(str, "%02u", miao_val);
  Show_StringandChinese(X_Position+206, Y_Position+96, str, WHITE, RED, 24, 0);
	LCD_DrawLine(0,Y_Position+32*3+24+8,X_Position+320,Y_Position+32*3+24+8,WHITE); 
	
	sprintf(str, "%.2f", val);
	Show_StringandChinese(X_Position+110,Y_Position+156,str,WHITE,RED,24,0);	
}
/******************************************************************************
      函数说明：LCD数据显示函数
      入口数据：无
      返回值：  无
******************************************************************************/
void VEP_All_Display() 
{
	LCD_ShowIntNum(X_Position+76,Y_Position-32,12,6,GREEN,BLACK,24);
	LCD_ShowIntNum(X_Position+76,Y_Position,23,6,GREEN,BLACK,24);
	LCD_ShowIntNum(X_Position+76,Y_Position+32,34,4,GREEN,BLACK,24);
	LCD_ShowIntNum(X_Position+76,Y_Position+32*2,45,3,GREEN,BLACK,24);
	LCD_ShowIntNum(X_Position+76,Y_Position+32*3,56,3,GREEN,BLACK,24);

}


