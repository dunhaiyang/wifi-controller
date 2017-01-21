#include "Middleware_ControllerPollDevice.h"


void __SendPollDataToDevice(uint8_t index)
{
	uint16_t   tmpParityValue = 0;
    
	// 每次发送轮询，设备增加失败次数，有应答则清除
	//
//    DeviceInfo_Set_FailTimes(index);
    
    // 设备编号
    //
//    NRF905_SendBuffer[0] = DeviceList[index].deviceNo;
//    
//    NRF905_SendBuffer[1] = DeviceList[index].deviceNo >> 8;
    
    // 命令编号
    //
    NRF905_SendBuffer[2] = 0x01;
    
    // 命令流水
    //
    NRF905_SendBuffer[3] = 0x00;
	
    // 使用主路由
    //
//	NRF905_SendBuffer[4] = DeviceList[index].deviceMasterRouter[0];       // 目的中继
//	
//	NRF905_SendBuffer[5] = DeviceList[index].deviceMasterRouter[0];       // 中继1
//	
//	NRF905_SendBuffer[6] = DeviceList[index].deviceMasterRouter[1];       // 中继2
//	
//	NRF905_SendBuffer[7] = DeviceList[index].deviceMasterRouter[2];       // 中继3
    
    // 填充字符
    //
    NRF905_SendBuffer[8] = 0xF1;
    
    // 设备编号
    //
    NRF905_SendBuffer[9] = NRF905_SendBuffer[0];
    
    NRF905_SendBuffer[10] = NRF905_SendBuffer[1];
    
    // 设备类型
    //
//    NRF905_SendBuffer[11] = DeviceList[index].deviceType;
    
    // 无线信道
    //
//    NRF905_SendBuffer[12] = WirelessChannel;
    
    // 秒\分\时\日\星期\月\年
    //
    NRF905_SendBuffer[13] = BCD(SysTime.second);
    
    NRF905_SendBuffer[14] = BCD(SysTime.minute);
    
    NRF905_SendBuffer[15] = BCD(SysTime.hour);
    
    NRF905_SendBuffer[16] = BCD(SysTime.day);
    
    NRF905_SendBuffer[17] = BCD(SysTime.week);
    
    NRF905_SendBuffer[18] = BCD(SysTime.month);
    
    NRF905_SendBuffer[19] = BCD(SysTime.year);
    
    // 内部和校验
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer + 8, 12);
    NRF905_SendBuffer[20] = tmpParityValue;
    NRF905_SendBuffer[21] = tmpParityValue >> 8;
    
    // 填充字符0xF1
    //
    memset(NRF905_SendBuffer + 22, 0xF1, 8);
    
    // 外部和校验
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer, 30);
    NRF905_SendBuffer[30] = tmpParityValue;
    NRF905_SendBuffer[31] = tmpParityValue >> 8;
    
    // 发送轮询指令
    //
//    Wireless_SendDataToDevice(NRF905_SendBuffer);
    
	
	// 根据中继来设置无线发送等待超时时间
	//
	Pca_Start(NRF905_SendBuffer, 0);
}


// 发送轮询指令到设备，设备回应包有两种：
// 一种是直接数据（如实时消费机）， 一种是间接数据（如脱机设备， 需要进一步读取脱机数据）
//
void ControllerPollDevice_SendPollDataToDevice(void)
{
//	static uint8_t index = 0;
//	
//	for (; index < DeviceInfo_DeviceMaxNum; index++)
//	{
//		if (!DeviceList[index].canUseFlag)
//		{
//			COM_GREEN = 0;							// 亮绿灯
//			
//			__SendPollDataToDevice(index);			// 发送轮询数据
//			
//			DeviceInfo_CurrentIndex = index++;		// 保存好刚刚设备轮询的索引
//			
//			printf("poll\r\n");
//	
//			COM_GREEN = 1;							// 灭绿灯
//			
//			return;
//		}
//	}
//	index = 0;
}


// 发送间接数据, 
//
void ControllerPollDevice_ReadDirectData(void)
{
	// 处于读取脱机数据阶段
	//
//	if (OneCardDataUpload_IndirectCount--)
//	{
//		ReadOneOfflineData_DealData();
//	}
//	// 结束读取脱机数据阶段
//	//
//	else
//	{
//		OneCardDataUpload_PollDeviceStatus = 2;
//	}
}


// 恢复成轮询状态
//
void ControllerPollDevice_RecoverPollStatus(void)
{
//	if (OneCardDataUpload_RecoverCount)
//	{
//		OneCardDataUpload_RecoverCount--;
//	}
//	else
//	{
//		OneCardDataUpload_PollDeviceStatus = 0;
//	}
}


















