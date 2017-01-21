#ifndef __PARAMETER_H_
#define __PARAMETER_H_


#include "OS_HAL.h"


typedef struct
{
	// 私有接口
	//
	ProcVoidP_Void				init;
	
	
	// 公共接口
	//
	ProcUint16_Void				erase;					// 擦除
	
	ProcUint16_Uint8			read;					// 读取
	
	ProcUint16Uint8_Void		write;					// 写入
	
}Parameter;


void Parameter_Init(void *self);



#endif

