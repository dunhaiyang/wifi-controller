#include "Command_ControlerTest.h"



// 控制器通讯测试命令应答, Data是PC发送的测试数据包
//
void ControlerTest_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpSerialNo = Data[1];
    
    // 准备应答包数据
    //
    SocketData_SendBuffer[0] = Data[Enum_CommandContent + 0];
    SocketData_SendBuffer[1] = Data[Enum_CommandContent + 1];
    
    // 发送控制器测试命令给PC
    //
    PC_SendCommand(0x66, tmpSerialNo, SocketData_SendBuffer, 2);
}
