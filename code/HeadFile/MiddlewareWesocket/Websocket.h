#ifndef __WEBSOCKET_H_
#define __WEBSOCKET_H_


#include "Json.h"


void Websocket_SendShakehand(uint8_t *locaIp, uint16_t locaPort, uint8_t *handShakeBuffer, uint16_t *handShakeBufferLen);


bool  Websocket_ReceiveShakehand(uint8_t *handShakeBuffer, uint16_t handShakeBufferLen);


// ȥ��0x81�͸��س���, *frameFirstByteָ���һ���ֽڣ� ���ظ��س���
//
uint16_t Websocket_ReceiveFrameText(uint8_t *receiveBuffer, uint16_t receiveBufferLen, uint8_t **frameFirstByte);
	

// ���0x81�͸��س���
//
//void Websocket_SendFrameText(uchar *buffer, uint buffer);
	

//void Websocket_



#endif

