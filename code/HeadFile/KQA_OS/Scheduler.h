#ifndef __SCHEDULE_H_
#define __SCHEDULE_H_


#include "OS_HAL.h"


typedef struct
{
	ProcVoid_Bool				function;						/// 任务调度函数
	
	uint16_t					intervalTicks;					/// 滴答间隔
	
	uint32_t					maxLimitMilliseconds;			/// 最大延迟执行时间（毫秒为单位）
	
	/// 以下的成员变量用来辅助任务调度的算法，定义这个类型的变量时不用初始化(留着这个尾巴的确不优雅，以后移植到c++环境，再做优化)
	///
	uint16_t					__intervalTicks;				/// 任务调度函数执行时的滴答间隔
	
	uint32_t					__maxLimitMilliseconds;			/// 任务调度函数执行时的系统毫秒数（毫秒为单位）
	
}Task;


typedef struct
{
	// 私有接口
	//
	ProcVoidP_Void				init;
	
	// 公共接口
	//
	ProcVoid_Void				run;							/// Scheduler执行逻辑
	
	ProcVoidPUint8_Void			registerTask;					/// 第一个参数是Task*， 第二个参数是task个数
	
	ProcUint16_Void				delayMilliseconds;				/// 毫秒级别延时
	
	ProcVoid_Uint32				milliseconds;					/// 系统开机以来的系统毫秒数
	
	ProcVoid_Void				ticksIncrease;					/// 用来递增滴答数
	
	// 私有成员变量
	//
	uint16_t					ticks;							/// 滴答数
	
	Task						*tasks;							/// 任务
	
	uint8_t						taskEntries;					/// 任务个数
	
}Scheduler;


void Scheduler_Init(void *self);



#endif

