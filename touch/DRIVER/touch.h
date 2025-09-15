#ifndef	__TOUCH_H
#define	__TOUCH_H
#include "type_def.h"
#define TOUCHKEYVALUETH    10000UL
#define TOUCHKEYLONGPRESS  400000UL
extern u8  xdata B_ReadKeyOk;
extern u16 xdata TK_cnt[];
/**
***********************************************************
* @brief   触摸按键获取键值
* @param 
* @return  
***********************************************************
*/
u8 GetTouchVal();
/**
***********************************************************
* @brief   触摸按键配置
* @param 
* @return  
***********************************************************
*/
void Touch_Config();

#endif