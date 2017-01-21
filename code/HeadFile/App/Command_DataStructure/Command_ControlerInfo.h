#ifndef __COMMAND_CONTROLERINFO_H_
#define __COMMAND_CONTROLERINFO_H_

#include "APP_HAL_API.h"


typedef struct
{
	uint8_t StartScan:1;						// 开始扫描标志， 初始化值0
	
	uint8_t HeartbeatNotAckTimes:3;				// 心跳没有应答次数，初始化值为0。设置轮询时清零，心跳请求时递增（达到一定数量关掉轮询），心跳应答时清零
	
	uint8_t Reserver:4;							// 保留未来使用
		
	uint8_t FirstBootup;						// 首次开机标志位， 0x31表示首次开机， 0x32表示非首次开机
	
	uint8_t HeartbeatInterval;					// 心跳间隔，单位是1S
	
	uint8_t HeartbeatInterval_Bak;				// 心跳间隔备份，单位是1S
	
	uint8_t Version[3];							// 控制器版本号(例如：0x16, 0x12, 0x15)
	
	uint8_t Name[10];							// 控制器名称()
	
	uint8_t Info[10];							// 控制器附带字段()
	
	uint8_t Password[6];						// 控制器的密码
	
}ControlerInfo_Typedef;


#define SetStartScan(val)						ControlerInfo.StartScan = val

#define IsStartScan()							ControlerInfo.StartScan

#define SetHeartbeatNotAckTimes(val)			ControlerInfo.HeartbeatNotAckTimes = val

#define SetFirstBootUp(val)						ControlerInfo.FirstBootup = val

#define SetHeartbeatInterval(val)				ControlerInfo.HeartbeatInterval = val? val:5

#define SetHeartbeatIntervalBak(val)			ControlerInfo.HeartbeatInterval_Bak = val? val:5

#define	RestoreHeartbeatInterval()				ControlerInfo.HeartbeatInterval = ControlerInfo.HeartbeatInterval_Bak		// 恢复心跳间隔(当断网的时候，为了快速重连，因此缩短心跳间隔，然后网络重连的时候，再恢复原来的值)


extern	ControlerInfo_Typedef					ControlerInfo;


void ControlerInfo_ReadName(void);


void ControlerInfo_WriteName(void);


void ControlerInfo_ReadNetworkParameter(void);


void ControlerInfo_WriteNetworkParameter(void);
	

void ControlerInfo_Init(void);



#endif
