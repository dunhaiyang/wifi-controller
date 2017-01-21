#ifndef __UART2_H_
#define __UART2_H_


#include "types.h"


void Uart2_Init( void );


uint16_t Uart2_Mode0_ReceiveString(uint8_t *buffer);


uint16_t Uart2_Mode1_ReceiveString(uint8_t **buffer);


void Uart2_SetMode0(void);


void Uart2_SetMode1(void);


void Uart2_SendByte(uint8_t byte);


void Uart2_SendString(uint8_t *string);


void Uart2_SendNString(uint8_t *string, uint8_t count);


#endif