#ifndef __MIDDLEWARE_DEVICEWHITELIST_H_
#define __MIDDLEWARE_DEVICEWHITELIST_H_


#include "Command_Temporary.h"
//#include "Command_DeviceInfo.h"
#include "Json.h"
#include "MiddlewareData.h"
//#include "Kernel_PC.h"


extern	uint16_t	DeviceWhiteList_SerialNo;


bool DeviceWhiteList_DealFrameText(uint8_t **Data);


void DeviceWhiteList_SendFrameTextToPc(uint16_t cmdSerialNo, uint8_t *Data);



#endif


