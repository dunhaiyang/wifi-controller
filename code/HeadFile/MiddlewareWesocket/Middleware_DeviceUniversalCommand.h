#ifndef __MIDDLEWARE_DEVICE_UNIVERSAL_COMMAND_
#define __MIDDLEWARE_DEVICE_UNIVERSAL_COMMAND_


#include "Command_Temporary.h"
//#include "Command_DeviceInfo.h"
#include "Json.h"
#include "MiddlewareData.h"
//#include "Kernel_PC.h"


bool DeviceUniversalCommand_DealFrameText(uint8_t **Data);


void DeviceUniversalCommand_SendFrameTextToPc(uint16_t cmdSerialNo, uint8_t *Data);



#endif

