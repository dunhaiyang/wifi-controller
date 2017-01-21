#ifndef __MIDDLEWARE_DEVICE_DATA_RECOLLECT_H_
#define __MIDDLEWARE_DEVICE_DATA_RECOLLECT_H_


#include "Command_Temporary.h"
#include "Json.h"
//#include "Command_DeviceInfo.h"
#include "MiddlewareData.h"
//#include "Kernel_PC.h"


bool DeviceDataRecollect_DealFrameText(uint8_t **Data);


void DeviceDataRecollect_SendFrameTextToPc(uint16_t cmdSerialNo, uint8_t *Data);




#endif
