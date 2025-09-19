#ifndef __LCD_BASE_H
#define __LCD_BASE_H	


#include "type_def.h"

#define USE_HORIZONTAL 3  //2,3为横屏显示，0,1为竖屏显示，本项目里只提供横向显示

#if USE_HORIZONTAL==2||USE_HORIZONTAL==3
#define LCD_W 320
#define LCD_H 240
#endif

void LCD_Writ_Bus(u8 dat);//模拟SPI时序
void LCD_WR_DATA8(u8 dat);//写入一个字节
void LCD_WR_DATA(u16 dat);//写入两个字节
void LCD_WR_REG(u8 dat);  //写入一个指令

void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//设置坐标函数
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);//指定区域填充颜色
void LCD_DrawPoint(u16 x,u16 y,u16 color);//在指定位置画一个点
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);//在指定位置画一条线

void LCD_ShowChinese(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode);//显示汉字串
void LCD_ShowChinese16x16(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode);//显示单个16x16汉字
void LCD_ShowChinese24x24(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode);//显示单个24x24汉字


void LCD_ShowChar(u16 x,u16 y,u8 num,u16 fc,u16 bc,u8 sizey,u8 mode);//显示一个字符
void LCD_ShowString(u16 x,u16 y,const u8 *p,u16 fc,u16 bc,u8 sizey,u8 mode);//显示字符串
void Show_StringandChinese(u16 x,u16 y,u8 *str, u16 fc,u16 bc,u8 sizey,u8 mode); //汉字、字符串混合显示
u32 mypow(u8 m,u8 n);//求幂

//void LCD_ShowFloatNum1(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey);//显示一位小数变量
void LCD_ShowFloatNum2(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey);//显示两位小数变量
void LCD_ShowFloatNum3(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey);//显示三位小数变量

void LCD_ShowPicture(u16 x,u16 y,u16 length,u16 width,const u8 pic[]);//显示16位真彩图片
void LCD_ShowPictureBW(u16 x,u16 y,u16 length,u16 width,const u8 pic[],u16 fc,u16 bc,u8 mode);//显示单色图形
void LCD_ShowIntNum(u16 x,u16 y,u16 num,u8 len,u16 fc,u16 bc,u8 sizey);//显示整数变量

void LCD_Fill_Black(u16 xsta,u16 ysta,u16 xend,u16 yend); //全屏黑屏初始化显示，高刷新率


//画笔颜色
#define WHITE         	 0xFFFF //白色
#define BLACK         	 0x0000	//黑色
#define BLUE           	 0x001F //蓝色
#define BRED             0XF81F 
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800 //红色
#define MAGENTA       	 0xF81F //品红色
#define GREEN         	 0x07E0 //绿色
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0 //黄色
#define BROWN 			     0XBC40 //棕色
#define BRRED 			     0XFC07 //棕红色
#define GRAY  			     0X8430 //灰色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

#endif





