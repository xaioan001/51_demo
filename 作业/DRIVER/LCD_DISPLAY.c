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
      ����˵����LCD��ʼ������
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void LCD_Init(void)
{
	LCD_RES=0;    // ��λҺ����
	delay_ms(200);
	LCD_RES=1;	
	delay_ms(200);
	
	LCD_WR_REG(0x11);           //Sleep out 
	delay_ms(120);              //Delay 120ms 
	LCD_WR_REG(0x36);
//	if(USE_HORIZONTAL==2)  // ���� ,����뷴������ʾ���ɼ����������
//		LCD_WR_DATA8(0x70);
  if(USE_HORIZONTAL==3)
	{
		LCD_WR_DATA8(0xA0);  // ���� 
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
	LCD_WR_DATA8(0x15); //GVDD=4.8V  ��ɫ���
				
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
      ����˵����״̬4����ѡ�� �������ӻ���ʱ��
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
//void ClockorTime(u8 state)
//{
//	if(state==5)
//		Show_StringandChinese(X_Position+20,60, "����ҳ��1-ʱ������",WHITE,BLUE,24,0);
//	  Show_StringandChinese(X_Position+20,150,"����ҳ��2-��������",WHITE,BLUE,24,0);
//}
/******************************************************************************
      ����˵����״̬7���ý��� ����ʱ��
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void Page_Content1_2_3(mode)  // ������1-2-3�µĵ�����
{		

		if(mode==7)
		{
			Show_StringandChinese(X_Position+20,60, "����ҳ��1-ʱ������",WHITE,BLUE,24,0);
			LCD_ShowIntNum(X_Position+50,Y_Position+100,YEAR,2,WHITE,RED,24);
			Show_StringandChinese(X_Position+74,Y_Position+100,"��",WHITE,RED,24,0);
			LCD_ShowIntNum(X_Position+98,Y_Position+100,MONTH,2,WHITE,RED,24);
			Show_StringandChinese(X_Position+122,Y_Position+100,"��",WHITE,RED,24,0);
			LCD_ShowIntNum(X_Position+144,Y_Position+100,DAY,2,WHITE,RED,24);
			Show_StringandChinese(X_Position+168,Y_Position+100,"��",WHITE,RED,24,0);
			
			LCD_ShowIntNum(X_Position+32+38,Y_Position+150,HOUR,2,WHITE,RED,24);//״̬1����ʾʱ���� ������
			LCD_ShowChar(X_Position+56+38,Y_Position+150,':',WHITE,RED,24,0);
			LCD_Fill(X_Position+56+38+12,Y_Position+150,X_Position+56+24+38,Y_Position+150+24,RED);			
			LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,MIN,2,WHITE,RED,24);
			LCD_ShowChar(X_Position+80+12+12+38,Y_Position+150,':',WHITE,RED,24,0);
		  LCD_Fill(X_Position+80+24+12+38,Y_Position+150,X_Position+80+24+12+38+12,Y_Position+150+24,RED);			
			LCD_ShowIntNum(X_Position+124+38,Y_Position+150,SEC,2,WHITE,RED,24);
		}
		
		
		if((mode>=9)&&(mode<=14))
		{		
				Show_StringandChinese(X_Position+20,60, "����ҳ��1-ʱ������",WHITE,BLUE,24,0);
				Show_StringandChinese(X_Position+74,Y_Position+100,"��",WHITE,RED,24,0);
				Show_StringandChinese(X_Position+122,Y_Position+100,"��",WHITE,RED,24,0);
				Show_StringandChinese(X_Position+168+2,Y_Position+100,"��",WHITE,RED,24,0);
				LCD_ShowChar(X_Position+56+38,Y_Position+150,':',WHITE,RED,24,0);
				LCD_ShowChar(X_Position+80+12+12+38,Y_Position+150,':',WHITE,RED,24,0);
				LCD_Fill(X_Position+56+12+38,Y_Position+150,X_Position+56+24+38,Y_Position+150+24,RED);		
				LCD_Fill(X_Position+80+24+12+38,Y_Position+150,X_Position+80+24+12+38+8,Y_Position+150+24,RED);			
			if(mode==9)
				{	
					LCD_ShowIntNum(X_Position+50,Y_Position+100,YEAR,2,BLUE,BLACK,24);
					LCD_ShowIntNum(X_Position+98,Y_Position+100,MONTH,2,WHITE,RED,24);		
					LCD_ShowIntNum(X_Position+146,Y_Position+100,DAY,2,WHITE,RED,24);										
					LCD_ShowIntNum(X_Position+32+38,Y_Position+150,HOUR,2,WHITE,RED,24);//״̬1����ʾʱ���� ������											
					LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,MIN,2,WHITE,RED,24);									
					LCD_ShowIntNum(X_Position+124+38,Y_Position+150,SEC,2,WHITE,RED,24);
				}
					if(mode==10)
				{					
					LCD_ShowIntNum(X_Position+50,Y_Position+100,YEAR,2,WHITE,RED,24);				
					LCD_ShowIntNum(X_Position+98,Y_Position+100,MONTH,2,BLUE,BLACK,24);	
					LCD_ShowIntNum(X_Position+146,Y_Position+100,DAY,2,WHITE,RED,24);									
					LCD_ShowIntNum(X_Position+32+38,Y_Position+150,HOUR,2,WHITE,RED,24);//״̬1����ʾʱ���� ������								
					LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,MIN,2,WHITE,RED,24);						
					LCD_ShowIntNum(X_Position+124+38,Y_Position+150,SEC,2,WHITE,RED,24);
				}
				if(mode==11)
				{					
					LCD_ShowIntNum(X_Position+50,Y_Position+100,YEAR,2,WHITE,RED,24);		
					LCD_ShowIntNum(X_Position+98,Y_Position+100,MONTH,2,WHITE,RED,24);					
					LCD_ShowIntNum(X_Position+146,Y_Position+100,DAY,2,BLUE,BLACK,24);									
					LCD_ShowIntNum(X_Position+32+38,Y_Position+150,HOUR,2,WHITE,RED,24);//״̬1����ʾʱ���� ������							
					LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,MIN,2,WHITE,RED,24);							
					LCD_ShowIntNum(X_Position+124+38,Y_Position+150,SEC,2,WHITE,RED,24);
				}
						if(mode==12)
				{					
					LCD_ShowIntNum(X_Position+50,Y_Position+100,YEAR,2,WHITE,RED,24);					
					LCD_ShowIntNum(X_Position+98,Y_Position+100,MONTH,2,WHITE,RED,24);			
					LCD_ShowIntNum(X_Position+146,Y_Position+100,DAY,2,WHITE,RED,24);										
					LCD_ShowIntNum(X_Position+32+38,Y_Position+150,HOUR,2,BLUE,BLACK,24);//״̬1����ʾʱ���� ������					
					LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,MIN,2,WHITE,RED,24);						
					LCD_ShowIntNum(X_Position+124+38,Y_Position+150,SEC,2,WHITE,RED,24);
				}
						if(mode==13)
				{					
					LCD_ShowIntNum(X_Position+50,Y_Position+100,YEAR,2,WHITE,RED,24);	
					LCD_ShowIntNum(X_Position+98,Y_Position+100,MONTH,2,WHITE,RED,24);					
					LCD_ShowIntNum(X_Position+146,Y_Position+100,DAY,2,WHITE,RED,24);							
					LCD_ShowIntNum(X_Position+32+38,Y_Position+150,HOUR,2,WHITE,RED,24);//״̬1����ʾʱ���� ������								
					LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,MIN,2,BLUE,BLACK,24);								
					LCD_ShowIntNum(X_Position+124+38,Y_Position+150,SEC,2,WHITE,RED,24);
				}
						if(mode==14)
				{					
					LCD_ShowIntNum(X_Position+50,Y_Position+100,YEAR,2,WHITE,RED,24);				
					LCD_ShowIntNum(X_Position+98,Y_Position+100,MONTH,2,WHITE,RED,24);				
					LCD_ShowIntNum(X_Position+146,Y_Position+100,DAY,2,WHITE,RED,24);										
					LCD_ShowIntNum(X_Position+32+38,Y_Position+150,HOUR,2,WHITE,RED,24);//״̬1����ʾʱ���� ������						
					LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,MIN,2,WHITE,RED,24);								
					LCD_ShowIntNum(X_Position+124+38,Y_Position+150,SEC,2,BLUE,BLACK,24);
				}
		}
		if(mode==8)
		{
			Show_StringandChinese(X_Position+20,60, "����ҳ��2-��������",WHITE,BLUE,24,0);
			LCD_ShowIntNum(X_Position+32+38,Y_Position+150,ALAHOUR,2,WHITE,RED,24);//״̬1����ʾʱ���� ������
			LCD_ShowChar(X_Position+56+38,Y_Position+150,':',WHITE,RED,24,0);
			LCD_Fill(X_Position+56+12+38,Y_Position+150,X_Position+56+24+38,Y_Position+150+24,RED);			
			LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,ALAMIN,2,WHITE,RED,24);
			LCD_ShowChar(X_Position+80+12+12+38,Y_Position+150,':',WHITE,RED,24,0);
		  LCD_Fill(X_Position+80+24+12+38,Y_Position+150,X_Position+80+24+12+38+12,Y_Position+150+24,RED);			
			LCD_ShowIntNum(X_Position+124+38,Y_Position+150,ALASEC,2,WHITE,RED,24);
		}
		if((mode>=15)&&(mode<=17))
		{
			Show_StringandChinese(X_Position+20,60, "����ҳ��2-��������",WHITE,BLUE,24,0);
			
			LCD_ShowChar(X_Position+56+38,Y_Position+150,':',WHITE,RED,24,0);
			LCD_Fill(X_Position+56+12+38,Y_Position+150,X_Position+56+24+38,Y_Position+150+24,RED);
			LCD_ShowChar(X_Position+80+12+12+38,Y_Position+150,':',WHITE,RED,24,0);
			LCD_Fill(X_Position+80+24+12+38,Y_Position+150,X_Position+80+24+12+38+12,Y_Position+150+24,RED);
			if(mode==15)
			{	
					LCD_ShowIntNum(X_Position+32+38,Y_Position+150,ALAHOUR,2,BLUE,BLACK,24);//״̬1����ʾʱ���� ������								
					LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,ALAMIN,2,WHITE,RED,24);										
					LCD_ShowIntNum(X_Position+124+38+4,Y_Position+150,ALASEC,2,WHITE,RED,24);
			}
			if(mode==16)
			{
					LCD_ShowIntNum(X_Position+32+38,Y_Position+150,ALAHOUR,2,WHITE,RED,24);//״̬1����ʾʱ���� ������								
					LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,ALAMIN,2,BLUE,BLACK,24);								
					LCD_ShowIntNum(X_Position+124+38+4,Y_Position+150,ALASEC,2,WHITE,RED,24);
			}
			if(mode==17)
			{
					LCD_ShowIntNum(X_Position+32+38,Y_Position+150,ALAHOUR,2,WHITE,RED,24);//״̬1����ʾʱ���� ������								
					LCD_ShowIntNum(X_Position+68+12+38,Y_Position+150,ALAMIN,2,WHITE,RED,24);		
					LCD_ShowIntNum(X_Position+124+38+4,Y_Position+150,ALASEC,2,BLUE,BLACK,24);
			}
		}
}
/******************************************************************************
      ����˵����״̬4���ý��� �������ӣ�����ʱ��
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void Page_Content1_2(void)  // ������1�µĵڶ���
{	
	Show_StringandChinese(X_Position+20,60, "����ҳ��1-ʱ������",WHITE,BLUE,24,0);
	Show_StringandChinese(X_Position+20,150,"����ҳ��2-��������",WHITE,BLUE,24,0);			
}
/******************************************************************************
      ����˵����LCD�̶�ҳ����ʾ����  ״̬1
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void Page_Content_1(u16 year,u16 month,u16 day,u16 hour,u16 min,u16 sec,u16 shi_val,u16 fen_val,u16 miao_val,float val)  // �̶�ҳ��_1����ʾһЩ�ɱ������
{ 
	//sprintf������Ӧ����u16���ͣ����Բ���ֵ����u16����
	u8 str[30];
	Show_StringandChinese(95,0,"����С����",WHITE,RED,24,0);
	LCD_DrawLine(0,30,320,30,WHITE);    //�ָ���
	
	sprintf(str, "%02u", year);
	Show_StringandChinese(X_Position+4,50,"����",WHITE,RED,24,0);	
	Show_StringandChinese(X_Position+110,50,str,WHITE,RED,24,0);
	Show_StringandChinese(X_Position+134,50,"��",WHITE,RED,24,0);
	sprintf(str, "%02u", month);
	Show_StringandChinese(X_Position+4,Y_Position+60,"ʱ��",WHITE,RED,24,0);
	Show_StringandChinese(X_Position+158,50,str,WHITE,RED,24,0);
	Show_StringandChinese(X_Position+182,50,"��",WHITE,RED,24,0);
	sprintf(str, "%02u", day);
	Show_StringandChinese(X_Position+4,Y_Position+96,"����",WHITE,RED,24,0);
	Show_StringandChinese(X_Position+206,50,str,WHITE,RED,24,0);
	Show_StringandChinese(X_Position+230,50,"��",WHITE,RED,24,0);
	Show_StringandChinese(X_Position+4,Y_Position+156,"��Դ��ѹ",WHITE,RED,24,0);
	
	sprintf(str, "%02u", hour);//��ʾʱ��
  Show_StringandChinese(X_Position+110, Y_Position+60, str, WHITE, RED, 24, 0);
  Show_StringandChinese(X_Position+134, Y_Position+60, ":", WHITE, RED, 24, 0);    
  sprintf(str, "%02u", min);
  Show_StringandChinese(X_Position+158, Y_Position+60, str, WHITE, RED, 24, 0);
  Show_StringandChinese(X_Position+182, Y_Position+60, ":", WHITE, RED, 24, 0); 
  sprintf(str, "%02u", sec);
  Show_StringandChinese(X_Position+206, Y_Position+60, str, WHITE, RED, 24, 0);
	
	sprintf(str, "%02u", shi_val);//��ʾ����
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
      ����˵����LCD������ʾ����
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void VEP_All_Display() 
{
	LCD_ShowIntNum(X_Position+76,Y_Position-32,12,6,GREEN,BLACK,24);
	LCD_ShowIntNum(X_Position+76,Y_Position,23,6,GREEN,BLACK,24);
	LCD_ShowIntNum(X_Position+76,Y_Position+32,34,4,GREEN,BLACK,24);
	LCD_ShowIntNum(X_Position+76,Y_Position+32*2,45,3,GREEN,BLACK,24);
	LCD_ShowIntNum(X_Position+76,Y_Position+32*3,56,3,GREEN,BLACK,24);

}


