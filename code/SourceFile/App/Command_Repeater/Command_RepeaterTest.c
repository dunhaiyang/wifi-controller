#include "Command_RepeaterTest.h"


void RepeaterTest_DealData(uint8_t *Data)
{
    uint8_t tmpCommandNo        = Data[Enum_CommandNo];
    
    uint8_t tmpCommandSerialNo  = Data[Enum_CommandSerialNo];
    
    uint8_t tmpRepeaterNo       = Data[Enum_CommandContent + 0];
    
    uint8_t tmpRepeater1        = Data[Enum_CommandContent + 1];
    
    uint8_t tmpRepeater2        = Data[Enum_CommandContent + 2];
    
    uint8_t tmpRepeater3        = Data[Enum_CommandContent + 3];
    
    uint8_t tmpTestPacketNoL    = Data[Enum_CommandContent + 4];
    
    uint8_t tmpTestPacketNoH    = Data[Enum_CommandContent + 5];
    
    uint16_t tmpParityValue       = 0;
    
    
    // 设备编号
    //
    NRF905_SendBuffer[0] = 0xEB;
    NRF905_SendBuffer[1] = 0xFD;
    
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
    NRF905_SendBuffer[8] = 0xA3;
    NRF905_SendBuffer[9] = tmpRepeaterNo;
    NRF905_SendBuffer[10] = App_Hal_Api.wireless->channelNo;
    NRF905_SendBuffer[11] = tmpTestPacketNoL;
    NRF905_SendBuffer[12] = tmpTestPacketNoH;
    
    // 内部和校验
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer + 8, 5);
    NRF905_SendBuffer[13] = tmpParityValue;
    NRF905_SendBuffer[14] = tmpParityValue >> 8;
    
    // 填充字符0xA3
    //
    memset(NRF905_SendBuffer + 15, 0xA3, 15);
    
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



void RepeaterTest_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpCommandSerialNo  = Data[3];
    
    uint8_t tmpRepeaterNo       = Data[9];
    
    uint8_t tmpTestPacketNoL    = Data[11];
    
    uint8_t tmpTestPacketNoH    = Data[12];
    
    // 中继编号
    //
    SocketData_SendBuffer[0] = tmpRepeaterNo;
    
    // 测试包序号
    //
    SocketData_SendBuffer[1] = tmpTestPacketNoL;
    SocketData_SendBuffer[2] = tmpTestPacketNoH;
    
    // 发送中继器测试包给PC
    //
    PC_SendCommand(0x68, tmpCommandSerialNo, SocketData_SendBuffer, 3);
}


