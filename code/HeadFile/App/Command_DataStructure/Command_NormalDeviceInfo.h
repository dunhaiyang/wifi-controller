#ifndef __COMMAND_NORMAL_DEVICEINFO_H_
#define __COMMAND_NORMAL_DEVICEINFO_H_


#include "APP_HAL_API.h"


// 支持最大存储的设备数据数
//
#define NormalDeviceListSum 40


// 设备数据结构（自动轮询中使用）
//
typedef struct
{
    uint8_t deviceNumber[2];              // 设备号
    
    uint8_t deviceMainRoute[3];           // 主路由
    
    uint8_t deviceBakRoute[3];            // 备份路由
	
	uint8_t deviceFailTimes;              // 轮询失败次数，达到一定次数，就切换主路由和备份路由来轮询设备
    
    uint8_t usingDeviceRouteNow:1;        // 使用设备路由：0->使用主路由， 1->使用备份路由
	
	uint8_t deviceOnline:1;				  // 设备连接在线
    
    uint8_t deviceValidFlag:1;            // 轮询有效标志, 0->表示无效，1->表示有效
    
    uint8_t deviceType:5;                 // 设备类型: 多门门禁为23最大
    
}NormalDeviceInfo_Typedef;



// 设备列表, 设备列表元素数量
//
extern  NormalDeviceInfo_Typedef   NormalDeviceList[NormalDeviceListSum];


// 已经存储了多少设备列表
//
extern  uint8_t   NormalDeviceListUsage;


// 设备数据的流水号
//
extern  uint8_t   DeviceDataSerialNo;


// ============================================== 设备列表相关操作 ==================================================
// =================================================================================================================


// 初始化设备列表
//
void NormalDeviceInfo_Init();


// 查找指定数据, 返回-1表示找不到，其他值标志找到的下标
//
int8_t NormalDeviceInfo_FindDeviceList(uint8_t deviceNoL, uint8_t deviceNoH, uint8_t deviceType);


// 查询还可以存储多少个设备列表数据
//
#define NormalDeviceInfo_HowManySpace() (NormalDeviceListSum - NormalDeviceListUsage)


// 增加设备列表
//
bool NormalDeviceInfo_AddDeviceList(uint8_t *deviceListAddress);


// 删除设备列表中设备
//
bool NormalDeviceInfo_DeleteDeviceList(uint8_t *deviceListAddress);


// 清空设备列表
//
bool NormalDeviceInfo_EmptyDeviceList();


//打印全部设备列表结果，用于调试
//
void NormalDeviceInfo_TravelDeviceList();



#endif