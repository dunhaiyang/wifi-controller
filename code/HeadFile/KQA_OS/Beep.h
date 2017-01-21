#ifndef __BEEP_H_
#define __BEEP_H_


#include "OS_HAL.h"


enum
{
	BEEP_ON = 0,
	
	BEEP_OFF = 1,
};


typedef struct
{
	// 私有接口
	//
	ProcVoidP_Void			init;

	// 公共接口
	//
	ProcVoid_Void			run;								// BEEP任务(需要周期性地调用)
	
	ProcUint32_Void			setTime;							// 设置蜂鸣器响多久
	
	ProcUint8_Void			action;								// 控制蜂鸣器的行为
	
}Beep;


void Beep_Init(void *self);






#endif


