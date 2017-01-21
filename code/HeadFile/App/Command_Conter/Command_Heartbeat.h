#ifndef __COMMAND_HEARTBEAT_H_
#define __COMMAND_HEARTBEAT_H_



#include "Pc.h"
#include "Command_Temporary.h"
#include "Command_NormalDeviceInfo.h"
#include "Command_HookFunction.h"


void Heartbeat_SendDataToPC(void);


void Heartbeat_DealData(uint8_t *Data);


#endif