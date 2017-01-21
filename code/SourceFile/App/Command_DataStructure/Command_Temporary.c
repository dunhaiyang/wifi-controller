#include "Command_Temporary.h"



// ��������״̬
//
WiresslessChannel_Status_Typedef WiresslessChannel_Status = WirelessChannel_Free;


// ָ��ͳ�ʱ
//
uint8_t Timeout = 0;


// �����ݼ���ʱ
//
uint8_t TimeoutCounter = 0;


// ָ���ط�����
//
uint8_t ResendTimes = 0;


// �����У��ֵ
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


// ����PCA�������߷��ͼ�ʱ
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
	
	// �������ѯָ���׼ʱ����1ms
	//
	if (str[Enum_Wirelss_CommandNo] == 0x01)
	{
		baseTime = 30;
	}
	// ����������豸���м�ָ���׼ʱ����20*5 = 100ms
	//
	else
	{
		baseTime = 50;
	}
	
	// ������м̵Ļ��������м̵���������������ָ��Ӧ��ȴ�ʱ��
	//
	if (str[Enum_Wirelss_Repeater1] != 0)
	{
		if (str[Enum_Wirelss_Repeater2] != 0)
		{
			if (str[Enum_Wirelss_Repeater3] != 0)
			{
				// ���м�1�� 2�� 3
				//
				Pca_SubStart(baseTime + 60, resendTimes); 
			}
			// �м�1�� 2
			else
			{
				Pca_SubStart(baseTime + 40, resendTimes); 
			}
		}
		// ���м�1
		//
		else
		{
			Pca_SubStart(baseTime + 20, resendTimes); 
		}
	}
	// û���м�
	//
	else 
	{
		Pca_SubStart(baseTime, resendTimes); 
	}
}


// ֹͣPCA
//
void Pca_Stop(void)
{
    CR = 0;
	
	ResendTimes = 0;
    
    WiresslessChannel_Status = WirelessChannel_Free;
}


// ÿ5ms�ж�һ��, ʵ�ֳ�ʱ���¿���ɨ��
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


