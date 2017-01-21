#ifndef __MIDDLEWAREDATA_H_
#define __MIDDLEWAREDATA_H_


#include "APP_HAL_API.h"



// 使用这套api的时候要注意，里面不支持线程安全
//

typedef enum
{
	MiddlewareData_PollData,
	
	MiddlewareData_SendDataNormal,
	
	MiddlewareData_ReceiveDataNormal,
	
	MiddlewareData_SendDataUrgency,
	
	MiddlewareData_ReceiveDataUrgency,
	
}MiddlewareData_Enum;


typedef struct
{
	// 标志位
	//
	uint8_t 	poolDataFlag:4;							// 四位对应poolData数组是否已经分配使用
	
	uint8_t		normalSendDataFlag:4;					// 四位对应normalSendData数组是否已经分配使用
	
	uint8_t		normalReceiveDataFlag:4;				// 四位对应normalReceiveData数组是否已经分配使用
	
	uint8_t		urgencySendDataFlag:4;					// 四位对应urgencySendData数组是否已经分配使用
	
	uint8_t		urgencyReceiveDataFlag:4;				// 四位对应urgencyReceiveData数组是否已经分配使用
	
	
	// 待分配的数组队列
	//
	uint8_t		poolData[4][32];						// 存储轮询指令
	
	uint8_t		normalSendData[4][32];					// 存储普通发送指令
	
	uint8_t		normalReceiveData[4][32];				// 存储普通接收指令
	
	uint8_t		urgencySendData[4][32];					// 存储紧急发送指令
	
	uint8_t		urgencyReceiveData[4][32];				// 存储紧急接收指令
	
}MiddlewareData_t;


extern MiddlewareData_t middlewareData;


// 轮询指令
//
#define MiddlewareData_poolDataFlag						middlewareData.poolDataFlag

#define MiddlewareData_poolData							middlewareData.poolData

#define MiddlewareData_Emtpy_PoolData()					MiddlewareData_poolDataFlag = 0


// 普通发送指令
//
#define MiddlewareData_normalSendDataFlag				middlewareData.normalSendDataFlag

#define MiddlewareData_normalSendData					middlewareData.normalSendData

#define MiddlewareData_Empty_SendDataNormal()			MiddlewareData_normalSendDataFlag = 0


// 普通接收指令
//
#define MiddlewareData_normalReceiveDataFlag			middlewareData.normalReceiveDataFlag

#define MiddlewareData_normalReceiveData				middlewareData.normalReceiveData

#define MiddlewareData_Empty_ReceiveDataNormal()		MiddlewareData_normalReceiveDataFlag = 0


// 紧急发送指令
//
#define MiddlewareData_urgencySendDataFlag				middlewareData.urgencySendDataFlag

#define MiddlewareData_urgencySendData					middlewareData.urgencySendData

#define MiddlewareData_Empty_SendDataUrgency()			MiddlewareData_urgencySendDataFlag = 0


// 紧急接收指令
//
#define MiddlewareData_urgencyReceiveDataFlag			middlewareData.urgencyReceiveDataFlag

#define MiddlewareData_urgencyReceiveData				middlewareData.urgencyReceiveData

#define MiddlewareData_Empty_ReceiveDataUrgency()		MiddlewareData_urgencyReceiveDataFlag = 0


// 清空所有队列，即清零四个标志位（poolDataFlag， normalSendDataFlag， normalReceiveDataFlag， urgencySendDataFlag， urgencyReceiveDataFlag）
//
void MiddlewareData_Init(void);


// 申请对应的队列的内存，用于存放数据
//
uint8_t *MiddlewareData_Malloc(MiddlewareData_Enum type);


// 判断所在队列是否为空
//
bool MiddlewareData_IsEmpty(MiddlewareData_Enum type);


// 获取队列数据
//
uint8_t *MiddlewareData_Fetch(MiddlewareData_Enum type);


// 释放队列数据
//
void MiddlewareData_Free(MiddlewareData_Enum type);


#endif












