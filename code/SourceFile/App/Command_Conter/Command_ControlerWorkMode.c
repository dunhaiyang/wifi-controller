#include "Command_ControlerWorkMode.h"


void ControlerWorkMode_DealData(uint8_t *Data)
{
    bool tmpError = 0;
    
    uint8_t tmpSerialNo         = Data[1];
    
    uint8_t tmpOperationMode    = Data[3];
    
    // ���ù���ģʽΪ��ʼ��ѯ
    //
    if (0x31 == tmpOperationMode)
    {
        SetStartScan(1);
    }
	// ���ù���ģʽΪֹͣ��ѯ
	//
    else if (0x32 == tmpOperationMode)
    {
        SetStartScan(0);
    }
	// �����ָ������κβ���
	//
    else
    {
        tmpError = 1;
    }
    
    // ������������ʱ����
    //
    SysTime.year    = DCB(Data[Enum_CommandContent + 1]);
    
    SysTime.month   = DCB(Data[Enum_CommandContent + 2]);
    
    SysTime.day     = DCB(Data[Enum_CommandContent + 3]);
    
    SysTime.week    = DCB(Data[Enum_CommandContent + 4]);
    
    SysTime.hour    = DCB(Data[Enum_CommandContent + 5]);
    
    SysTime.minute  = DCB(Data[Enum_CommandContent + 6]);
    
    SysTime.second  = DCB(Data[Enum_CommandContent + 7]);
    
    
    // ����Ӧ�������
    //
    SocketData_SendBuffer[0] = Data[Enum_CommandContent + 0];
    SocketData_SendBuffer[1] = tmpError? 0x32:0x31;
    
    
    // ���Ϳ���������ģʽ����Ӧ�����0x74����PC
    //
    PC_SendCommand(0x74, tmpSerialNo, SocketData_SendBuffer, 2);
	
	// ����ģʽ�Ĺ��Ӻ���
	//
	HookFunction_ControlerWorkMode();
}





