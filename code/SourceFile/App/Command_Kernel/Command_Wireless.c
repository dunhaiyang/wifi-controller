#include "Command_Wireless.h"



void Wireless_DealControlData(uint8_t *command)
{
    switch (command[Enum_Wirelss_CommandNo])
    {
        case 0x04:   // ��ȡһ���ѻ�����
            ReadOneOfflineData_SendDataToPC(command);
            break;
        
        case 0x06:   // ɾ��һ���ѻ�����
            DeleteOneOfflineData_SendDataToPC(command);
            break;  
        
        case 0x08:   // ɾ��ĳ��������ѻ�����
            DeleteSomeAreaData_SendDataToPC(command);
            break;
        
        case 0x0A:   // ���ݽṹ�ָ�������״̬
            RestoreDataStructure_SendDataToPC(command);
            break;
        
        case 0x0C:   // ���к�Ѳ��������
            SerialNoWatchAndConfigure_SendDataToPC(command);
            break;
        
        case 0x0E:   // �޸��豸���к�
            ChangeDeviceSerialNo_SendDataToPC(command);
            break;
        
        case 0x10:   // ��ʼ��������
            WhiteListInit_SendDataToPC(command);
            break;
        
        case 0x12:   // �����ϴ�Ӧ��
            WhiteListUpload_SendDataToPC(command);
            break;
        
        case 0x14:   // �ֳ�����ָ��
            RealtimeControl_SendDataToPC(command);
            break;
        
        case 0x16:   // ��ȡָ����������ָ��
            ReadWhiteListPointer_SendDataToPC(command);
            break;
		
		case 0x18:	 // ��ȡ������
			ReadWhiteList_SendDataToPC(command);
			break;
        
        case 0x1A:   // ��д���ò���
            ReadWriteConfigureParameter_SendDataToPC(command);
            break;
        
        case 0x1C:   // ��ȡ���н�����ˮ
            ReadAllTradeRecord_SendDataToPC(command);
            break;
		
		case 0x1E:	 // Զ�������ĳ���
			ProgramUpdate_SendDataToPC(command);
			break;
        
        case 0x32:   // �ָ�����״̬Ӧ��
            RestoreDefaultConfigure_SendDataToPC(command);
            break;
        
        case 0x68:   // �м���ͨѶ����Ӧ��
            RepeaterTest_SendDataToPC(command);
            break;
        
        case 0x6C:   // �м�������Ӧ��
            RepeaterParameter_SendDataToPC(command);
            break;
        
        case 0x6E:   // �豸ͨѶ����Ӧ��
            DeviceTest_SendDataToPC(command);
            break;
        
        case 0xE0:   // ��ѯӦ��ʵʱ���ݣ�
        case 0xE2:   // ��ѯӦ���ѻ����ݣ�
        case 0x02:   // ����һ��ͨ��׼���豸
            OneCardDataUpload_SendDataToPC(command);
//			printf("222\r\n");
            break;
        
        case 0xF2:   // �豸����ɾ��Ӧ��
            OneCardDataUploadDelete_SendDataToPC(command);
            break;
        
        case 0xF4:   // һ��ͨ�豸����ָ��Ӧ��
            OneCardOperation_SendDataToPC(command);
            break;
        
        default:     // �Ƿ�Ӧ��
            return;
    }
	App_Hal_Api.led->setTime(YELLOW_LED, 2);											// ���Ƶ�
}



















