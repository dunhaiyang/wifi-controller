#ifndef __WEBSOCKET_H_
#define __WEBSOCKET_H_


#include "Json.h"


void Websocket_SendShakehand(uint8_t *locaIp, uint16_t locaPort, uint8_t *handShakeBuffer, uint16_t *handShakeBufferLen);


bool  Websocket_ReceiveShakehand(uint8_t *handShakeBuffer, uint16_t handShakeBufferLen);


// 去掉0x81和负载长度, *frameFirstByte指向第一个字节， 返回负载长度
//
uint16_t Websocket_ReceiveFrameText(uint8_t *receiveBuffer, uint16_t receiveBufferLen, uint8_t **frameFirstByte);
	

// 添加0x81和负载长度
//
//void Websocket_SendFrameText(uchar *buffer, uint buffer);
	

//void Websocket_



#endif

