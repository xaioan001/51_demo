#ifndef __LCD_DISPLAY_H
#define __LCD_DISPLAY_H
#include "STC8H.H"
#include "type_def.h"

sbit LCD_RES = P7^0; //液晶复位
sbit LCD_SCL = P4^3; //SCLK
sbit LCD_SDA = P4^0; //MOSI
sbit LCD_DC  = P6^0;  //DC

//只修改 X，Y原始坐标即可修改 动态显示区域的整个位置
#define X_Position 20
#define Y_Position 24

void LCD_Init(void);//LCD初始化
//void Page_Content_1(void);  // 固定页面_1，显示一些固定不变的内容
void VEP_All_Display(void);
/******************************************************************************
      函数说明：LCD固定页面显示函数
      入口数据：无
      返回值：  无
******************************************************************************/
void  Page_Content_1(u16 year,u16 month,u16 day,u16 hour,u16 min,u16 sec,u16 shi_val,u16 fen_val,u16 miao_val,float val);
/******************************************************************************
      函数说明：状态4设置界面 设置闹钟，设置时间
      入口数据：无
      返回值：  无
******************************************************************************/
void Page_Content1_2(void);  // 主界面1下的第二层
/******************************************************************************
      函数说明：状态7设置界面 设置时间
      入口数据：mode:状态模式
      返回值：  无
******************************************************************************/
void Page_Content1_2_3(mode);

#endif




