#ifndef	__DIGITALLED_H
#define	__DIGITALLED_H
#include "config.h"
/**
***********************************************************
* @brief ����595��дһ���ֽ�
* @param 
* @return 
***********************************************************
*/
void Hc595WriteByte(u8 Data);
/**
***********************************************************
* @brief ��74H595���
* @param 
* @return 
***********************************************************
*/
void DisplayNum(u8 num,u8 dat);
/**
***********************************************************
* @brief ��ʾ����5λ����65535����
* @param disnum��Ҫ��ʾ������
* @return 
***********************************************************
*/
void DisplayAnyNum(u16 disnum);
void DisplayAny1_Num(u32 disnum);
void test_display(u8 disnum);

#endif

