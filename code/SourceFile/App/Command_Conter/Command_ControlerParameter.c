#include "Command_ControlerParameter.h"


// ��������������
//
void ControlerParameter_DealData(uint8_t *Data)
{
    uint8_t tmpSerialNo = Data[1];
    
    uint8_t tmpChangeChannel = Data[Enum_CommandContent + 0];
    
    uint8_t tmpChannel = Data[Enum_CommandContent + 1];
    
    uint8_t tmpChangePoolInterval = Data[Enum_CommandContent + 2];
    
    uint8_t tmpPoolInterval = Data[Enum_CommandContent + 3];
	
	uint8_t tmpChangeHeartbeatInterval = Data[Enum_CommandContent + 4];
	
	uint8_t tmpHeartbeatInterval = Data[Enum_CommandContent + 5];
	
	SocketData_SendBuffer[0] = 0x32; 
	SocketData_SendBuffer[2] = 0x32;
	SocketData_SendBuffer[4] = 0x32;
    
    // ----------------  �޸Ŀ��������ŵ���  ------------------------
    //
    if (0x31 == tmpChangeChannel)
    {
        App_Hal_Api.wireless->changeChannel(tmpChannel);
		
		App_Hal_Api.beep->setTime(30);
		
		SocketData_SendBuffer[0] = 0x31;
    }
    
    // ---------------  �޸Ŀ���������ѯ���  ---------------------
    //
    if (0x31 == tmpChangePoolInterval)
    {
		SocketData_SendBuffer[2] = 0x31;
    }
	
	// ---------------  �޸Ŀ��������������  ---------------------
    //
	if (0x31 == tmpChangeHeartbeatInterval)
	{
		SetHeartbeatInterval(tmpHeartbeatInterval);
		
		SetHeartbeatIntervalBak(tmpHeartbeatInterval);
		
		SocketData_SendBuffer[4] = 0x31;
	}
	
	// ���������ŵ���Ӧ������
	//
	SocketData_SendBuffer[1] = tmpChannel;
	
	// ������ѯ���Ӧ������
	//
	SocketData_SendBuffer[3] = tmpPoolInterval;
	
	// �����������Ӧ������
	//
	SocketData_SendBuffer[5] = ControlerInfo.HeartbeatInterval;
    
    // ���Ϳ�����������PC
    //
    PC_SendCommand(0x6A, tmpSerialNo, SocketData_SendBuffer, 6);
}







