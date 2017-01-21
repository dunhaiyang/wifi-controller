#include "Websocket.h"


#define	WEBSOCK_HEADER_GET								"GET "

#define WEBSOCK_HEADER_GET_LENGTH						4

#define WEBSOCK_HEADER_GET_ADDRESS						"/apartment/websocket/control?00000026"

#define WEBSOCK_HEADER_GET_ADDRESS_LENGTH				37

#define WEBSOCK_HEADER_HTTP								" HTTP/1.1\r\n"

#define WEBSOCK_HEADER_HTTP_LENGTH						11

#define WEBSOCK_HEADER_HOST								"Host: "

#define WEBSOCK_HEADER_HOST_LENGTH						6

#define WEBSOCK_HEADER_UPGRADE							"Upgrade: websocket\r\n"

#define WEBSOCK_HEADER_UPGRADE_LENGTH					20

#define WEBSOCK_HEADER_CONNECTION						"Connection: Upgrade\r\n"

#define WEBSOCK_HEADER_CONNECTION_LENGTH				21

#define WEBSOCK_HEADER_KEY								"Sec-WebSocket-Key: v0mFxeDYcUHVLZuNnLmIlg==\r\n"

#define WEBSOCK_HEADER_KEY_LENGTH						45

#define WEBSOCK_HEADER_VERSION							"Sec-WebSocket-Version: 13\r\n"

#define WEBSOCK_HEADER_VERSION_LENGTH					27

#define WEBSOCK_HEADER_PRAGMA							"Pragma: no-cache\r\n"

#define WEBSOCK_HEADER_PRAGMA_LENGTH					18

#define WEBSOCK_HEADER_CONTROL							"Cache-Control: no-cache\r\n\r\n"

#define WEBSOCK_HEADER_CONTROL_LENGTH					27


void Websocket_SendShakehand(uint8_t *locaIp, uint16_t locaPort, uint8_t *handShakeBuffer, uint16_t *handShakeBufferLen)
{
	uint16_t	handShakeLen = 0;
	
	//  检查参数合法性
	//
//	if (!ip || !handShakeBuffer && !handShakeBufferLen)
//	{
//		return 0;
//	}
	
	// GET /websocket/controller?12345678 HTTP/1.1\r\n
	//
	memcpy(handShakeBuffer + handShakeLen, WEBSOCK_HEADER_GET, WEBSOCK_HEADER_GET_LENGTH);
	handShakeLen += WEBSOCK_HEADER_GET_LENGTH;
	
	memcpy(handShakeBuffer + handShakeLen, WEBSOCK_HEADER_GET_ADDRESS, WEBSOCK_HEADER_GET_ADDRESS_LENGTH);
	handShakeLen += WEBSOCK_HEADER_GET_ADDRESS_LENGTH;
	
	memcpy(handShakeBuffer + handShakeLen, WEBSOCK_HEADER_HTTP, WEBSOCK_HEADER_HTTP_LENGTH);
	handShakeLen += WEBSOCK_HEADER_HTTP_LENGTH;
	
	// Host: xxx.xxx.xxx.xxx:xxxx\r\n
	//
	memcpy(handShakeBuffer + handShakeLen, WEBSOCK_HEADER_HOST, WEBSOCK_HEADER_HOST_LENGTH);
	handShakeLen += WEBSOCK_HEADER_HOST_LENGTH;
	
	handShakeLen += sprintf(handShakeBuffer + handShakeLen, "%u.%u.%u.%u:%u\r\n", (uint16_t)(locaIp[0]),
																				  (uint16_t)(locaIp[1]),
																				  (uint16_t)(locaIp[2]),
																				  (uint16_t)(locaIp[3]),
																				  (uint16_t)(locaPort));
	// Upgrade: websocket\r\n
	//
	memcpy(handShakeBuffer + handShakeLen, WEBSOCK_HEADER_UPGRADE, WEBSOCK_HEADER_UPGRADE_LENGTH);
	handShakeLen += WEBSOCK_HEADER_UPGRADE_LENGTH;
	
	// Connection: Upgrade\r\n
	//
	memcpy(handShakeBuffer + handShakeLen, WEBSOCK_HEADER_CONNECTION, WEBSOCK_HEADER_CONNECTION_LENGTH);
	handShakeLen += WEBSOCK_HEADER_CONNECTION_LENGTH;
	
	// Sec-WebSocket-Key: xxxxxxxxxxxxxxxxxxx\r\n
	//
	memcpy(handShakeBuffer + handShakeLen, WEBSOCK_HEADER_KEY, WEBSOCK_HEADER_KEY_LENGTH);
	handShakeLen += WEBSOCK_HEADER_KEY_LENGTH;
	
	// Sec_WebSocket-Version: 13\r\n
	//
	memcpy(handShakeBuffer + handShakeLen, WEBSOCK_HEADER_VERSION, WEBSOCK_HEADER_VERSION_LENGTH);
	handShakeLen += WEBSOCK_HEADER_VERSION_LENGTH;
	
	// Pragma: no-cache\r\n
	//
	memcpy(handShakeBuffer + handShakeLen, WEBSOCK_HEADER_PRAGMA, WEBSOCK_HEADER_PRAGMA_LENGTH);
	handShakeLen += WEBSOCK_HEADER_PRAGMA_LENGTH;
	
	// Cache-Control: no-cache\r\n
	//
	memcpy(handShakeBuffer + handShakeLen, WEBSOCK_HEADER_CONTROL, WEBSOCK_HEADER_CONTROL_LENGTH);
	handShakeLen += WEBSOCK_HEADER_CONTROL_LENGTH;
	
	// 设置websocket的字符串
	//
	*handShakeBufferLen = handShakeLen;
}


bool Websocket_ReceiveShakehand(uint8_t *handShakeBuffer, uint16_t handShakeBufferLen)
{
	handShakeBuffer[handShakeBufferLen] = 0;
	
	if (strstr(handShakeBuffer, "HTTP/1.1 101"))
	{
		return 1;
	}
	
	return 0;
}



// receiveBuffer指向数据包（帧头+负载数据）， 长度为receiveBufferLen
// frameFirstByte最终指向负载数据（不包括负载长度和掩码）的第一个字节的位置， 返回负载数据的长度
//
uint16_t Websocket_ReceiveFrameText(uint8_t *receiveBuffer, uint16_t receiveBufferLen, uint8_t **frameFirstByte)
{
	uint16_t  payloadLen = 0;
	
	// 检查有没有接收到websocket的帧头
	//
	if (receiveBuffer[0] != 0x81)
	{
		return 0;
	}
	
	// 获取websocket的负载长度
	//
	if (receiveBuffer[1] < 0x7E)
	{
		payloadLen = receiveBuffer[1];
		
		*frameFirstByte = receiveBuffer + 2;
		
		receiveBufferLen -= 2;
	}
	else if (receiveBuffer[1] == 0x7E)
	{
		payloadLen = (receiveBuffer[2] << 8) | receiveBuffer[3];
		
		*frameFirstByte = receiveBuffer + 4;
		
		receiveBufferLen -= 4;
	}
	else
	{
		return 0;
	}
	
	// 对比数据长度和负载长度
	//
	if (payloadLen != receiveBufferLen)
	{
		return 0;
	}
	
	return payloadLen;
}









