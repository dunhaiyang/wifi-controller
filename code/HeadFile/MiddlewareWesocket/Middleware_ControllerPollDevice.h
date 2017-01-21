#ifndef __MIDDLEWARE_CONTROLLERPOLLDEVICE_H_
#define __MIDDLEWARE_CONTROLLERPOLLDEVICE_H_


#include "Wireless.h"
#include "Command_OneCardDataUpload.h"
#include "Command_ReadOneOfflineData.h"


void ControllerPollDevice_SendPollDataToDevice(void);


void ControllerPollDevice_ReadDirectData(void);


void ControllerPollDevice_RecoverPollStatus(void);


#endif
