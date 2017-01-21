#include "Command_OneCardDataUpload.h"


void OneCardDataUpload_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpDeviceNoL        = Data[Enum_Wirelss_DeviceNoL];
    
    uint8_t tmpDeviceNoH        = Data[Enum_Wirelss_DeviceNoH];
    
    uint8_t tmpCommandNo        = Data[Enum_Wirelss_CommandNo];      // ��ѯӦ��������֣�ʵʱ���� - 0xF0, �ѻ����� - 0xF1
    
    uint8_t tmpCommandSerialNo  = Data[Enum_Wirelss_CommandSerialNo];
    
    uint8_t tmpRepeater1        = Data[Enum_Wirelss_Repeater1];
    
    uint8_t tmpRepeater2        = Data[Enum_Wirelss_Repeater2];
    
    uint8_t  tmpRepeater3        = Data[Enum_Wirelss_Repeater3];
    
    uint8_t tmpTradeType        = Data[Enum_Wirelss_DataStart];
    
    int8_t  findDeviceList      = -1;                                // ��ʼ��δ����ʧ��
    
    
    // 1.����豸��ѯӦ�����������(û�����ݵ������������ʵʱ���ݣ� ���ҽ���������88; �����Ǳ�׼���ѻ�����(��������)�����ҿ�ʼ�����ַ�ͽ��������ַһ��),��ô���ϱ���PC
    //
    if ( !((0xE0 == tmpCommandNo && 0x88 == tmpTradeType) || 
		 (0x02 == tmpCommandNo && 22 != DevicePool_DeviceType && !memcmp(Data + 12, Data + 15, 3) && Data[9] == 0)) )
    {
        // �豸���
        //
        SocketData_SendBuffer[0] = tmpDeviceNoL;
        
        SocketData_SendBuffer[1] = tmpDeviceNoH;
        
        // �豸����
        //
        SocketData_SendBuffer[2] = DevicePool_DeviceType;
        
        // �м�123
        //
        SocketData_SendBuffer[3] = tmpRepeater1;
        
        SocketData_SendBuffer[4] = tmpRepeater2;
        
        SocketData_SendBuffer[5] = tmpRepeater3;
        
        // ��������(0xE0:ʵʱ���ݣ� 0xE2���ѻ�����)
        //
        if (0xE0 == tmpCommandNo)                       // ʵʱ����
        {
            SocketData_SendBuffer[6] = 0x31;
        }
        else if (0xE2 == tmpCommandNo)                  // �ѻ�����
        {
            
            SocketData_SendBuffer[6] = 0x32;
        }
        else if (0x02 == tmpCommandNo)                  // ��׼����ѻ�����
        {
            SocketData_SendBuffer[6] = 0x33;
        }
        else
        {
            SocketData_SendBuffer[6] = 0x34;
        }
        
        // ������Ҫ����(22�ֽ�)
        //
        memcpy(SocketData_SendBuffer + 7, Data + Enum_Wirelss_DataStart, 22);
        
            
        // ���������ϱ�����PC
        //
        PC_SendCommand(0xF0, tmpCommandSerialNo, SocketData_SendBuffer,  29);
    }
    
    
    // 2. �����豸����������Դ���ͨ�豸��ʵʱ���ѻ��ȣ��������豸������������
    //
    // �����豸
    //
    if (22 == DevicePool_DeviceType)
    {
        findDeviceList = SpecialDeviceInfo_FindDeviceList(tmpDeviceNoL, tmpDeviceNoH);
        
        if (findDeviceList != -1)
        {
            // ��ѯӦ��ɹ���ɾ�������豸�б���豸
            //
            SpecialDeviceList[findDeviceList].deviceValidFlag = 0;
			
			if (SpecialDeviceListUsage > 0)
			{
				SpecialDeviceListUsage--;
			}
        }
    }
    // ��ͨ�豸
    //
    else
    {
        // 3.�����豸�б����豸·��������Ϣ
        //
        findDeviceList = NormalDeviceInfo_FindDeviceList(tmpDeviceNoL, tmpDeviceNoH, DevicePool_DeviceType);
    
        if (findDeviceList != -1)
        {
            // ��ѯӦ��ɹ�����ô��ѯʧ�ܴ�������
            //
            NormalDeviceList[findDeviceList].deviceFailTimes = 0;
                
            // �����豸�������豸״̬Ϊ����
            //
            NormalDeviceList[findDeviceList].deviceOnline = 1;
        }
    }
}





