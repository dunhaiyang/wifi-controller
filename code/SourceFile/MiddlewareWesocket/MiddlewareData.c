#include "MiddlewareData.h"


// ====================  ����1��0�����λ  ===============================
//
//char code MiddlewareData_Matrix8_0[256] = {
//	
//	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, 	/* 0x00 to 0x0F                  */
//	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 5, 	/* 0x10 to 0x1F                  */
//	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, 	/* 0x20 to 0x2F                  */
//	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 6, 	/* 0x30 to 0x3F                  */
//	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, 	/* 0x40 to 0x4F                  */
//	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 5, 	/* 0x50 to 0x5F                  */
//	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, 	/* 0x60 to 0x6F                  */
//	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 7, 	/* 0x70 to 0x7F                  */
//	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, 	/* 0x80 to 0x8F                  */
//	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 5, 	/* 0x90 to 0x9F                  */
//	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, 	/* 0xA0 to 0xAF                  */
//	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 6, 	/* 0xB0 to 0xBF                  */
//	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, 	/* 0xC0 to 0xCF                  */
//	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 5, 	/* 0xD0 to 0xDF                  */
//	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, 	/* 0xE0 to 0xEF                  */
//	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, -1 	/* 0xF0 to 0xFF                  */
//};


//char code MiddlewareData_Matrix8_1[256] = {
//	
//   -1, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 	/* 0x00 to 0x0F                   */
//    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 	/* 0x10 to 0x1F                   */
//    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 	/* 0x20 to 0x2F                   */
//    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 	/* 0x30 to 0x3F                   */
//    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 	/* 0x40 to 0x4F                   */
//    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 	/* 0x50 to 0x5F                   */
//    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 	/* 0x60 to 0x6F                   */
//    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 	/* 0x70 to 0x7F                   */
//    7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 	/* 0x80 to 0x8F                   */
//    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 	/* 0x90 to 0x9F                   */
//    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 	/* 0xA0 to 0xAF                   */
//    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 	/* 0xB0 to 0xBF                   */
//    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 	/* 0xC0 to 0xCF                   */
//    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 	/* 0xD0 to 0xDF                   */
//    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 	/* 0xE0 to 0xEF                   */
//    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0  	/* 0xF0 to 0xFF                   */
//};


char code MiddlewareData_Matrix4_0[16] = {
	
	0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, -1,	/* 0x00 to 0x0F					   */

};


int8_t code	MiddlewareData_Matrix4_1[16] = {
	
	-1, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,	/* 0x00 to 0x0F					   */ 
	
};


MiddlewareData_t	middlewareData;


// ��ʼ����̬�ڴ����
//
void MiddlewareData_Init(void)
{
	MiddlewareData_Emtpy_PoolData();				// �����ѯ����
	
	MiddlewareData_Empty_SendDataNormal();			// �����ͨ��������
	
	MiddlewareData_Empty_ReceiveDataNormal();		// �����ͨ��������
	
	MiddlewareData_Empty_SendDataUrgency();			// ��ս�����������
	
	MiddlewareData_Empty_ReceiveDataUrgency();		// ��ս�����������
}


// �����ڴ�
//
uint8_t *MiddlewareData_Malloc(MiddlewareData_Enum type)
{
	uint8_t *tmpBuffer = 0;
	
	switch (type)
	{
		case MiddlewareData_PollData:				// ��ѯ
			if (MiddlewareData_poolDataFlag != 0x0F)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_poolData + MiddlewareData_Matrix4_0[MiddlewareData_poolDataFlag]);
				MiddlewareData_poolDataFlag |= 1 << MiddlewareData_Matrix4_0[MiddlewareData_poolDataFlag];
			}
			break;
		
		case MiddlewareData_SendDataNormal:			// ��������
			if (MiddlewareData_normalSendDataFlag != 0x0F)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_normalSendData + MiddlewareData_Matrix4_0[MiddlewareData_normalSendDataFlag]);
				MiddlewareData_normalSendDataFlag |= 1 << MiddlewareData_Matrix4_0[MiddlewareData_normalSendDataFlag];
			}
			break;
	
		case MiddlewareData_ReceiveDataNormal:		// ��������
			if (MiddlewareData_normalReceiveDataFlag != 0x0F)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_normalReceiveData + MiddlewareData_Matrix4_0[MiddlewareData_normalReceiveDataFlag]);
				MiddlewareData_normalReceiveDataFlag |= 1 << MiddlewareData_Matrix4_0[MiddlewareData_normalReceiveDataFlag];
			}
			break;
		
		case MiddlewareData_SendDataUrgency:		// ���ͽ�������
			if (MiddlewareData_urgencySendDataFlag != 0x0F)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_urgencySendData + MiddlewareData_Matrix4_0[MiddlewareData_urgencySendDataFlag]);
				MiddlewareData_urgencySendDataFlag |= 1 << MiddlewareData_Matrix4_0[MiddlewareData_urgencySendDataFlag];
			}
			break;
			
		case MiddlewareData_ReceiveDataUrgency:		// ���ս�������
			if (MiddlewareData_urgencyReceiveDataFlag != 0x0F)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_urgencyReceiveData + MiddlewareData_Matrix4_0[MiddlewareData_urgencyReceiveDataFlag]);
				MiddlewareData_urgencyReceiveDataFlag |= 1 << MiddlewareData_Matrix4_0[MiddlewareData_urgencyReceiveDataFlag];
			}
			break;
			
		default:									// ����
			break;
	}
	return tmpBuffer;
}


// Ϊ��
//
bool MiddlewareData_IsEmpty(MiddlewareData_Enum type)
{
	switch (type)
	{
		case MiddlewareData_PollData:				// ��ѯ
			return (MiddlewareData_poolDataFlag == 0);
		
		case MiddlewareData_SendDataNormal:			// ��������
			return (MiddlewareData_normalSendDataFlag == 0);
	
		case MiddlewareData_ReceiveDataNormal:		// ��������
			return (MiddlewareData_normalReceiveDataFlag == 0);
		
		case MiddlewareData_SendDataUrgency:		// ���ͽ�������
			return (MiddlewareData_urgencySendDataFlag == 0);
			
		case MiddlewareData_ReceiveDataUrgency:		// ���ս�������
			return (MiddlewareData_urgencyReceiveDataFlag == 0);
			
		default:									// ����
			break;
	}
	return 1;
}


// ��ȡ����
//
uint8_t *MiddlewareData_Fetch(MiddlewareData_Enum type)
{
	uint8_t *tmpBuffer = 0;
	
	switch (type)
	{
		case MiddlewareData_PollData:				// ��ѯ
			if (MiddlewareData_poolDataFlag)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_poolData + MiddlewareData_Matrix4_1[MiddlewareData_poolDataFlag]);
			}
			break;
		
		case MiddlewareData_SendDataNormal:			// ��������
			if (MiddlewareData_normalSendDataFlag)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_normalSendData + MiddlewareData_Matrix4_1[MiddlewareData_normalSendDataFlag]);
			}
			break;
	
		case MiddlewareData_ReceiveDataNormal:		// ��������
			if (MiddlewareData_normalReceiveDataFlag)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_normalReceiveData + MiddlewareData_Matrix4_1[MiddlewareData_normalReceiveDataFlag]);
			}
			break;
		
		case MiddlewareData_SendDataUrgency:		// ���ͽ�������
			if (MiddlewareData_urgencySendDataFlag)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_urgencySendData + MiddlewareData_Matrix4_1[MiddlewareData_urgencySendDataFlag]);
			}
			break;
			
		case MiddlewareData_ReceiveDataUrgency:		// ���ս�������
			if (MiddlewareData_urgencyReceiveDataFlag)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_urgencyReceiveData + MiddlewareData_Matrix4_1[MiddlewareData_urgencyReceiveDataFlag]);
			}
			break;
			
		default:									// ����
			break;
	}
	return tmpBuffer;
}


// �ͷ��ڴ�
//
void MiddlewareData_Free(MiddlewareData_Enum type)
{
	switch (type)
	{
		case MiddlewareData_PollData:			// ��ѯ
			if (MiddlewareData_poolDataFlag)
			{
				MiddlewareData_poolDataFlag &= ~(1 << MiddlewareData_Matrix4_1[MiddlewareData_poolDataFlag]);
			}
			break;
		
		case MiddlewareData_SendDataNormal:			// ��������
			if (MiddlewareData_normalSendDataFlag)
			{
				MiddlewareData_normalSendDataFlag &= ~(1 << MiddlewareData_Matrix4_1[MiddlewareData_normalSendDataFlag]);
			}
			break;
	
		case MiddlewareData_ReceiveDataNormal:		// ��������
			if (MiddlewareData_normalReceiveDataFlag)
			{
				MiddlewareData_normalReceiveDataFlag &= ~(1 << MiddlewareData_Matrix4_1[MiddlewareData_normalReceiveDataFlag]);
			}
			break;
		
		case MiddlewareData_SendDataUrgency:	// ���ͽ�������
			if (MiddlewareData_urgencySendDataFlag)
			{
				MiddlewareData_urgencySendDataFlag &= ~(1 << MiddlewareData_Matrix4_1[MiddlewareData_urgencySendDataFlag]);
			}
			break;
			
		case MiddlewareData_ReceiveDataUrgency:	// ���ս�������
			if (MiddlewareData_urgencyReceiveDataFlag)
			{
				MiddlewareData_urgencyReceiveDataFlag &= ~(1 << MiddlewareData_Matrix4_1[MiddlewareData_urgencyReceiveDataFlag]);
			}
			break;
			
		default:								// ����
			break;
	}
}

