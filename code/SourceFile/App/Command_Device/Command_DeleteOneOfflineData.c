#include "Command_DeleteOneOfflineData.h"


uint8_t DeleteOneOfflineData_DeviceType = 0xFF;


void DeleteOneOfflineData_DealData(uint8_t *Data)
{
    uint8_t tmpCommandNo        = Data[0];
    
    uint8_t tmpCommandSerialNo  = Data[1];
    
    uint8_t tmpDeviceNoL        = Data[3];
    
    uint8_t tmpDeviceNoH        = Data[4];
    
    uint8_t tmpDeviceType       = Data[5];
    
    uint8_t tmpRepeater1        = Data[6];
    
    uint8_t tmpRepeater2        = Data[7];
    
    uint8_t tmpRepeater3        = Data[8];
    
    uint16_t tmpParityValue       = 0;
    
    // 保存设备类型，在应答包中使用
    //
    DeleteOneOfflineData_DeviceType = tmpDeviceType;
    
    // 设备编号
    //
    NRF905_SendBuffer[0] = tmpDeviceNoL;
    
    NRF905_SendBuffer[1] = tmpDeviceNoH;
    
    // 命令编号
    //
    NRF905_SendBuffer[2] = tmpCommandNo;
    
    // 命令流水号
    //
    NRF905_SendBuffer[3] = tmpCommandSerialNo;
    
    // 目的中继
    //
    NRF905_SendBuffer[4] = tmpRepeater1;
    
    // 中继1
    //
    NRF905_SendBuffer[5] = tmpRepeater1;
    
    // 中继2
    //
    NRF905_SendBuffer[6] = tmpRepeater2;
    
    // 中继3
    //
    NRF905_SendBuffer[7] = tmpRepeater3;
    
    // 数据（22字节）
    //
    NRF905_SendBuffer[8] = 0xF4;
    
    NRF905_SendBuffer[9] = tmpDeviceNoL;
    
    NRF905_SendBuffer[10] = tmpDeviceNoH;
    
    NRF905_SendBuffer[11] = tmpDeviceType;
    
    NRF905_SendBuffer[12] = App_Hal_Api.wireless->channelNo;
    
    memcpy(NRF905_SendBuffer + 13, Data + 9, 6);
    
    // 内部和校验
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer + 8, 11);
    NRF905_SendBuffer[19] = tmpParityValue;
    NRF905_SendBuffer[20] = tmpParityValue >> 8;
    
    // 填充字符0xA3
    //
    memset(NRF905_SendBuffer + 21, 0xF4, 9);
    
    // 外部和校验
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer, 30);
    NRF905_SendBuffer[30] = tmpParityValue;
    NRF905_SendBuffer[31] = tmpParityValue >> 8;
    
    // 发送数据到无线设备
    //
	App_Hal_Api.wireless->write(NRF905_SendBuffer);
	
	// 根据中继来设置无线发送等待超时时间
	//
	Pca_Start(NRF905_SendBuffer, 0);
}


void DeleteOneOfflineData_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpDeviceNoL        = Data[0];
    
    uint8_t tmpDeviceNoH        = Data[1];
    
    uint8_t tmpCommandSerialNo  = Data[3];
    
    // 设备编号
    //
    SocketData_SendBuffer[0] = tmpDeviceNoL;
    
    SocketData_SendBuffer[1] = tmpDeviceNoH;
    
    // 设备类型
    //
    SocketData_SendBuffer[2] = DeleteOneOfflineData_DeviceType;
    
    memcpy(SocketData_SendBuffer + 3, Data + 13, 7);
    
    // 发送中继器测试包给PC
    //
    PC_SendCommand(0x06, tmpCommandSerialNo, SocketData_SendBuffer, 10);
}





