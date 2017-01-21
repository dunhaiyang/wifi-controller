#ifndef __MIDDLEWAREDATA_H_
#define __MIDDLEWAREDATA_H_


#include "APP_HAL_API.h"



// ʹ������api��ʱ��Ҫע�⣬���治֧���̰߳�ȫ
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
	// ��־λ
	//
	uint8_t 	poolDataFlag:4;							// ��λ��ӦpoolData�����Ƿ��Ѿ�����ʹ��
	
	uint8_t		normalSendDataFlag:4;					// ��λ��ӦnormalSendData�����Ƿ��Ѿ�����ʹ��
	
	uint8_t		normalReceiveDataFlag:4;				// ��λ��ӦnormalReceiveData�����Ƿ��Ѿ�����ʹ��
	
	uint8_t		urgencySendDataFlag:4;					// ��λ��ӦurgencySendData�����Ƿ��Ѿ�����ʹ��
	
	uint8_t		urgencyReceiveDataFlag:4;				// ��λ��ӦurgencyReceiveData�����Ƿ��Ѿ�����ʹ��
	
	
	// ��������������
	//
	uint8_t		poolData[4][32];						// �洢��ѯָ��
	
	uint8_t		normalSendData[4][32];					// �洢��ͨ����ָ��
	
	uint8_t		normalReceiveData[4][32];				// �洢��ͨ����ָ��
	
	uint8_t		urgencySendData[4][32];					// �洢��������ָ��
	
	uint8_t		urgencyReceiveData[4][32];				// �洢��������ָ��
	
}MiddlewareData_t;


extern MiddlewareData_t middlewareData;


// ��ѯָ��
//
#define MiddlewareData_poolDataFlag						middlewareData.poolDataFlag

#define MiddlewareData_poolData							middlewareData.poolData

#define MiddlewareData_Emtpy_PoolData()					MiddlewareData_poolDataFlag = 0


// ��ͨ����ָ��
//
#define MiddlewareData_normalSendDataFlag				middlewareData.normalSendDataFlag

#define MiddlewareData_normalSendData					middlewareData.normalSendData

#define MiddlewareData_Empty_SendDataNormal()			MiddlewareData_normalSendDataFlag = 0


// ��ͨ����ָ��
//
#define MiddlewareData_normalReceiveDataFlag			middlewareData.normalReceiveDataFlag

#define MiddlewareData_normalReceiveData				middlewareData.normalReceiveData

#define MiddlewareData_Empty_ReceiveDataNormal()		MiddlewareData_normalReceiveDataFlag = 0


// ��������ָ��
//
#define MiddlewareData_urgencySendDataFlag				middlewareData.urgencySendDataFlag

#define MiddlewareData_urgencySendData					middlewareData.urgencySendData

#define MiddlewareData_Empty_SendDataUrgency()			MiddlewareData_urgencySendDataFlag = 0


// ��������ָ��
//
#define MiddlewareData_urgencyReceiveDataFlag			middlewareData.urgencyReceiveDataFlag

#define MiddlewareData_urgencyReceiveData				middlewareData.urgencyReceiveData

#define MiddlewareData_Empty_ReceiveDataUrgency()		MiddlewareData_urgencyReceiveDataFlag = 0


// ������ж��У��������ĸ���־λ��poolDataFlag�� normalSendDataFlag�� normalReceiveDataFlag�� urgencySendDataFlag�� urgencyReceiveDataFlag��
//
void MiddlewareData_Init(void);


// �����Ӧ�Ķ��е��ڴ棬���ڴ������
//
uint8_t *MiddlewareData_Malloc(MiddlewareData_Enum type);


// �ж����ڶ����Ƿ�Ϊ��
//
bool MiddlewareData_IsEmpty(MiddlewareData_Enum type);


// ��ȡ��������
//
uint8_t *MiddlewareData_Fetch(MiddlewareData_Enum type);


// �ͷŶ�������
//
void MiddlewareData_Free(MiddlewareData_Enum type);


#endif












