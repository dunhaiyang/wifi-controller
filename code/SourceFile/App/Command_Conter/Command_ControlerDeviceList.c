#include "Command_ControlerDeviceList.h"


void ControlerDeviceList_DealData(uint8_t *Data)
{
    bool   tmpSuccess = 1;
    
    uint8_t i;
    
    uint8_t tmpSerialNo = Data[1];
    
    
    // ģʽ�� 0x31->��ӣ� 0x32->ɾ���� 0x33->����
    //
    uint8_t operateMode = Data[Enum_CommandContent + 0];
    
    
    // ��ȡ�豸����
    //
    uint8_t deviceQuantity = Data[Enum_CommandContent + 1];
    
    
    // ��ȡ�豸�б�����
    //
    switch (operateMode)
    {
        // ������ͨ�豸�б�ģʽ
        //
        case 0x33:
            NormalDeviceInfo_EmptyDeviceList();      // ע�⣬����û��break
        
        
        // ������ͨ�豸�б�ģʽ
        //
        case 0x31:
            // û���㹻�Ŀռ�洢�豸�б�����
            //
            if (NormalDeviceInfo_HowManySpace() < deviceQuantity)
            {
                tmpSuccess = 0;
                
                break;
            }
            // ��������豸�б�����
            //
            for (i = Enum_CommandContent + 2; deviceQuantity > 0; i += 9)
            {
                NormalDeviceInfo_AddDeviceList(Data + i);
                
                --deviceQuantity;
            }
            break;
            
        
        // ɾ����ͨ�豸�б�ģʽ
        //
        case 0x32:
            for (i = Enum_CommandContent + 2; deviceQuantity > 0; i += 9)
            {
                NormalDeviceInfo_DeleteDeviceList(Data + i);
                
                --deviceQuantity;
            }
            break;
            
            
        // �������������豸�б�ģʽ
        //
        case 0x36:
            SpecialDeviceInfo_EmptyDeviceList();
            
        
        // �������������豸�б�ģʽ
        //
        case 0x34:
			// û���㹻�Ŀռ�洢�豸�б�����
            //
            if (SpecialDeviceInfo_HowManySpace() < deviceQuantity)
            {
                tmpSuccess = 0;
                
                break;
            }
            // ��������豸�б�����
            //
            for (i = Enum_CommandContent + 2; deviceQuantity > 0; i += 9)
            {
                SpecialDeviceInfo_AddDeviceList(Data + i);
                
                --deviceQuantity;
            }
            break;
        
        // ɾ�����������豸�б�ģʽ
        //
        case 0x35:
            for (i = Enum_CommandContent + 2; deviceQuantity > 0; i += 9)
            {
                SpecialDeviceInfo_DeleteDeviceList(Data + i);
                
                --deviceQuantity;
            }
            break;
        
        default:            // ���ܴ��ڵ�ģʽ
            tmpSuccess = 0;
            break;
    }
    
    // ����Ӧ�������
    //
    if (operateMode >= 0x34)
    {
        SocketData_SendBuffer[0] = SpecialDeviceInfo_HowManySpace();
    }
    else
    {
        SocketData_SendBuffer[0] = NormalDeviceInfo_HowManySpace();
    }
    SocketData_SendBuffer[1] = tmpSuccess? 0x31:0x32;
    
    // ���͸�PC, Data�����������ݰ��������+������ˮ��+�������ݳ���+��������+���У��
    //
    PC_SendCommand(0x70, tmpSerialNo, SocketData_SendBuffer, 2);
}








