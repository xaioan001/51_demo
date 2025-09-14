#ifndef	__DIGITALLED_H
#define	__DIGITALLED_H
#include "config.h"
/**
***********************************************************
* @brief 驱动595，写一个字节
* @param 
* @return 
***********************************************************
*/
void Hc595WriteByte(u8 Data);
/**
***********************************************************
* @brief 让74H595输出
* @param 
* @return 
***********************************************************
*/
void DisplayNum(u8 num,u8 dat);
/**
***********************************************************
* @brief 显示任意5位数，65535以内
* @param disnum，要显示的数字
* @return 
***********************************************************
*/
void DisplayAnyNum(u16 disnum);
void DisplayAny1_Num(u32 disnum);
void test_display(u8 disnum);

#endif

