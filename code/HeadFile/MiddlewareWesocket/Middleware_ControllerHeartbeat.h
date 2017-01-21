#ifndef __MIDDLEWARE_CONTROLLERHEATBEAT_H_
#define __MIDDLEWARE_CONTROLLERHEATBEAT_H_



#include "Json.h"
#include "Command_ControlerInfo.h"
//#include "Command_DeviceInfo.h"



bool ControllerHeartbeat_DealFrameText(uint8_t **Data);



void ControllerHeartbeat_SendFrameTextToPc(uint8_t *Data);



#endif

