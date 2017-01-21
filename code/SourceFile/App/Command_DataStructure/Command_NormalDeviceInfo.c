#include "Command_NormalDeviceInfo.h"



// �豸�б�, �豸�б�Ԫ������
//
NormalDeviceInfo_Typedef NormalDeviceList[NormalDeviceListSum];



// �Ѿ��洢�˶����豸�б�
//
uint8_t   NormalDeviceListUsage = 0;


// �豸���ݵ���ˮ��
//
uint8_t    DeviceDataSerialNo = 0;


// ============================================== �豸�б���ز��� ==================================================
// =================================================================================================================


// ��ʼ���豸�б�
//
void NormalDeviceInfo_Init(void)
{
    uint8_t index;
    
    for (index = 0; index < NormalDeviceListSum; ++index)
    {
        // ����Ϊ��Ч��ʧ�ܴ���Ϊ0�� ״̬Ϊ������ ʹ����·��, û�еȴ���ѯ�豸Ӧ��
        //
        NormalDeviceList[index].deviceValidFlag = 0;
        
        NormalDeviceList[index].deviceFailTimes = 0;
			
		NormalDeviceList[index].deviceOnline = 0;
        
        NormalDeviceList[index].usingDeviceRouteNow = 0;
    }
    
    NormalDeviceListUsage = 0;
}


// ����ָ������, ����-1��ʾ�Ҳ���������ֵ��־�ҵ����±�
//
int8_t NormalDeviceInfo_FindDeviceList(uint8_t deviceNoL, uint8_t deviceNoH, uint8_t deviceType)
{
    uint8_t index;
    
    for (index = 0; index < NormalDeviceListSum; index++)
    {
        if (NormalDeviceList[index].deviceValidFlag
            && NormalDeviceList[index].deviceNumber[0] == deviceNoL
            && NormalDeviceList[index].deviceNumber[1] == deviceNoH
            && NormalDeviceList[index].deviceType == deviceType)
        {
            return index;
        }
    }
    
    return -1;
}



// �����豸�б�
//
bool NormalDeviceInfo_AddDeviceList(uint8_t *deviceListAddress)
{
    int8_t  retValue;
    uint8_t index;
    
    // ��ѯ�Ƿ��Ѿ�����
    //
    retValue = NormalDeviceInfo_FindDeviceList(deviceListAddress[0], deviceListAddress[1], deviceListAddress[2]);
    
    // ֮ǰ�Ѿ���ӹ��ˣ�ֱ�ӷ�����
    //
    if (retValue != -1)
    {
        return 1;
    }
    
    // �ҵ�һ�����еط�����
    //
    for (index = 0; index < NormalDeviceListSum; index++)
    {
        if (!NormalDeviceList[index].deviceValidFlag)
        {
            NormalDeviceList[index].deviceNumber[0] = deviceListAddress[0];
            
            NormalDeviceList[index].deviceNumber[1] = deviceListAddress[1];
            
            NormalDeviceList[index].deviceType = deviceListAddress[2];
            
            memcpy(NormalDeviceList[index].deviceMainRoute, deviceListAddress + 3, 3);
            
            memcpy(NormalDeviceList[index].deviceBakRoute, deviceListAddress + 6, 3);
            
            NormalDeviceList[index].deviceValidFlag = 1;
			
			NormalDeviceList[index].deviceOnline = 0;
            
            NormalDeviceListUsage++;
            
            return 1;
        }
    }
    
    return 0;
}


// ɾ���豸�б�
//
bool NormalDeviceInfo_DeleteDeviceList(uint8_t *deviceListAddress)
{
    int8_t retValue;
    
    retValue = NormalDeviceInfo_FindDeviceList(deviceListAddress[0], deviceListAddress[1], deviceListAddress[2]);
    
    if (retValue != -1)
    {
        NormalDeviceList[retValue].deviceValidFlag = 0;
        
        NormalDeviceListUsage--;
    }
    
    return 1;
}


// ����豸�б�
//
bool NormalDeviceInfo_EmptyDeviceList(void)
{
    uint8_t index;
    
    for (index = 0; index < NormalDeviceListSum; index++)
    {
        NormalDeviceList[index].deviceValidFlag = 0;
    }
    
    NormalDeviceListUsage = 0;
    
    return 1;
}



void NormalDeviceInfo_TravelDeviceList(void)
{
    static uint8_t index;
    
    for (index = 0; index < NormalDeviceListSum; index++)
    {
        if (NormalDeviceList[index].deviceValidFlag)
        {
			App_Hal_Api.console->printDec("index:\t", 	index);
			App_Hal_Api.console->printDec("\tdevno:\t", 	NormalDeviceList[index].deviceNumber[0] | NormalDeviceList[index].deviceNumber[1] << 8);
			App_Hal_Api.console->printDecLn("\ttype:\t",	NormalDeviceList[index].deviceType);
			App_Hal_Api.console->printDec("mr0:\t",		NormalDeviceList[index].deviceMainRoute[0]);
			App_Hal_Api.console->printDec("\tmr1:\t",		NormalDeviceList[index].deviceMainRoute[0]);
			App_Hal_Api.console->printDecLn("\tmr2:\t",	NormalDeviceList[index].deviceMainRoute[0]);
			App_Hal_Api.console->printDec("br0:\t",		NormalDeviceList[index].deviceBakRoute[0]);
			App_Hal_Api.console->printDec("\tbr1:\t",		NormalDeviceList[index].deviceBakRoute[0]);
			App_Hal_Api.console->printDecLn("\tbr2:\t",	NormalDeviceList[index].deviceBakRoute[0]);
        }
    }
}







