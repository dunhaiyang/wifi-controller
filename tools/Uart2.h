#ifndef __UART2_H_
#define __UART2_H_


#include "types.h"


#define Uart2_RXLEN		80

extern  uchar 	xdata	Uart2_RxBufCount;
extern  uchar 	xdata 	Uart2_RxBuf[Uart2_RXLEN]; 	                    // 接收缓冲区


extern  bit           	UartPack_ReciveCmdOk;							// 接收命令正确标志
extern  bit			  	UartPack_0x10Received;   						// 是否已经接收到了0x10
extern  bit				UartPack_Started;								// 通讯包是否已经开始


void Uart2_Init( void );


void Uart2_SendByte(uchar send_data);


void Uart2_SendString(uchar *string);


#endif