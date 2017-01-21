#ifndef __JSON_H_
#define __JSON_H_



#include "APP_HAL_API.h"
	

// 从负载数据中获取对应的字符串值
//
bool Json_ReceiveFrameStringValue(uint8_t **frameFirstByte, uint8_t *string, uint8_t stringLen, uint8_t **value);


// 从负载数据中获取对应的字符串值的第一个字符
//
bool Json_ReceiveFrameFirstbyteValue(uint8_t **frameFirstByte, uint8_t *string, uint8_t stringLen, uint8_t *value);


// 从负载数据中获取对应的字节值
//
bool Json_ReceiveFrameCharValue(uint8_t **frameFirstByte, uint8_t *string, uint8_t stringLen, uint8_t *value);


// 从负载数据中获取对应的双字节值
//
bool Json_ReceiveFrameUintValue(uint8_t **frameFirstByte, uint8_t *string, uint8_t stringLen, uint16_t *value);


// 从负载数据中获取对应的路由信息
//
bool Json_ReceiveFrameRouterValue(uint8_t **frameFirstByte, uint8_t *string, uint8_t stringLen, uint8_t *value);


#endif