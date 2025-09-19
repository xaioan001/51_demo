#ifndef __LCD_BASE_H
#define __LCD_BASE_H	


#include "type_def.h"

#define USE_HORIZONTAL 3  //2,3Ϊ������ʾ��0,1Ϊ������ʾ������Ŀ��ֻ�ṩ������ʾ

#if USE_HORIZONTAL==2||USE_HORIZONTAL==3
#define LCD_W 320
#define LCD_H 240
#endif

void LCD_Writ_Bus(u8 dat);//ģ��SPIʱ��
void LCD_WR_DATA8(u8 dat);//д��һ���ֽ�
void LCD_WR_DATA(u16 dat);//д�������ֽ�
void LCD_WR_REG(u8 dat);  //д��һ��ָ��

void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//�������꺯��
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);//ָ�����������ɫ
void LCD_DrawPoint(u16 x,u16 y,u16 color);//��ָ��λ�û�һ����
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);//��ָ��λ�û�һ����

void LCD_ShowChinese(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode);//��ʾ���ִ�
void LCD_ShowChinese16x16(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode);//��ʾ����16x16����
void LCD_ShowChinese24x24(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode);//��ʾ����24x24����


void LCD_ShowChar(u16 x,u16 y,u8 num,u16 fc,u16 bc,u8 sizey,u8 mode);//��ʾһ���ַ�
void LCD_ShowString(u16 x,u16 y,const u8 *p,u16 fc,u16 bc,u8 sizey,u8 mode);//��ʾ�ַ���
void Show_StringandChinese(u16 x,u16 y,u8 *str, u16 fc,u16 bc,u8 sizey,u8 mode); //���֡��ַ��������ʾ
u32 mypow(u8 m,u8 n);//����

//void LCD_ShowFloatNum1(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey);//��ʾһλС������
void LCD_ShowFloatNum2(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey);//��ʾ��λС������
void LCD_ShowFloatNum3(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey);//��ʾ��λС������

void LCD_ShowPicture(u16 x,u16 y,u16 length,u16 width,const u8 pic[]);//��ʾ16λ���ͼƬ
void LCD_ShowPictureBW(u16 x,u16 y,u16 length,u16 width,const u8 pic[],u16 fc,u16 bc,u8 mode);//��ʾ��ɫͼ��
void LCD_ShowIntNum(u16 x,u16 y,u16 num,u8 len,u16 fc,u16 bc,u8 sizey);//��ʾ��������

void LCD_Fill_Black(u16 xsta,u16 ysta,u16 xend,u16 yend); //ȫ��������ʼ����ʾ����ˢ����


//������ɫ
#define WHITE         	 0xFFFF //��ɫ
#define BLACK         	 0x0000	//��ɫ
#define BLUE           	 0x001F //��ɫ
#define BRED             0XF81F 
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800 //��ɫ
#define MAGENTA       	 0xF81F //Ʒ��ɫ
#define GREEN         	 0x07E0 //��ɫ
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0 //��ɫ
#define BROWN 			     0XBC40 //��ɫ
#define BRRED 			     0XFC07 //�غ�ɫ
#define GRAY  			     0X8430 //��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			     0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

#endif





