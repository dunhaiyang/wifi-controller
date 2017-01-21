#ifndef __UART1_H_
#define __UART1_H_

#include "types.h"

#ifdef  Uart1_Debug


void Uart1_Init( void );



bit Uart1_Available(void);



uint8_t	Uart1_ReceiveByte(void);



void Uart1_SendByte(uint8_t send_data);



void Uart1_SendNString(uint8_t *send_string, uint8_t len);



void Uart1_SendString(uint8_t *send_string);
    
 
#endif



#endif