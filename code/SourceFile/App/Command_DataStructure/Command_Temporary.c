#include "Command_Temporary.h"



// 控制器的状态
//
WiresslessChannel_Status_Typedef WiresslessChannel_Status = WirelessChannel_Free;


// 指令发送超时
//
uint8_t Timeout = 0;


// 用来递减超时
//
uint8_t TimeoutCounter = 0;


// 指令重发次数
//
uint8_t ResendTimes = 0;


// 计算和校验值
//
uint16_t Temporary_CalcSumParity(uint8_t *str, uint8_t len)
{
    uint8_t   i;
    uint16_t  parity = 0;
    
    for (i = 0; i < len; i++)
    {
        parity += str[i];
    }
    return parity;
}


// 开启PCA，给无线发送计时
// timeout:, resendTimes:, permitPool:
//
void Pca_SubStart(uint16_t timeout, uint8_t resendTimes)
{
	CR = 0;
    
    WiresslessChannel_Status = WirelessChannel_Busy;
    
    Timeout = timeout? timeout:1;
    
    TimeoutCounter = Timeout;
    
    ResendTimes = resendTimes;
    
    CR = 1;
}


void Pca_Start(uint8_t *str, uint8_t resendTimes)
{
	uint8_t baseTime = 0;
	
	// 如果是轮询指令，基准时间是1ms
	//
	if (str[Enum_Wirelss_CommandNo] == 0x01)
	{
		baseTime = 30;
	}
	// 如果是其他设备和中继指令，基准时间是20*5 = 100ms
	//
	else
	{
		baseTime = 50;
	}
	
	// 如果有中继的话，根据中继的数量来设置无线指令应答等待时间
	//
	if (str[Enum_Wirelss_Repeater1] != 0)
	{
		if (str[Enum_Wirelss_Repeater2] != 0)
		{
			if (str[Enum_Wirelss_Repeater3] != 0)
			{
				// 有中继1， 2， 3
				//
				Pca_SubStart(baseTime + 60, resendTimes); 
			}
			// 中继1， 2
			else
			{
				Pca_SubStart(baseTime + 40, resendTimes); 
			}
		}
		// 有中继1
		//
		else
		{
			Pca_SubStart(baseTime + 20, resendTimes); 
		}
	}
	// 没有中继
	//
	else 
	{
		Pca_SubStart(baseTime, resendTimes); 
	}
}


// 停止PCA
//
void Pca_Stop(void)
{
    CR = 0;
	
	ResendTimes = 0;
    
    WiresslessChannel_Status = WirelessChannel_Free;
}


// 每5ms中断一次, 实现超时重新开启扫描
//
void Pca_Interrupt() interrupt 7
{
    CCF0 = 0;                       // Clear interrupt flag
    
    CCAP0L = PCA_Value;             // Update compare value
    CCAP0H = PCA_Value >> 8;
    
    PCA_Value += T1000Hz;
    
    while (--TimeoutCounter == 0)
    {
        CR = 0;
		
		Pca_Stop(); 
    }
}


