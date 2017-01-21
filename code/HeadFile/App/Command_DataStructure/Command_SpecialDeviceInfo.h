#ifndef __COMMAND_SPECIALDEVICEINFO_H_
#define __COMMAND_SPECIALDEVICEINFO_H_



#include "APP_HAL_API.h"


// ֧�����洢���豸������
//
#define SpecialDeviceListSum 3


// �豸���ݽṹ���Զ���ѯ��ʹ�ã�
//
typedef struct
{
    uint8_t deviceNumber[2];              // �豸��
    
    uint8_t deviceMainRoute[3];           // ��·��
    
    uint8_t deviceValidFlag;              // �豸��Ч��־
    
}SpecialDeviceInfo_Typedef;


extern SpecialDeviceInfo_Typedef SpecialDeviceList[SpecialDeviceListSum];


// �Ѿ��洢�˶����豸�б�
//
extern  uint8_t   SpecialDeviceListUsage;



// ��ʼ���豸�б�
//
void SpecialDeviceInfo_Init();


// ����ָ������, ����-1��ʾ�Ҳ���������ֵ��־�ҵ����±�
//
int8_t SpecialDeviceInfo_FindDeviceList(uint8_t deviceNoL, uint8_t deviceNoH);


// ��ѯ�����Դ洢���ٸ��豸�б�����
//
#define SpecialDeviceInfo_HowManySpace() (SpecialDeviceListSum - SpecialDeviceListUsage)


// �����豸�б�
//
bool SpecialDeviceInfo_AddDeviceList(uint8_t *deviceListAddress);


// ɾ���豸�б����豸
//
bool SpecialDeviceInfo_DeleteDeviceList(uint8_t *deviceListAddress);


// ����豸�б�
//
bool SpecialDeviceInfo_EmptyDeviceList();







#endif
