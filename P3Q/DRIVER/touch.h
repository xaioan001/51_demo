#ifndef	__TOUCH_H
#define	__TOUCH_H
#include "type_def.h"
#define TOUCHKEYMAX        15000
#define TOUCHKEYVALUETH    1000
#define TOUCHKEYLONGPRESS  400000UL
extern u8  xdata B_ReadKeyOk;
extern u16 xdata TK_cnt[];
/**
***********************************************************
* @brief   ����������ȡ��ֵ
* @param 
* @return  
***********************************************************
*/
u8 GetTouchVal();
/**
***********************************************************
* @brief   ������������
* @param 
* @return  
***********************************************************
*/
void Touch_Config();
/**
***********************************************************
* @brief  �����ϵ�û�а��µļ�ֵ
* @param 
* @return  
***********************************************************
*/
void SaveTouchZeroValue();

#endif