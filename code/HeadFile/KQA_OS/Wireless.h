#ifndef __Wireless_H_
#define __Wireless_H_


#include "OS_HAL.h"


typedef struct
{
	// 私有接口
	//
	ProcVoidP_Void			init;
	
	// 公共接口
	//
	uint8_t					channelNo;						// 获取无线信道号
	
	// 公共接口
	
	ProcUint8_Void			changeChannel;					// 改变无线信道
	
	ProcVoid_Bool			avilable;						// 有数据可读
	
	ProcUint8P_Void			write;							// 发送数据
	
	ProcUint8P_Void			read;							// 接收数据
	
}Wireless;


void Wireless_Init(void *self);




#endif

