#ifndef __HOOKFUNCTION_H_
#define __HOOKFUNCTION_H_


#include "Command_ControlerInfo.h"

// =====================  �߳���صĹ��Ӻ���  ============================
//
// ����PC���ݵĹ��Ӻ���
//
void HookFunction_ReceivePcData(void);

// =====================  ������ָ����صĹ��Ӻ���  ============================
//
// ������صĹ��Ӻ���
//
void HookFunction_HeartbeatReq(void);

void HookFunction_HeartbeatAck(void);


// ����ģʽ�Ĺ��Ӻ���
//
void HookFunction_ControlerWorkMode(void);


// ====================  �м���ָ����صĹ��Ӻ���  =============================
// 



// ====================  �豸ָ����صĹ��Ӻ���  ===============================
//





#endif
