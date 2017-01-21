#ifndef __HOOKFUNCTION_H_
#define __HOOKFUNCTION_H_


#include "Command_ControlerInfo.h"

// =====================  线程相关的钩子函数  ============================
//
// 接收PC数据的钩子函数
//
void HookFunction_ReceivePcData(void);

// =====================  控制器指令相关的钩子函数  ============================
//
// 心跳相关的钩子函数
//
void HookFunction_HeartbeatReq(void);

void HookFunction_HeartbeatAck(void);


// 工作模式的钩子函数
//
void HookFunction_ControlerWorkMode(void);


// ====================  中继器指令相关的钩子函数  =============================
// 



// ====================  设备指令相关的钩子函数  ===============================
//





#endif
