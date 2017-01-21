#include "Command_OneCardOperation.h"


void OneCardOperation_DealData(uint8_t *Data)
{
    uint8_t tmpCommandNo        = Data[0];
    
    uint8_t tmpCommandSerialNo  = Data[1];
    
    uint8_t tmpDeviceNoL        = Data[3];
    
    uint8_t tmpDeviceNoH        = Data[4];
    
    uint8_t tmpRepeater1        = Data[6];
    
    uint8_t tmpRepeater2        = Data[7];
    
    uint8_t tmpRepeater3        = Data[8];
    
    uint16_t  tmpParityValue;
    
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
    
    
    // 目的中继, 中继1，中继2， 中继3
    //
    NRF905_SendBuffer[4] = tmpRepeater1;
    NRF905_SendBuffer[5] = tmpRepeater1;
    NRF905_SendBuffer[6] = tmpRepeater2;
    NRF905_SendBuffer[7] = tmpRepeater3;
    
    // 主要数据
    //
    memcpy(NRF905_SendBuffer + 8, Data + 9, 22);
    
    // 和校验
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



void OneCardOperation_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpDeviceNoL        = Data[0];
    
    uint8_t tmpDeviceNoH        = Data[1];

    uint8_t tmpCommandNo        = Data[2];
    
    uint8_t tmpCommandSerialNo  = Data[3];
    
    uint8_t tmpRepeater1        = Data[5];
    
    uint8_t tmpRepeater2        = Data[6];
    
    uint8_t tmpRepeater3        = Data[7];
    
    uint8_t tmpOperationResult  = Data[8];
    
    // 设备编号
    //
    SocketData_SendBuffer[0] = tmpDeviceNoL;
    SocketData_SendBuffer[1] = tmpDeviceNoH;
    
    
    // 设备类型
    //
    SocketData_SendBuffer[2] = 0x01;                   // 默认是消费机
    
    
    // 目的中继, 中继1，中继2， 中继3
    //
    SocketData_SendBuffer[3] = tmpRepeater1;
    SocketData_SendBuffer[4] = tmpRepeater2;
    SocketData_SendBuffer[5] = tmpRepeater3;
    
    
    // 修改结果（1）+ 卡号（4） + 交易流水号（4）
    //
    memcpy(SocketData_SendBuffer + 6, Data + 8, 9);
	
    // 发送中继器测试包给PC
    //
    PC_SendCommand(0xF4, tmpCommandSerialNo, SocketData_SendBuffer,  15);
}






