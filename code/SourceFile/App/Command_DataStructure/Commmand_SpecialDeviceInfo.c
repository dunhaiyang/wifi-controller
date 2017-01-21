#include "Command_SpecialDeviceInfo.h"


// �豸�б�, �豸�б�Ԫ������
//
SpecialDeviceInfo_Typedef SpecialDeviceList[SpecialDeviceListSum];


// �Ѿ��洢�˶����豸�б�
//
uint8_t   SpecialDeviceListUsage = 0;



// ��ʼ���豸�б�
//
void SpecialDeviceInfo_Init(void)
{
    uint8_t index;
    
    for (index = 0; index < SpecialDeviceListSum; ++index)
    {
        SpecialDeviceList[index].deviceValidFlag = 0;
    }
}


// ����ָ������, ����-1��ʾ�Ҳ���������ֵ��־�ҵ����±�
//
int8_t SpecialDeviceInfo_FindDeviceList(uint8_t deviceNoL, uint8_t deviceNoH)
{
    uint8_t index;
    
    for (index = 0; index < SpecialDeviceListSum; index++)
    {
        if (SpecialDeviceList[index].deviceValidFlag &&
            SpecialDeviceList[index].deviceNumber[0] == deviceNoL && 
            SpecialDeviceList[index].deviceNumber[1] == deviceNoH)
        {
            return index;
        }
    }
    
    return -1;
}


// �����豸�б�
//
bool SpecialDeviceInfo_AddDeviceList(uint8_t *deviceListAddress)
{
    int8_t retVal;
    
    uint8_t index;
    
    retVal = SpecialDeviceInfo_FindDeviceList(deviceListAddress[0], deviceListAddress[1]);
    
    if (retVal != -1)
    {
        return 0;
    }

    for (index = 0; index < SpecialDeviceListSum; ++index)
    {
        // ��ʽ�����豸�б�����
        //
        if (!SpecialDeviceList[index].deviceValidFlag)
        {
            SpecialDeviceList[index].deviceNumber[0] = deviceListAddress[0];
            SpecialDeviceList[index].deviceNumber[1] = deviceListAddress[1];
            
            SpecialDeviceList[index].deviceMainRoute[0] = deviceListAddress[3];
            SpecialDeviceList[index].deviceMainRoute[1] = deviceListAddress[4];
            SpecialDeviceList[index].deviceMainRoute[2] = deviceListAddress[5];
            SpecialDeviceList[index].deviceValidFlag = 1;
            
            SpecialDeviceListUsage++;
            
            return 1;
        }
    }

    return 0;
}


// ɾ���豸�б����豸
//
bool SpecialDeviceInfo_DeleteDeviceList(uint8_t *deviceListAddress)
{
    int8_t retVal;
    
    retVal = SpecialDeviceInfo_FindDeviceList(deviceListAddress[0], deviceListAddress[1]);
    
    if (retVal != -1)
    {
        SpecialDeviceList[retVal].deviceValidFlag = 0;
        
        SpecialDeviceListUsage--;
    }
    
    return 1;
}


// ����豸�б�
//
bool SpecialDeviceInfo_EmptyDeviceList()
{
    uint8_t index;

    for (index = 0; index < SpecialDeviceListSum; ++index)
    {
        // ��ʽ�����豸�б�����
        //
        SpecialDeviceList[index].deviceValidFlag = 0;
    }
    
    SpecialDeviceListUsage = 0;
    
    return 1;
}















