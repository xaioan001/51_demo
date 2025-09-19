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
* @brief   状态机获取状态
* @param 
* @return  实时状态序号
***********************************************************
*/
u8 Getstate(u8 key,u16 VAL )
{
	static u8 state=1,layer=1;//state:状态 layer:层数

	if((key==1)&&(layer==1))
		{
			state=state%3+1;//在第一到第三主界面下的第一层转换(s1,s2,s3)
			if(state==1)//状态1
			{
					Page_Content_1(YEAR,MONTH,DAY,HOUR,MIN,SEC,ALAHOUR,ALAMIN,ALASEC,VAL);					
			}
			else if(state==2)
			{
				LCD_Fill_Black(0,0,320,240);
				LCD_ShowPicture(100,50,IMG_HEIGHT,IMG_WIDTH,IMG_DATA);
			}
			else if(state==3)//状态3
				LCD_Fill_Black(0,0,320,240);
					
		}
	if((key == 44)&&(state!=5)&&(state!=6))
	{
		if(layer == 1)
		{
			state = 4;
			layer =2;
			LCD_Fill_Black(0,0,320,240); //清屏
		}
	 if(layer == 2)
		{
			state = 4;
			layer =2;
			LCD_Fill_Black(0,0,320,240); //清屏
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
		Page_Content1_2_3(state);//设置界面1 时间设置
		
	}

	if((key == 1)&&(layer == 3))
	{
		if(state == 7)
		{
			state=9;//年
		}
		else if(state == 9)
		{
			state=10;//月
		}
		else if(state == 10)
		{
			state=11;//日
		}
		else if(state == 11)
		{
			state=12;//时
		}
		else if(state == 12)
		{
			state=13;//分
		}
		else if(state == 13)
		{
			state=14;//秒	
		}
		else if(state==14)
		{
			state=9;
		}
		LCD_Fill_Black(0,0,320,240);
		Page_Content1_2_3(state);
	}
	if((key == 2)&&(layer == 3))//增加1
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
	if((key == 3)&&(layer == 3))//减少1
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
		Page_Content1_2_3(state);//设置界面2 闹钟设置
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
		state=1;//从第二层返回第一层
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
* @brief   主状态机
* @param 
* @return  
***********************************************************
*/
void StateMachine(u8 state,u8 key)
{
	
	switch (state)
  {
  	case 1:						//20          //24
			LCD_ShowIntNum(X_Position+110,Y_Position+60,HOUR,2,WHITE,RED,24);//状态1下显示时分秒 电压值，年月日
			LCD_ShowChar(X_Position+134,Y_Position+60,':',WHITE,RED,24,0);
			LCD_Fill(X_Position+134+12,Y_Position+60,X_Position+134+24,Y_Position+60+24,RED);//填充缺口
			
			LCD_ShowIntNum(X_Position+158,Y_Position+60,MIN,2,WHITE,RED,24);
			LCD_ShowChar(X_Position+182,Y_Position+60,':',WHITE,RED,24,0);
		  LCD_Fill(X_Position+182+12,Y_Position+60,X_Position+182+24,Y_Position+60+24,RED);
			
			LCD_ShowIntNum(X_Position+206,Y_Position+60,SEC,2,WHITE,RED,24);//显示整数变量
			
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
			Show_StringandChinese(X_Position+20,60, "设置页面1-时间设置",WHITE,RED,24,0);
   	  Show_StringandChinese(X_Position+20,150,"设置页面2-闹钟设置",WHITE,BLUE,24,0);
  		break;
  	case 6:
			Show_StringandChinese(X_Position+20,60, "设置页面1-时间设置",WHITE,BLUE,24,0);
   	  Show_StringandChinese(X_Position+20,150,"设置页面2-闹钟设置",WHITE,RED,24,0);
  		break;
		case 7:
			Page_Content1_2_3(state);//时间设置页面
  		break;
		case 8:
			Page_Content1_2_3(state);//闹钟设置页面
  		break;
		case 9:
			Page_Content1_2_3(state);//年
			break;
		case 10:
			Page_Content1_2_3(state);//月
  		break;
		case 11:
			Page_Content1_2_3(state);//日	
  		break;
		case 12:
			Page_Content1_2_3(state);//时				
  		break;
		case 13:
			Page_Content1_2_3(state);//分		
  		break;
		case 14:
			Page_Content1_2_3(state);//秒				
  		break;
		case 15: 
			Page_Content1_2_3(state);//闹钟设置  时
  		break;
		case 16:
			Page_Content1_2_3(state);//分			
  		break;
		case 17:
			Page_Content1_2_3(state);//秒
  		break;
		case 18:
			Page_Content1_2_3(state);//秒->时		
  		break;
		case 19:
			
			
  		break;
		case 20: 
  		break;
		
  	default:
  		break;
		
  }
}