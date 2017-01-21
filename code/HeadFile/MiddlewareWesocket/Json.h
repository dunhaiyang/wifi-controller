#ifndef __JSON_H_
#define __JSON_H_



#include "APP_HAL_API.h"
	

// �Ӹ��������л�ȡ��Ӧ���ַ���ֵ
//
bool Json_ReceiveFrameStringValue(uint8_t **frameFirstByte, uint8_t *string, uint8_t stringLen, uint8_t **value);


// �Ӹ��������л�ȡ��Ӧ���ַ���ֵ�ĵ�һ���ַ�
//
bool Json_ReceiveFrameFirstbyteValue(uint8_t **frameFirstByte, uint8_t *string, uint8_t stringLen, uint8_t *value);


// �Ӹ��������л�ȡ��Ӧ���ֽ�ֵ
//
bool Json_ReceiveFrameCharValue(uint8_t **frameFirstByte, uint8_t *string, uint8_t stringLen, uint8_t *value);


// �Ӹ��������л�ȡ��Ӧ��˫�ֽ�ֵ
//
bool Json_ReceiveFrameUintValue(uint8_t **frameFirstByte, uint8_t *string, uint8_t stringLen, uint16_t *value);


// �Ӹ��������л�ȡ��Ӧ��·����Ϣ
//
bool Json_ReceiveFrameRouterValue(uint8_t **frameFirstByte, uint8_t *string, uint8_t stringLen, uint8_t *value);


#endif