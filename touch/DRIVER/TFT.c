#include	"STC8G_H_GPIO.h"
#include "type_def.h"
#include	"STC8G_H_Delay.h"
#include	"STC8G_H_Delay.h"
#include "STC8H.H"
#define LCD_DC   P60
#define LCD_RES  P70
#define LCD_CS	 P43
/**
***********************************************************
* @brief   SPI初始化
* @param 
* @return  
***********************************************************
*/
void SPI_Init()
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义

	GPIO_InitStructure.Pin  = GPIO_Pin_0;
	GPIO_InitStructure.Mode = GPIO_OUT_PP;
	GPIO_Inilize(GPIO_P4,&GPIO_InitStructure);	
}

/**
***********************************************************
* @brief   SPI发送一个字节
* @param 
* @return  
***********************************************************
*/
void SPI_SendByte(u8 dat) {
    SPDAT = dat;
    while (!(SPSTAT & 0x80)); // 等待发送完成
    SPSTAT = 0xC0;            // 清标志
}

/**
***********************************************************
* @brief   LCD写命令
* @param 
* @return  
***********************************************************
*/
void LCD_WriteCmd(u8 cmd) {
    LCD_DC = 0;
    LCD_CS = 0;
    SPI_SendByte(cmd);
    LCD_CS = 1;
}

/**
***********************************************************
* @brief   LCD写数据
* @param 
* @return  
***********************************************************
*/
void LCD_WriteData(u8 dat) {
    LCD_DC = 1;
    LCD_CS = 0;
    SPI_SendByte(dat);
    LCD_CS = 1;
}

/**
***********************************************************
* @brief   LCD写数据颜色
* @param 
* @return  
***********************************************************
*/
void LCD_WriteData16(u16 dat) {
    LCD_WriteData(dat >> 8);
    LCD_WriteData(dat & 0xFF);
}

/**
***********************************************************
* @brief   LCD复位
* @param 
* @return  
***********************************************************
*/
void LCD_Reset() {
    LCD_RES = 0;
    delay_ms(100);
    LCD_RES = 1;
    delay_ms(100);
}
/**
***********************************************************
* @brief   LCD初始化
* @param 
* @return  
***********************************************************
*/
void LCD_Init() {
    LCD_Reset();

    LCD_WriteCmd(0x36); // MADCTL
    LCD_WriteData(0x00);

    LCD_WriteCmd(0x3A); // COLMOD
    LCD_WriteData(0x55); // 16bit/pixel

    LCD_WriteCmd(0xB2); // PORCTRL
    LCD_WriteData(0x0C);
    LCD_WriteData(0x0C);
    LCD_WriteData(0x00);
    LCD_WriteData(0x33);
    LCD_WriteData(0x33);

    LCD_WriteCmd(0xB7); // GCTRL
    LCD_WriteData(0x35);

    LCD_WriteCmd(0xBB); // VCOMS
    LCD_WriteData(0x19);

    LCD_WriteCmd(0xC0); // LCMCTRL
    LCD_WriteData(0x2C);

    LCD_WriteCmd(0xC2); // VDVVRHEN
    LCD_WriteData(0x01);

    LCD_WriteCmd(0xC3); // VRHS
    LCD_WriteData(0x12);

    LCD_WriteCmd(0xC4); // VDVS
    LCD_WriteData(0x20);

    LCD_WriteCmd(0xC6); // FRCTRL2
    LCD_WriteData(0x0F);

    LCD_WriteCmd(0xD0); // PWCTRL1
    LCD_WriteData(0xA4);
    LCD_WriteData(0xA1);

    LCD_WriteCmd(0xE0); // PVGAMCTRL
    LCD_WriteData(0xD0);
    LCD_WriteData(0x04);
    LCD_WriteData(0x0D);
    LCD_WriteData(0x11);
    LCD_WriteData(0x13);
    LCD_WriteData(0x2B);
    LCD_WriteData(0x3F);
    LCD_WriteData(0x54);
    LCD_WriteData(0x4C);
    LCD_WriteData(0x18);
    LCD_WriteData(0x0D);
    LCD_WriteData(0x0B);
    LCD_WriteData(0x1F);
    LCD_WriteData(0x23);

    LCD_WriteCmd(0xE1); // NVGAMCTRL
    LCD_WriteData(0xD0);
    LCD_WriteData(0x04);
    LCD_WriteData(0x0C);
    LCD_WriteData(0x11);
    LCD_WriteData(0x13);
    LCD_WriteData(0x2C);
    LCD_WriteData(0x3F);
    LCD_WriteData(0x44);
    LCD_WriteData(0x51);
    LCD_WriteData(0x2F);
    LCD_WriteData(0x1F);
    LCD_WriteData(0x1F);
    LCD_WriteData(0x20);
    LCD_WriteData(0x23);

    LCD_WriteCmd(0x21); // INVON
    LCD_WriteCmd(0x11); // SLPOUT
    delay_ms(120);
    LCD_WriteCmd(0x29); // DISPON
}

/**
***********************************************************
* @brief   LCD设置显示区域
* @param 
* @return  
***********************************************************
*/
void LCD_SetWindow(u16 x1, u16 y1, u16 x2, u16 y2) {
    LCD_WriteCmd(0x2A); // CASET
    LCD_WriteData(x1 >> 8);
    LCD_WriteData(x1 & 0xFF);
    LCD_WriteData(x2 >> 8);
    LCD_WriteData(x2 & 0xFF);

    LCD_WriteCmd(0x2B); // RASET
    LCD_WriteData(y1 >> 8);
    LCD_WriteData(y1 & 0xFF);
    LCD_WriteData(y2 >> 8);
    LCD_WriteData(y2 & 0xFF);

    LCD_WriteCmd(0x2C); // RAMWR
}

/**
***********************************************************
* @brief   LCD清屏
* @param 
* @return  
***********************************************************
*/
void LCD_Clear(u16 color) {
    u32 i;
    LCD_SetWindow(0, 0, 239, 319);
    for (i = 0; i < 240 * 320; i++) {
        LCD_WriteData16(color);
    }
}

//void main() {
//    SPI_Init();
//    LCD_Init();
//    LCD_Clear(0xFFFF); // 白色清屏
//    while(1);
//}












