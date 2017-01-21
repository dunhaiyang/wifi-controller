#include "MiddlewareData.h"


// ====================  查找1或0的最低位  ===============================
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


// 初始化动态内存机制
//
void MiddlewareData_Init(void)
{
	MiddlewareData_Emtpy_PoolData();				// 清空轮询数据
	
	MiddlewareData_Empty_SendDataNormal();			// 清空普通发送数据
	
	MiddlewareData_Empty_ReceiveDataNormal();		// 清空普通接收数据
	
	MiddlewareData_Empty_SendDataUrgency();			// 清空紧急发送数据
	
	MiddlewareData_Empty_ReceiveDataUrgency();		// 清空紧急接收数据
}


// 分配内存
//
uint8_t *MiddlewareData_Malloc(MiddlewareData_Enum type)
{
	uint8_t *tmpBuffer = 0;
	
	switch (type)
	{
		case MiddlewareData_PollData:				// 轮询
			if (MiddlewareData_poolDataFlag != 0x0F)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_poolData + MiddlewareData_Matrix4_0[MiddlewareData_poolDataFlag]);
				MiddlewareData_poolDataFlag |= 1 << MiddlewareData_Matrix4_0[MiddlewareData_poolDataFlag];
			}
			break;
		
		case MiddlewareData_SendDataNormal:			// 发送数据
			if (MiddlewareData_normalSendDataFlag != 0x0F)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_normalSendData + MiddlewareData_Matrix4_0[MiddlewareData_normalSendDataFlag]);
				MiddlewareData_normalSendDataFlag |= 1 << MiddlewareData_Matrix4_0[MiddlewareData_normalSendDataFlag];
			}
			break;
	
		case MiddlewareData_ReceiveDataNormal:		// 接收数据
			if (MiddlewareData_normalReceiveDataFlag != 0x0F)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_normalReceiveData + MiddlewareData_Matrix4_0[MiddlewareData_normalReceiveDataFlag]);
				MiddlewareData_normalReceiveDataFlag |= 1 << MiddlewareData_Matrix4_0[MiddlewareData_normalReceiveDataFlag];
			}
			break;
		
		case MiddlewareData_SendDataUrgency:		// 发送紧急数据
			if (MiddlewareData_urgencySendDataFlag != 0x0F)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_urgencySendData + MiddlewareData_Matrix4_0[MiddlewareData_urgencySendDataFlag]);
				MiddlewareData_urgencySendDataFlag |= 1 << MiddlewareData_Matrix4_0[MiddlewareData_urgencySendDataFlag];
			}
			break;
			
		case MiddlewareData_ReceiveDataUrgency:		// 接收紧急数据
			if (MiddlewareData_urgencyReceiveDataFlag != 0x0F)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_urgencyReceiveData + MiddlewareData_Matrix4_0[MiddlewareData_urgencyReceiveDataFlag]);
				MiddlewareData_urgencyReceiveDataFlag |= 1 << MiddlewareData_Matrix4_0[MiddlewareData_urgencyReceiveDataFlag];
			}
			break;
			
		default:									// 错误
			break;
	}
	return tmpBuffer;
}


// 为空
//
bool MiddlewareData_IsEmpty(MiddlewareData_Enum type)
{
	switch (type)
	{
		case MiddlewareData_PollData:				// 轮询
			return (MiddlewareData_poolDataFlag == 0);
		
		case MiddlewareData_SendDataNormal:			// 发送数据
			return (MiddlewareData_normalSendDataFlag == 0);
	
		case MiddlewareData_ReceiveDataNormal:		// 接收数据
			return (MiddlewareData_normalReceiveDataFlag == 0);
		
		case MiddlewareData_SendDataUrgency:		// 发送紧急数据
			return (MiddlewareData_urgencySendDataFlag == 0);
			
		case MiddlewareData_ReceiveDataUrgency:		// 接收紧急数据
			return (MiddlewareData_urgencyReceiveDataFlag == 0);
			
		default:									// 错误
			break;
	}
	return 1;
}


// 获取数据
//
uint8_t *MiddlewareData_Fetch(MiddlewareData_Enum type)
{
	uint8_t *tmpBuffer = 0;
	
	switch (type)
	{
		case MiddlewareData_PollData:				// 轮询
			if (MiddlewareData_poolDataFlag)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_poolData + MiddlewareData_Matrix4_1[MiddlewareData_poolDataFlag]);
			}
			break;
		
		case MiddlewareData_SendDataNormal:			// 发送数据
			if (MiddlewareData_normalSendDataFlag)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_normalSendData + MiddlewareData_Matrix4_1[MiddlewareData_normalSendDataFlag]);
			}
			break;
	
		case MiddlewareData_ReceiveDataNormal:		// 接收数据
			if (MiddlewareData_normalReceiveDataFlag)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_normalReceiveData + MiddlewareData_Matrix4_1[MiddlewareData_normalReceiveDataFlag]);
			}
			break;
		
		case MiddlewareData_SendDataUrgency:		// 发送紧急数据
			if (MiddlewareData_urgencySendDataFlag)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_urgencySendData + MiddlewareData_Matrix4_1[MiddlewareData_urgencySendDataFlag]);
			}
			break;
			
		case MiddlewareData_ReceiveDataUrgency:		// 接收紧急数据
			if (MiddlewareData_urgencyReceiveDataFlag)
			{
				tmpBuffer = (uint8_t *)(MiddlewareData_urgencyReceiveData + MiddlewareData_Matrix4_1[MiddlewareData_urgencyReceiveDataFlag]);
			}
			break;
			
		default:									// 错误
			break;
	}
	return tmpBuffer;
}


// 释放内存
//
void MiddlewareData_Free(MiddlewareData_Enum type)
{
	switch (type)
	{
		case MiddlewareData_PollData:			// 轮询
			if (MiddlewareData_poolDataFlag)
			{
				MiddlewareData_poolDataFlag &= ~(1 << MiddlewareData_Matrix4_1[MiddlewareData_poolDataFlag]);
			}
			break;
		
		case MiddlewareData_SendDataNormal:			// 发送数据
			if (MiddlewareData_normalSendDataFlag)
			{
				MiddlewareData_normalSendDataFlag &= ~(1 << MiddlewareData_Matrix4_1[MiddlewareData_normalSendDataFlag]);
			}
			break;
	
		case MiddlewareData_ReceiveDataNormal:		// 接收数据
			if (MiddlewareData_normalReceiveDataFlag)
			{
				MiddlewareData_normalReceiveDataFlag &= ~(1 << MiddlewareData_Matrix4_1[MiddlewareData_normalReceiveDataFlag]);
			}
			break;
		
		case MiddlewareData_SendDataUrgency:	// 发送紧急数据
			if (MiddlewareData_urgencySendDataFlag)
			{
				MiddlewareData_urgencySendDataFlag &= ~(1 << MiddlewareData_Matrix4_1[MiddlewareData_urgencySendDataFlag]);
			}
			break;
			
		case MiddlewareData_ReceiveDataUrgency:	// 接收紧急数据
			if (MiddlewareData_urgencyReceiveDataFlag)
			{
				MiddlewareData_urgencyReceiveDataFlag &= ~(1 << MiddlewareData_Matrix4_1[MiddlewareData_urgencyReceiveDataFlag]);
			}
			break;
			
		default:								// 错误
			break;
	}
}

