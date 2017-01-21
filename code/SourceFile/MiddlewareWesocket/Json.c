#include "Json.h"


#define Json_GetDecimal(v1, v2, v3)					(((v1 - '0') * 100) + ((v2 - '0') * 10) + (v3 - '0'))

#define Json_GetDoubleDecimal(v1, v2, v3, v4, v5)	(((v1 - '0') * 10000) + ((v2 - '0') * 1000) + ((v3 - '0') * 100) + ((v4 - '0')* 10) + (v5 - '0'))


// 从负载数据中获取对应的字符串值
//
bool Json_ReceiveFrameStringValue(uint8_t **frameFirstByte, uint8_t *string, uint8_t stringLen, uint8_t **value)
{
	*value = strstr(*frameFirstByte, string);
	
	if (*value)
	{
		*value += stringLen;
		
		*frameFirstByte = *value;
		
		return 1;
	}
	
	return 0;
}


// 从负载数据中获取对应的字符串值的第一个字符
//
bool Json_ReceiveFrameFirstbyteValue(uint8_t **frameFirstByte, uint8_t *string, uint8_t stringLen, uint8_t *value)
{
	uint8_t *tmpBuffer = strstr(*frameFirstByte, string);
	
	if (tmpBuffer)
	{
		tmpBuffer += stringLen;
		
		*frameFirstByte = tmpBuffer;
		
		*value = *tmpBuffer;
		
		return 1;
	}
	
	return 0;
}


// 从负载数据中获取对应的字节值
//
bool Json_ReceiveFrameCharValue(uint8_t **frameFirstByte, uint8_t *string, uint8_t stringLen, uint8_t *value)
{
	uint8_t *tmpBuffer = strstr(*frameFirstByte, string);
	
	if (tmpBuffer)
	{
		tmpBuffer += stringLen;
		
		*frameFirstByte = tmpBuffer;
		
		*value = Json_GetDecimal(tmpBuffer[0], tmpBuffer[1], tmpBuffer[2]);
		
		return 1;
	}
	
	return 0;
}


// 从负载数据中获取对应的双字节值
//
bool Json_ReceiveFrameUintValue(uint8_t **frameFirstByte, uint8_t *string, uint8_t stringLen, uint16_t *value)
{
	uint8_t *tmpBuffer = strstr(*frameFirstByte, string);
	
	if (tmpBuffer)
	{
		tmpBuffer += stringLen;
		
		*frameFirstByte = tmpBuffer;
		
		*value = Json_GetDoubleDecimal(tmpBuffer[0], tmpBuffer[1], tmpBuffer[2], tmpBuffer[3], tmpBuffer[4]);
		
		return 1;
	}
	
	return 0;
}

// 从负载数据中获取对应的路由信息
//
bool Json_ReceiveFrameRouterValue(uint8_t **frameFirstByte, uint8_t *string, uint8_t stringLen, uint8_t *value)
{
	uint8_t *tmpBuffer = strstr(*frameFirstByte, string);
	
	if (tmpBuffer)
	{
		tmpBuffer += stringLen;
		
		*frameFirstByte = tmpBuffer;
		
		value[0] = Json_GetDecimal(tmpBuffer[0], tmpBuffer[1], tmpBuffer[2]);
		
		value[1] = Json_GetDecimal(tmpBuffer[3], tmpBuffer[4], tmpBuffer[5]);
		
		value[2] = Json_GetDecimal(tmpBuffer[6], tmpBuffer[7], tmpBuffer[8]);
		
		return 1;
	}
	
	return 0;
}



















