#include "Command_Network.h"


void Network_DealControlData(uint8_t *command)
{
    // ����PC���͹�����ָ��
    //
    switch (command[Enum_CommandNo])
    {
        case 0x03:          // ��ȡһ���ѻ�����
            ReadOneOfflineData_DealData(command);
            break;
        
        case 0x05:          // ɾ��һ���ѻ�����
            DeleteOneOfflineData_DealData(command);
            break;
        
        case 0x07:          // ɾ��ĳ��������ѻ�����
            DeleteSomeAreaData_DealData(command);
            break;
        
        case 0x09:          // ���ݽṹ�ָ�������״̬
            RestoreDataStructure_DealData(command);
            break;
        
        case 0x0B:			// ���к�Ѳ��������
            SerialNoWatchAndConfigure_DealData(command);
            break;
        
        case 0x0D:          // �޸��豸���к�
            ChangeDeviceSerialNo_DealData(command);
            break;
        
        case 0x0F:          // ��ʼ��������
            WhiteListInit_DealData(command);
            break;
        
        case 0x11:          // �ϴ�������
            WhiteListUpload_DealData(command);
            break;
        
        case 0x13:          // Զ�̿���ָ��
            RealtimeControl_DealData(command);
            break;
        
        case 0x14:          // �ֳ�����ָ��
            WhiteListUpload_DealData(command);
            break;
        
        case 0x15:          // ��ȡָ����������ָ��
            ReadWhiteListPointer_DealData(command);
            break;
		
		case 0x17:			// ��ȡ������
            ReadWhiteList_DealData(command);
            break;
        
        case 0x19:          // ��д���ò���
            ReadWriteConfigureParameter_DealData(command);
            break;
        
        case 0x1B:          // ��ȡ���н�����ˮ
            ReadAllTradeRecord_DealData(command);
            break;
		
		case 0x1D:			// Զ������
			ProgramUpdate_DealData(command);
			break;
        
        case 0x31:          // �ظ�������״̬
            RestoreDefaultConfigure_DealData(command);
            break;
            break;
		
		case 0x61:			// ����IP
			SearchIp_SendDataToPC(command);
			break;
		
		case 0x63:			// �����������
			NetworkParameter_SendDataToPC(command);
			break;
        
        case 0x65:          // ������ͨѶ��������
            ControlerTest_SendDataToPC(command);
            break;
        
        case 0x67:          // �м���ͨѶ����
            RepeaterTest_DealData(command);
            break;
        
        case 0x69:          // ��������������
            ControlerParameter_DealData(command);
            break;
        
        case 0x6B:          // �м�����������
            RepeaterParameter_DealData(command);
            break;
        
        case 0x6D:          // �豸ͨѶ����
            DeviceTest_DealData(command);
            break;
        
        case 0x6F:          // ���������豸�б�����
            ControlerDeviceList_DealData(command);
            break;
        
        case 0x72:          // ����Ӧ���
            Heartbeat_DealData(command);
            break;
        
        case 0x73:          // ����������ģʽ����
            ControlerWorkMode_DealData(command);
            break;
        
        case 0xF1:          // һ��ͨ�豸����Ӧ��(PC����ɾ������)
            OneCardDataUploadDelete_DealData(command);
            break;
        
        case 0xF3:          // һ��ͨ�豸����ָ��
            OneCardOperation_DealData(command);
//			printf("333\r\n");
            break;
        
        default:            // �޷�ʶ���ָ��
            break;
    }
}











