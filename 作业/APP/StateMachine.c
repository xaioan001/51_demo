#include "type_def.h"
#include "LCD_DISPLAY.h"
#include "LCD_BASE.h"
#include	"STC8H_RTC.h"
#include "filtering.h"
#include "Picture.h"
#include "stdio.h"
static u16 shi,fen,miao;
extern float VAL;

/**
***********************************************************
* @brief   ״̬����ȡ״̬
* @param 
* @return  ʵʱ״̬���
***********************************************************
*/
u8 Getstate(u8 key,u16 VAL )
{
	static u8 state=1,layer=1;//state:״̬ layer:����

	if((key==1)&&(layer==1))
		{
			state=state%3+1;//�ڵ�һ�������������µĵ�һ��ת��(s1,s2,s3)
			if(state==1)//״̬1
			{
					Page_Content_1(YEAR,MONTH,DAY,HOUR,MIN,SEC,ALAHOUR,ALAMIN,ALASEC,VAL);					
			}
			else if(state==2)
			{
				LCD_Fill_Black(0,0,320,240);
				LCD_ShowPicture(100,50,IMG_HEIGHT,IMG_WIDTH,IMG_DATA);
			}
			else if(state==3)//״̬3
				LCD_Fill_Black(0,0,320,240);
					
		}
	if((key == 44)&&(state!=5)&&(state!=6))
	{
		if(layer == 1)
		{
			state = 4;
			layer =2;
			LCD_Fill_Black(0,0,320,240); //����
		}
	 if(layer == 2)
		{
			state = 4;
			layer =2;
			LCD_Fill_Black(0,0,320,240); //����
			Page_Content1_2();
		}
		
	}
	if((key==1)&&(layer == 2)&&(state == 4))
	{
		state=6;
	}
	if((key == 1)&&(layer == 2))
	{
		state = 11 - state;
	}
	if((key == 11)&&(layer == 2)&&(state == 5))
	{
		state=7;
		layer=3;
		LCD_Fill_Black(0,0,320,240);
		Page_Content1_2_3(state);//���ý���1 ʱ������
		
	}

	if((key == 1)&&(layer == 3))
	{
		if(state == 7)
		{
			state=9;//��
		}
		else if(state == 9)
		{
			state=10;//��
		}
		else if(state == 10)
		{
			state=11;//��
		}
		else if(state == 11)
		{
			state=12;//ʱ
		}
		else if(state == 12)
		{
			state=13;//��
		}
		else if(state == 13)
		{
			state=14;//��	
		}
		else if(state==14)
		{
			state=9;
		}
		LCD_Fill_Black(0,0,320,240);
		Page_Content1_2_3(state);
	}
	if((key == 2)&&(layer == 3))//����1
	{
		if(state==9)
		{
				INIYEAR = YEAR;
				INIYEAR++;
				RTCCFG |= 0x01;
		}
		else if(state==10)
		{
				INIMONTH = MONTH;
				INIMONTH++;
				RTCCFG |= 0x01;
		}
		else if(state==11)
		{
				INIDAY = DAY;
				INIDAY++;
				RTCCFG |= 0x01;
		}
		else if(state==12)
		{
				INIHOUR = HOUR;
				INIHOUR++;
				RTCCFG |= 0x01;
		}
		else if(state==13)
		{
				INIMIN = MIN;
				INIMIN++;
				RTCCFG |= 0x01;
		}
		else if(state==14)
		{
				INISEC = SEC;
				INISEC++;
				RTCCFG |= 0x01;
		}
	}
	if((key == 3)&&(layer == 3))//����1
	{
		if(state==9)
		{
				INIYEAR = YEAR;
				INIYEAR--;
				RTCCFG |= 0x01;
		}
		else if(state==10)
		{
				INIMONTH = MONTH;
				INIMONTH--;
				RTCCFG |= 0x01;
		}
		else if(state==11)
		{
				INIDAY = DAY;
				INIDAY--;
				RTCCFG |= 0x01;
		}
		else if(state==12)
		{
				INIHOUR = HOUR;
				INIHOUR--;
				RTCCFG |= 0x01;
		}
		else if(state==13)
		{
				INIMIN = MIN;
				INIMIN--;
				RTCCFG |= 0x01;
		}
		else if(state==14)
		{
				INISEC = SEC;
				INISEC--;
				RTCCFG |= 0x01;
		}
	}
	if((key == 11)&&(layer == 2)&&(state == 6))
	{
		state=8;
		layer=3;
		LCD_Fill_Black(0,0,320,240);
		Page_Content1_2_3(state);//���ý���2 ��������
		//printf("State6 = %bu,layer = %bu.\n",state,layer);
	}
	if((key == 11)&&(layer == 3)&&(state == 8))
	{
		state=15;
		layer=3;
		//Page_Content1_2_3(state);
	}
	if((key == 1)&&(layer == 3)&&((state>=15)&&(state<=18)))
	{
		if(state==15)
		{
			state=16;
			
		}
		else if(state==16)
		{
			state=17;
			
		}
		else if(state==17)
		{
			state=15;
			
		}
		Page_Content1_2_3(state);
	}
	if((key == 2)&&(layer == 3)&&(state==15))
	{
		ALAHOUR++;
	}
	if((key == 3)&&(layer == 3)&&(state==15))
	{
		ALAHOUR--;
	}
	if((key == 2)&&(layer == 3)&&(state==16))
	{
		ALAMIN++;
	}
	if((key == 3)&&(layer == 3)&&(state==16))
	{
		ALAMIN--;
	}
	if((key == 2)&&(layer == 3)&&(state==17))
	{
		ALASEC++;
	}
	if((key == 3)&&(layer == 3)&&(state==17))
	{
		ALASEC--;
	}
	if(((state==5)||(state==6))&&(key == 44)&&(layer == 2))
	{
		state=1;//�ӵڶ��㷵�ص�һ��
		layer=1;
		LCD_Fill_Black(0,0,320,240);
		Page_Content_1(YEAR,MONTH,DAY,HOUR,MIN,SEC,ALAHOUR,ALAMIN,ALASEC,VAL);
	
	}
	if(((state==7)||(state==15))&&(key == 44)&&(layer == 3))
	{
		state=4;
		layer=2;
		LCD_Fill_Black(0,0,320,240);
		Page_Content1_2();
	}
	return state;
}
/**
***********************************************************
* @brief   ��״̬��
* @param 
* @return  
***********************************************************
*/
void StateMachine(u8 state,u8 key)
{
	
	switch (state)
  {
  	case 1:						//20          //24
			LCD_ShowIntNum(X_Position+110,Y_Position+60,HOUR,2,WHITE,RED,24);//״̬1����ʾʱ���� ��ѹֵ��������
			LCD_ShowChar(X_Position+134,Y_Position+60,':',WHITE,RED,24,0);
			LCD_Fill(X_Position+134+12,Y_Position+60,X_Position+134+24,Y_Position+60+24,RED);//���ȱ��
			
			LCD_ShowIntNum(X_Position+158,Y_Position+60,MIN,2,WHITE,RED,24);
			LCD_ShowChar(X_Position+182,Y_Position+60,':',WHITE,RED,24,0);
		  LCD_Fill(X_Position+182+12,Y_Position+60,X_Position+182+24,Y_Position+60+24,RED);
			
			LCD_ShowIntNum(X_Position+206,Y_Position+60,SEC,2,WHITE,RED,24);//��ʾ��������
			
	  	LCD_ShowFloatNum2(X_Position+110,Y_Position+156,VAL,3,WHITE,RED,24);
  		break;
  	case 2:
				LCD_ShowPicture(100,50,IMG_HEIGHT,IMG_WIDTH,IMG_DATA);
		printf("state = %bu.\n",state);
  		break;
	  case 3:
				LCD_Fill_Black(0,0,320,240);
  		break;
  	case 4:
			Page_Content1_2();
  		break;
		case 5:
			Show_StringandChinese(X_Position+20,60, "����ҳ��1-ʱ������",WHITE,RED,24,0);
   	  Show_StringandChinese(X_Position+20,150,"����ҳ��2-��������",WHITE,BLUE,24,0);
  		break;
  	case 6:
			Show_StringandChinese(X_Position+20,60, "����ҳ��1-ʱ������",WHITE,BLUE,24,0);
   	  Show_StringandChinese(X_Position+20,150,"����ҳ��2-��������",WHITE,RED,24,0);
  		break;
		case 7:
			Page_Content1_2_3(state);//ʱ������ҳ��
  		break;
		case 8:
			Page_Content1_2_3(state);//��������ҳ��
  		break;
		case 9:
			Page_Content1_2_3(state);//��
			break;
		case 10:
			Page_Content1_2_3(state);//��
  		break;
		case 11:
			Page_Content1_2_3(state);//��	
  		break;
		case 12:
			Page_Content1_2_3(state);//ʱ				
  		break;
		case 13:
			Page_Content1_2_3(state);//��		
  		break;
		case 14:
			Page_Content1_2_3(state);//��				
  		break;
		case 15: 
			Page_Content1_2_3(state);//��������  ʱ
  		break;
		case 16:
			Page_Content1_2_3(state);//��			
  		break;
		case 17:
			Page_Content1_2_3(state);//��
  		break;
		case 18:
			Page_Content1_2_3(state);//��->ʱ		
  		break;
		case 19:
			
			
  		break;
		case 20: 
  		break;
		
  	default:
  		break;
		
  }
}