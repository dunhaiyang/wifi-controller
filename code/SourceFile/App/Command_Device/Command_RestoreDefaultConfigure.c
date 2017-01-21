#include "Command_RestoreDefaultConfigure.h"

uint8_t RestoreDefaultConfigure_DeviceType = 0xFF;

void RestoreDefaultConfigure_DealData(uint8_t *Data)
{
    uint8_t tmpCommandNo        = Data[0];
    
    uint8_t tmpCommandSerialNo  = Data[1];
    
    uint8_t tmpDeviceNoL        = Data[3];
    
    uint8_t tmpDeviceNoH        = Data[4];
    
    uint8_t tmpDeviceType       = Data[5];
    
    uint8_t tmpRepeater1        = Data[6];
    
    uint8_t tmpRepeater2        = Data[7];
    
    uint8_t tmpRepeater3        = Data[8];
    
    uint8_t tmpRestoreFlag1     = Data[9];
    
    uint8_t tmpRestoreFlag2     = Data[10];
    
    uint16_t tmpParityValue       = 0;
    
    // 保存设备类型，在应答包中使用
    //
    RestoreDefaultConfigure_DeviceType = tmpDeviceType;
    
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
    NRF905_SendBuffer[8] = tmpRestoreFlag1;
    NRF905_SendBuffer[9] = tmpRestoreFlag2;
    
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


void RestoreDefaultConfigure_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpDeviceNoL        = Data[0];
    
    uint8_t tmpDeviceNoH        = Data[1];
    
    uint8_t tmpCommandSerialNo  = Data[3];
    
    uint8_t tmpOperationResult  = Data[8];
    
    
    // 设备编号
    //
    SocketData_SendBuffer[0] = tmpDeviceNoL;
    SocketData_SendBuffer[1] = tmpDeviceNoH;
    
    // 设备编号
    //
    SocketData_SendBuffer[2] = RestoreDefaultConfigure_DeviceType;
    
    // 指令执行结果
    //
    SocketData_SendBuffer[3] = tmpOperationResult;
    
    // 发送中继器测试包给PC
    //
    PC_SendCommand(0x32, tmpCommandSerialNo, SocketData_SendBuffer, 4);
}





