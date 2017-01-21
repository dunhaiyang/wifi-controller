#ifndef __MIDDLEWARE_DEVICEPARAMETER_H_
#define __MIDDLEWARE_DEVICEPARAMETER_H_


#include "Command_Temporary.h"
//#include "Command_DeviceInfo.h"
#include "Json.h"
#include "MiddlewareData.h"
//#include "Kernel_PC.h"


bool DeviceParameter_DealFrameText(uint8_t **Data);


void DeviceParameter_SendFrameTextToPc(uint16_t cmdSerialNo, uint8_t *Data);




#endif