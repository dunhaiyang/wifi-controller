#ifndef __MIDDLEWARE_H_
#define __MIDDLEWARE_H_


#include "MiddlewareData.h"
#include "Websocket.h"
#include "Middleware_ControllerParameter.h"
#include "Middleware_ControllerDeviceList.h"
#include "Middleware_ControllerHeartbeat.h"
#include "Middleware_ControllerPollDevice.h"
#include "Middleware_DeviceParameter.h"
#include "Middleware_DeviceWhiteList.h"
#include "Middleware_DeviceUniversalCommand.h"
#include "Middleware_DeviceDataRecollect.h"


typedef struct
{
	uint8_t		shakehand:1;							// 是否握手成功
	
	uint8_t 	reserver:5;								// 保留未来使用
	
	uint8_t 	needFastAck:1;							// 是否需要快速回复
	
	uint8_t 	errorFastAck:1;							// 接收到服务器的指令是否是错误的指令
	
	uint8_t 	fastAckCmdNo;							// 快速回应服务器的指令号
	
	uint16_t  	fastAckSerialNo;						// 快速回应服务器的指令号的序列号
	
	uint8_t 	slowAckCmdNo;							// 慢速回应服务器的指令号
	
	uint16_t  	slowAckSerialNo;						// 慢速回应服务器的指令号的序列号
	
}Middleware_Typedef;


extern Middleware_Typedef MiddlewareInfo;


/// 握手成功标志

#define		Middleware_Get_Shakehand()				MiddlewareInfo.shakehand

#define		Middleware_Set_Shakehand()				do {MiddlewareInfo.shakehand = 1; LedAll_Switch(LED_OFF);}while(0)

#define		Middleware_Clear_Shakehand()			MiddlewareInfo.shakehand = 0


/// 是否需要发送快速回包（回包告诉服务器，控制器已经接收到服务器发送的包）

#define		Middleware_Get_FastAck()				MiddlewareInfo.needFastAck

#define		Middleware_Set_FastAck()				MiddlewareInfo.needFastAck = 1

#define		Middleware_Clear_FastAck()				MiddlewareInfo.needFastAck = 0

/// 是否需要发送快速错误回包(回包告诉服务器，控制器接收到错误的包，拒绝执行)

#define		Middleware_GetError_FastAck()			MiddlewareInfo.errorFastAck

#define		Middleware_SetError_FastAck()			MiddlewareInfo.errorFastAck = 1

#define		Middleware_ClearError_FastAck()			MiddlewareInfo.errorFastAck = 0

/// 快速回包中需要知道的指令号和指令流水号

#define		Middleware_Get_FastAckCmdNo				MiddlewareInfo.fastAckCmdNo

#define		Middleware_Set_FastAckCmdNo(BYTE)		MiddlewareInfo.fastAckCmdNo = BYTE

#define 	Middleware_Get_FastAckSerialNo			MiddlewareInfo.fastAckSerialNo

/// 慢速回包中需要知道的指令号和指令流水号

#define		Middleware_Get_SlowAckCmdNo				MiddlewareInfo.slowAckCmdNo

#define		Middleware_Set_SlowAckCmdNo(BYTE)		MiddlewareInfo.slowAckCmdNo = BYTE

#define 	Middleware_Get_SlowAckSerialNo			MiddlewareInfo.slowAckSerialNo

#define		Middleware_Set_SlowAckSerialNo(BYTE)	MiddlewareInfo.slowAckSerialNo = BYTE


void Middleware_Init(void);						// 中间件初始化


void Middleware_DealAbort(void);				// 处理异常情况


void Middleware_SendShakehand(void);			// 发送websocket握手


void Middleware_SendDataToPC(void);				// 发送websocket数据


void Middleware_ReceiveDataFromPC(void);		// 接收websocket数据


void Middleware_SendUrgencyDataToDevice(void);	// 发送无线紧急数据


void Middleware_SendNormalDataToDevice(void);	// 发送无线普通数据



#endif




