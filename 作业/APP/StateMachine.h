#ifndef		__STATEMACHINE_H
#define		__STATEMACHINE_H
#include "type_def.h"



/**
***********************************************************
* @brief   状态机获取状态
* @param 
* @return  实时状态序号
***********************************************************
*/
u8 Getstate(u8 key,u16 VAL);
/**
***********************************************************
* @brief   主状态机
* @param 
* @return  
***********************************************************
*/
void StateMachine(u8 state,u8 keyNum);

#endif





