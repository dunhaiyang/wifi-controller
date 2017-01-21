#ifndef __COMMAND_NORMAL_DEVICEINFO_H_
#define __COMMAND_NORMAL_DEVICEINFO_H_


#include "APP_HAL_API.h"


// ֧�����洢���豸������
//
#define NormalDeviceListSum 40


// �豸���ݽṹ���Զ���ѯ��ʹ�ã�
//
typedef struct
{
    uint8_t deviceNumber[2];              // �豸��
    
    uint8_t deviceMainRoute[3];           // ��·��
    
    uint8_t deviceBakRoute[3];            // ����·��
	
	uint8_t deviceFailTimes;              // ��ѯʧ�ܴ������ﵽһ�����������л���·�ɺͱ���·������ѯ�豸
    
    uint8_t usingDeviceRouteNow:1;        // ʹ���豸·�ɣ�0->ʹ����·�ɣ� 1->ʹ�ñ���·��
	
	uint8_t deviceOnline:1;				  // �豸��������
    
    uint8_t deviceValidFlag:1;            // ��ѯ��Ч��־, 0->��ʾ��Ч��1->��ʾ��Ч
    
    uint8_t deviceType:5;                 // �豸����: �����Ž�Ϊ23���
    
}NormalDeviceInfo_Typedef;



// �豸�б�, �豸�б�Ԫ������
//
extern  NormalDeviceInfo_Typedef   NormalDeviceList[NormalDeviceListSum];


// �Ѿ��洢�˶����豸�б�
//
extern  uint8_t   NormalDeviceListUsage;


// �豸���ݵ���ˮ��
//
extern  uint8_t   DeviceDataSerialNo;


// ============================================== �豸�б���ز��� ==================================================
// =================================================================================================================


// ��ʼ���豸�б�
//
void NormalDeviceInfo_Init();


// ����ָ������, ����-1��ʾ�Ҳ���������ֵ��־�ҵ����±�
//
int8_t NormalDeviceInfo_FindDeviceList(uint8_t deviceNoL, uint8_t deviceNoH, uint8_t deviceType);


// ��ѯ�����Դ洢���ٸ��豸�б�����
//
#define NormalDeviceInfo_HowManySpace() (NormalDeviceListSum - NormalDeviceListUsage)


// �����豸�б�
//
bool NormalDeviceInfo_AddDeviceList(uint8_t *deviceListAddress);


// ɾ���豸�б����豸
//
bool NormalDeviceInfo_DeleteDeviceList(uint8_t *deviceListAddress);


// ����豸�б�
//
bool NormalDeviceInfo_EmptyDeviceList();


//��ӡȫ���豸�б��������ڵ���
//
void NormalDeviceInfo_TravelDeviceList();



#endif