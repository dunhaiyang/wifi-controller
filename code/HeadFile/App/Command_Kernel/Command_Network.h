#ifndef __COMMAND_NETWORK_H_
#define __COMMAND_NETWORK_H_


// 控制器指令
//
#include "Command_Heartbeat.h"

#include "Command_ControlerTest.h"

#include "Command_ControlerParameter.h"

#include "Command_ControlerDeviceList.h"

#include "Command_ControlerWorkMode.h"


// 中继指令
//
#include "Command_RepeaterTest.h"

#include "Command_RepeaterParameter.h"


// 设备指令
//
#include "Command_DevicePool.h"

#include "Command_DeviceTest.h"

#include "Command_OneCardDataUpload.h"

#include "Command_OneCardDataUploadDelete.h"

#include "Command_OneCardOperation.h"

#include "Command_DeviceParameterRead.h"

#include "Command_ReadOneOfflineData.h"

#include "Command_DeleteOneOfflineData.h"

#include "Command_DeleteSomeAreaData.h"

#include "Command_RestoreDefaultConfigure.h"

#include "Command_ReadWriteConfigureParameter.h"

#include "Command_ChangeDeviceSerialNo.h"

#include "Command_RealtimeControl.h"

#include "Command_ReadAllTradeRecord.h"

#include "Command_RestoreDataStructure.h"

#include "Command_ReadWhiteListPointer.h"

#include "Command_SerialNoWatchAndConfigure.h"

#include "Command_ReadWhiteList.h"

#include "Command_WhiteListUpload.h"

#include "Command_WhiteListInit.h"

#include "Command_ProgramUpdate.h"

#include "Command_SearchIp.h"

#include "Command_NetworkParameter.h"


void Network_DealControlData(uint8_t *command);




#endif

