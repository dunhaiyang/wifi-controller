#include "Command_Heartbeat.h"


void Heartbeat_SendDataToPC(void)
{
    uint8_t i;
    uint8_t howManyDeviceList = 0;
	uint8_t DeviceListStatus = 0;
    
    // 1. ��ȡ������Ч�豸�б���豸״̬
    //
    for (i = 0; i < NormalDeviceListSum; ++i)
    {
        // �ҵ���Ч�豸�б����ݣ������������У�Ȼ���͸�PC
        //
        if (NormalDeviceList[i].deviceValidFlag)
        {
			
			// ����豸�б��״̬
			//
			if (NormalDeviceList[i].deviceOnline)
			{
				DeviceListStatus = 0x01;
			}
			else
			{
				DeviceListStatus = 0x00;
			}
			
			// �豸��������
			//
            howManyDeviceList++;
			
			// ����豸�б����Ϣ
			//
			SocketData_SendBuffer[(howManyDeviceList - 1) * 4 + 1] = NormalDeviceList[i].deviceNumber[0];
			SocketData_SendBuffer[(howManyDeviceList - 1) * 4 + 2] = NormalDeviceList[i].deviceNumber[1];
			SocketData_SendBuffer[(howManyDeviceList - 1) * 4 + 3] = NormalDeviceList[i].deviceType;
			SocketData_SendBuffer[(howManyDeviceList - 1) * 4 + 4] = DeviceListStatus;
        }
    }
    
    // 2. ��Ч�豸����
    //
    SocketData_SendBuffer[0] = howManyDeviceList;
    
    
    // 3. ��������״̬��������ʱ���룩
    //
	SocketData_SendBuffer[(howManyDeviceList - 1) * 4 + 5] = IsStartScan()? 0x31:0x32;
	SocketData_SendBuffer[(howManyDeviceList - 1) * 4 + 6] = ControlerInfo.FirstBootup;
    
    // 4. ������������ָ��(0x71��ָ��)��PC
    //
    PC_SendCommand(0x71, DeviceDataSerialNo++, SocketData_SendBuffer,  howManyDeviceList * 4 + 3);
	
	// 5. ��������Ĺ��Ӻ���
	//
	HookFunction_HeartbeatReq();
}


void Heartbeat_DealData(uint8_t *Data)
{
    // ��BCD��ת��������
    //
    SysTime.year    = DCB(Data[Enum_CommandContent + 0]);
    
    SysTime.month   = DCB(Data[Enum_CommandContent + 1]);
    
    SysTime.day     = DCB(Data[Enum_CommandContent + 2]);
    
    SysTime.week    = DCB(Data[Enum_CommandContent + 3]);
    
    SysTime.hour    = DCB(Data[Enum_CommandContent + 4]);
    
    SysTime.minute  = DCB(Data[Enum_CommandContent + 5]);
    
    SysTime.second  = DCB(Data[Enum_CommandContent + 6]);
	
	// ����Ӧ��Ĺ��Ӻ���
	//
	HookFunction_HeartbeatAck();
}






