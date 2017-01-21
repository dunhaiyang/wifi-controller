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
	uint8_t		shakehand:1;							// �Ƿ����ֳɹ�
	
	uint8_t 	reserver:5;								// ����δ��ʹ��
	
	uint8_t 	needFastAck:1;							// �Ƿ���Ҫ���ٻظ�
	
	uint8_t 	errorFastAck:1;							// ���յ���������ָ���Ƿ��Ǵ����ָ��
	
	uint8_t 	fastAckCmdNo;							// ���ٻ�Ӧ��������ָ���
	
	uint16_t  	fastAckSerialNo;						// ���ٻ�Ӧ��������ָ��ŵ����к�
	
	uint8_t 	slowAckCmdNo;							// ���ٻ�Ӧ��������ָ���
	
	uint16_t  	slowAckSerialNo;						// ���ٻ�Ӧ��������ָ��ŵ����к�
	
}Middleware_Typedef;


extern Middleware_Typedef MiddlewareInfo;


/// ���ֳɹ���־

#define		Middleware_Get_Shakehand()				MiddlewareInfo.shakehand

#define		Middleware_Set_Shakehand()				do {MiddlewareInfo.shakehand = 1; LedAll_Switch(LED_OFF);}while(0)

#define		Middleware_Clear_Shakehand()			MiddlewareInfo.shakehand = 0


/// �Ƿ���Ҫ���Ϳ��ٻذ����ذ����߷��������������Ѿ����յ����������͵İ���

#define		Middleware_Get_FastAck()				MiddlewareInfo.needFastAck

#define		Middleware_Set_FastAck()				MiddlewareInfo.needFastAck = 1

#define		Middleware_Clear_FastAck()				MiddlewareInfo.needFastAck = 0

/// �Ƿ���Ҫ���Ϳ��ٴ���ذ�(�ذ����߷����������������յ�����İ����ܾ�ִ��)

#define		Middleware_GetError_FastAck()			MiddlewareInfo.errorFastAck

#define		Middleware_SetError_FastAck()			MiddlewareInfo.errorFastAck = 1

#define		Middleware_ClearError_FastAck()			MiddlewareInfo.errorFastAck = 0

/// ���ٻذ�����Ҫ֪����ָ��ź�ָ����ˮ��

#define		Middleware_Get_FastAckCmdNo				MiddlewareInfo.fastAckCmdNo

#define		Middleware_Set_FastAckCmdNo(BYTE)		MiddlewareInfo.fastAckCmdNo = BYTE

#define 	Middleware_Get_FastAckSerialNo			MiddlewareInfo.fastAckSerialNo

/// ���ٻذ�����Ҫ֪����ָ��ź�ָ����ˮ��

#define		Middleware_Get_SlowAckCmdNo				MiddlewareInfo.slowAckCmdNo

#define		Middleware_Set_SlowAckCmdNo(BYTE)		MiddlewareInfo.slowAckCmdNo = BYTE

#define 	Middleware_Get_SlowAckSerialNo			MiddlewareInfo.slowAckSerialNo

#define		Middleware_Set_SlowAckSerialNo(BYTE)	MiddlewareInfo.slowAckSerialNo = BYTE


void Middleware_Init(void);						// �м����ʼ��


void Middleware_DealAbort(void);				// �����쳣���


void Middleware_SendShakehand(void);			// ����websocket����


void Middleware_SendDataToPC(void);				// ����websocket����


void Middleware_ReceiveDataFromPC(void);		// ����websocket����


void Middleware_SendUrgencyDataToDevice(void);	// �������߽�������


void Middleware_SendNormalDataToDevice(void);	// ����������ͨ����



#endif




