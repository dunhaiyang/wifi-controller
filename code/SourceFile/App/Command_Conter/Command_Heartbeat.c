#include "Command_Heartbeat.h"


void Heartbeat_SendDataToPC(void)
{
    uint8_t i;
    uint8_t howManyDeviceList = 0;
	uint8_t DeviceListStatus = 0;
    
    // 1. 获取所有有效设备列表的设备状态
    //
    for (i = 0; i < NormalDeviceListSum; ++i)
    {
        // 找到有效设备列表数据，填充进心跳包中，然后发送给PC
        //
        if (NormalDeviceList[i].deviceValidFlag)
        {
			
			// 填充设备列表的状态
			//
			if (NormalDeviceList[i].deviceOnline)
			{
				DeviceListStatus = 0x01;
			}
			else
			{
				DeviceListStatus = 0x00;
			}
			
			// 设备总数计数
			//
            howManyDeviceList++;
			
			// 填充设备列表的信息
			//
			SocketData_SendBuffer[(howManyDeviceList - 1) * 4 + 1] = NormalDeviceList[i].deviceNumber[0];
			SocketData_SendBuffer[(howManyDeviceList - 1) * 4 + 2] = NormalDeviceList[i].deviceNumber[1];
			SocketData_SendBuffer[(howManyDeviceList - 1) * 4 + 3] = NormalDeviceList[i].deviceType;
			SocketData_SendBuffer[(howManyDeviceList - 1) * 4 + 4] = DeviceListStatus;
        }
    }
    
    // 2. 有效设备总数
    //
    SocketData_SendBuffer[0] = howManyDeviceList;
    
    
    // 3. 控制器的状态（年月日时分秒）
    //
	SocketData_SendBuffer[(howManyDeviceList - 1) * 4 + 5] = IsStartScan()? 0x31:0x32;
	SocketData_SendBuffer[(howManyDeviceList - 1) * 4 + 6] = ControlerInfo.FirstBootup;
    
    // 4. 主动发送心跳指令(0x71号指令)给PC
    //
    PC_SendCommand(0x71, DeviceDataSerialNo++, SocketData_SendBuffer,  howManyDeviceList * 4 + 3);
	
	// 5. 心跳请求的钩子函数
	//
	HookFunction_HeartbeatReq();
}


void Heartbeat_DealData(uint8_t *Data)
{
    // 把BCD码转化成整数
    //
    SysTime.year    = DCB(Data[Enum_CommandContent + 0]);
    
    SysTime.month   = DCB(Data[Enum_CommandContent + 1]);
    
    SysTime.day     = DCB(Data[Enum_CommandContent + 2]);
    
    SysTime.week    = DCB(Data[Enum_CommandContent + 3]);
    
    SysTime.hour    = DCB(Data[Enum_CommandContent + 4]);
    
    SysTime.minute  = DCB(Data[Enum_CommandContent + 5]);
    
    SysTime.second  = DCB(Data[Enum_CommandContent + 6]);
	
	// 心跳应答的钩子函数
	//
	HookFunction_HeartbeatAck();
}






