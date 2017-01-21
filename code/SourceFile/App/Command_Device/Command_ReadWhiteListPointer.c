#include "Command_ReadWhiteListPointer.h"


uint8_t ReadWhiteListPointer_DeviceType = 0xFF;


void ReadWhiteListPointer_DealData(uint8_t *Data)
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
    ReadWhiteListPointer_DeviceType = tmpDeviceType;
    
    
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
    
    // 数据
    //
    NRF905_SendBuffer[8] = 0xE7;
    
    memcpy(NRF905_SendBuffer + 9, Data + 9, 8);
    
    NRF905_SendBuffer[17] = tmpDeviceNoL;
    
    NRF905_SendBuffer[18] = tmpDeviceNoH;
    
    NRF905_SendBuffer[19] = tmpDeviceType;
    
    NRF905_SendBuffer[20] = App_Hal_Api.wireless->channelNo;
    
    NRF905_SendBuffer[21] = Data[17];
    
    // 内部和校验
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer + 8, 14);
    NRF905_SendBuffer[22] = tmpParityValue;
    NRF905_SendBuffer[23] = tmpParityValue >> 8;
    
    memset(NRF905_SendBuffer + 24, 0xE7, 6);
    
    // 外部和校验
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer, 30);
    NRF905_SendBuffer[Enum_Wirelss_ParityL] = tmpParityValue;
    NRF905_SendBuffer[Enum_Wirelss_ParityH] = tmpParityValue >> 8;
    
    // 发送数据到无线设备
    //
	App_Hal_Api.wireless->write(NRF905_SendBuffer);
	
	// 根据中继来设置无线发送等待超时时间
	//
	Pca_Start(NRF905_SendBuffer, 0);
}


void ReadWhiteListPointer_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpDeviceNoL    = Data[0];
    
    uint8_t tmpDeviceNoH    = Data[1];
    
    uint8_t tmpCommandSerialNo  = Data[3];
    
    uint8_t tmpUploadMode       = Data[9];
    
    // 设备编号
    //
    SocketData_SendBuffer[0] = tmpDeviceNoL;
    
    SocketData_SendBuffer[1] = tmpDeviceNoH;
    
    // 设备类型
    //
    SocketData_SendBuffer[2] = ReadWhiteListPointer_DeviceType;
    
    memcpy(SocketData_SendBuffer + 3, Data + 13, 12);
    
    // 发送中继器测试包给PC
    //
    PC_SendCommand(0x16, tmpCommandSerialNo, SocketData_SendBuffer,  15); 
}





