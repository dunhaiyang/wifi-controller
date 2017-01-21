#ifndef _PC_H_
#define _PC_H_


#include "APP_HAL_API.h"


extern uint8_t NRF905_SendBuffer[32];


bool Wireless_CheckCommand(uint8_t *command);


bool PC_CheckCommand(uint8_t *command, uint16_t commandLen);


void PC_SendCommand(uint8_t commandNo, uint8_t commandSerialNo, uint8_t *commandContent, uint8_t commandContentLen);


void PC_SendCommand_Boardcast(uint8_t commandNo, uint8_t commandSerialNo, uint8_t *commandContent, uint8_t commandContentLen);



#endif

