#ifndef __UART2_H_
#define __UART2_H_


#include "types.h"


#define Uart2_RXLEN		80

extern  uchar 	xdata	Uart2_RxBufCount;
extern  uchar 	xdata 	Uart2_RxBuf[Uart2_RXLEN]; 	                    // ���ջ�����


extern  bit           	UartPack_ReciveCmdOk;							// ����������ȷ��־
extern  bit			  	UartPack_0x10Received;   						// �Ƿ��Ѿ����յ���0x10
extern  bit				UartPack_Started;								// ͨѶ���Ƿ��Ѿ���ʼ


void Uart2_Init( void );


void Uart2_SendByte(uchar send_data);


void Uart2_SendString(uchar *string);


#endif