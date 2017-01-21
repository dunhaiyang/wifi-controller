#include "Command_ControlerWorkMode.h"


void ControlerWorkMode_DealData(uint8_t *Data)
{
    bool tmpError = 0;
    
    uint8_t tmpSerialNo         = Data[1];
    
    uint8_t tmpOperationMode    = Data[3];
    
    // 设置工作模式为开始轮询
    //
    if (0x31 == tmpOperationMode)
    {
        SetStartScan(1);
    }
	// 设置工作模式为停止轮询
	//
    else if (0x32 == tmpOperationMode)
    {
        SetStartScan(0);
    }
	// 错误的指令，不错任何操作
	//
    else
    {
        tmpError = 1;
    }
    
    // 设置年月日周时分秒
    //
    SysTime.year    = DCB(Data[Enum_CommandContent + 1]);
    
    SysTime.month   = DCB(Data[Enum_CommandContent + 2]);
    
    SysTime.day     = DCB(Data[Enum_CommandContent + 3]);
    
    SysTime.week    = DCB(Data[Enum_CommandContent + 4]);
    
    SysTime.hour    = DCB(Data[Enum_CommandContent + 5]);
    
    SysTime.minute  = DCB(Data[Enum_CommandContent + 6]);
    
    SysTime.second  = DCB(Data[Enum_CommandContent + 7]);
    
    
    // 设置应答包数据
    //
    SocketData_SendBuffer[0] = Data[Enum_CommandContent + 0];
    SocketData_SendBuffer[1] = tmpError? 0x32:0x31;
    
    
    // 发送控制器工作模式控制应答包（0x74）给PC
    //
    PC_SendCommand(0x74, tmpSerialNo, SocketData_SendBuffer, 2);
	
	// 工作模式的钩子函数
	//
	HookFunction_ControlerWorkMode();
}





