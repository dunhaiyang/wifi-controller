#include "Command_OneCardDataUploadDelete.h"



// 操作标记，这个影响到轮询，比如：如果接收到设备开机删除回包，那么马上开启轮询，实现轮询下一台消费机
//
uint8_t   OneCardDataUploadDelete_OperationFlag = 0x55; 



void OneCardDataUploadDelete_DealData(uint8_t *Data)
{
    uint8_t tmpCommandNo        = Data[0];
    
    uint8_t tmpCommandSerialNo  = Data[1];
    
    uint8_t tmpDeviceNoL        = Data[3];
    
    uint8_t tmpDeviceNoH        = Data[4];
    
    uint8_t tmpDeviceType       = Data[5];
    
    uint8_t tmpRepeater1        = Data[6];
    
    uint8_t tmpRepeater2        = Data[7];
    
    uint8_t tmpRepeater3        = Data[8];
    
    uint16_t tmpParityValue;
    
    OneCardDataUploadDelete_OperationFlag  = Data[9];           // 在设备删除应答包中有用
    
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
    
    // 目的中继, 中继1， 中继2， 中继3
    //
    NRF905_SendBuffer[4] = tmpRepeater1;
    NRF905_SendBuffer[5] = tmpRepeater1;
    NRF905_SendBuffer[6] = tmpRepeater2;
    NRF905_SendBuffer[7] = tmpRepeater3;
	
    
    // 操作标记（1） + 卡号（4）+ 交易流水号（4） + 可使用的未超额余额（2）
    //
    memcpy(NRF905_SendBuffer + 8, Data + 9, 11);
    
    
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


// 删除指令回包
//
void OneCardDataUploadDelete_SendDataToPC(uint8_t *Data)
{
    Data = Data;
}






