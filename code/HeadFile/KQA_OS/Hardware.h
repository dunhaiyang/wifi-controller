#ifndef __HARDWARE_H_
#define __HARDWARE_H_




#include "OS_HAL.h"


typedef struct
{
	// 私有接口
	//
	ProcVoidP_Void		init;
	
	// 公共接口
	//
	ProcVoid_Void		reboot;								/// 重启
	
	ProcVoid_Void		feedWatchdog;						/// 喂狗
	
}Hardware;


void Hardware_Init(void *self);



#endif

