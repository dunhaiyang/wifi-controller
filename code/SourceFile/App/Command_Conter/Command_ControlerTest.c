#include "Command_ControlerTest.h"



// ������ͨѶ��������Ӧ��, Data��PC���͵Ĳ������ݰ�
//
void ControlerTest_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpSerialNo = Data[1];
    
    // ׼��Ӧ�������
    //
    SocketData_SendBuffer[0] = Data[Enum_CommandContent + 0];
    SocketData_SendBuffer[1] = Data[Enum_CommandContent + 1];
    
    // ���Ϳ��������������PC
    //
    PC_SendCommand(0x66, tmpSerialNo, SocketData_SendBuffer, 2);
}
