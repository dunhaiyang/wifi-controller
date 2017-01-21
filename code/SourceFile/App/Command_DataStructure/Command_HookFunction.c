#include "Command_HookFunction.h"


// =====================  线程相关的钩子函数  ============================
//
// 接收PC数据的钩子函数
//
void HookFunction_ReceivePcData(void)
{
	// 清除心跳无应答次数，原因是可能PC数据收发负担比较重，心跳回答来不及）
	//
	ControlerInfo.HeartbeatNotAckTimes = 0;
}


// =====================  控制器指令相关的钩子函数  ============================
//
// 心跳相关的钩子函数
//
void HookFunction_HeartbeatReq(void)
{
	// 实现N次没有心跳应答，那么就断定控制器和电脑通讯已断，那么就停止轮询
	//
	if (ControlerInfo.HeartbeatNotAckTimes > 3)
	{
		SetStartScan(0);						// 停止轮询
	}
		
	// 否则就增加无应答次数
	else
	{
		ControlerInfo.HeartbeatNotAckTimes++;
	}
}

void HookFunction_HeartbeatAck(void)
{
	// 心跳无应答次数归零
	//
	ControlerInfo.HeartbeatNotAckTimes = 0;
	
	// 恢复原始心跳间隔
	//
	RestoreHeartbeatInterval();
	
	// 首次开机标志清掉
	//
	ControlerInfo.FirstBootup = 0x32;
}


// 工作模式的钩子函数
//
void HookFunction_ControlerWorkMode(void)
{
	// 心跳无应答次数归零
	//
	ControlerInfo.HeartbeatNotAckTimes = 0;
}


// ====================  中继器指令相关的钩子函数  =============================
// 



// ====================  设备指令相关的钩子函数  ===============================
//








