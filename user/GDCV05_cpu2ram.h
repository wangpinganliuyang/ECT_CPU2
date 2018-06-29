/*
 * GDCV05_cpu2ram.h
CPU1和CPU2共享结构体定义
 */

#ifndef USER_GDCV05_CPU2RAM_H_
#define USER_GDCV05_CPU2RAM_H_
#include "stdbool.h"

typedef struct {
	bool CycleOrder:1;   //翻转更新
	bool UpPara:2;  //0：空闲状态 2：上传参数完成
	bool DownPara:2; // 0: 空闲状态 2：下载参数完成
	bool res0:11;          //预留
}FLAG_BITS;

typedef union {
	FLAG_BITS bits;
	uint16_t all;
}FLAG;

//状态字定义
typedef struct {
	bool ReadySwithOn:1; //1:准备好开启
	bool SwithedOn:1; //1：开启
	bool OperationEnabl:1; //1:运行使能
	bool Fault:1; //1:故障
	bool VoltageEnabl:1;//1：高电源使能 DC有
	bool QuickStop:1;//0:处于急停状态；1：不支持急停或急停功能没有运行
	bool SwitchOnDisabl:1;//0:处于不可接通电源状态；
	bool Warning:1;//1:发生报警；
	bool res0:1;//预留
	bool Remote:1;  //0:非远程模式   1：远程模式  EtherCAT为远程模式
	bool TargetReached:1;   //1:达到目标指令，在轨迹位置模式下、标零模式下
	bool InternalLimitActive:1;  //
	bool res1:4;  //预留
}STATUSWORD_BITS;

typedef union {
	STATUSWORD_BITS bits;
	uint16_t all;
}STATUSWORD;

//CPU1 TO CPU2
typedef struct {
	 FLAG Flags;        //
	 STATUSWORD StatusWord;//状态字
	uint16_t ModesOfOperationDisplay;//0x6061：伺服显示的运行模式，1：轨迹位置控制模式；2：速度控制模式 3：轨迹速度控制模式 4：轨迹转矩控制模式  6：原点回归位置控制模式 7：内插位置控制模式  8：同步周期位置模式 9：同步周期速度模式 10：同步周期转矩模式
	uint16_t Res1;
	int32_t PositionActualValue;//主编码器实际位置
	int32_t VelocityActualValue;//反馈电动机当前实际转速
	int32_t TorqueActualValue;//反馈转矩
	uint32_t GDCIndex_Up;//上传参数索引:高16位为子索引，低16位为参数索引
	uint32_t GDCIndexValue_Up;//上传GDC参数索引值
	uint32_t GDCIndex_Download;//下载参数索引：高16位子索引，低16位为参数索引
	uint32_t GDCIndexValue_Download;//下载参数索引值
}GDC_R,*pGDC_R;
extern GDC_R  CPU1_CPU2;

//控制字定义   主站依此发送0x6 0x7 0xf

typedef struct {
	bool SwitchOn:1;   //0-1:接通电源；  1-0：切断电源
	bool EnableVoltage:1;   //0-1:使能供电 ；  1-0：停止供电---直流母线电压使能
	bool QucikStop:1;  //1-0:紧急停止
	bool EnableOperation:1;  //0-1:使能运行；  1-0:停止运行
	bool res0:3;              //预留
	bool FaultRest:1;        //复位错误
	bool Halt:1;             //暂停
	bool res1:7;              //预留
}CONTROLWORD_BITS;

typedef union {
	CONTROLWORD_BITS bits;
	UINT16 all;
}CONTROLWORD;


//CPU2 TO CPU1
typedef struct  {
	 FLAG Flags;            //
	 CONTROLWORD ControlWord;//x6040:控制字
	uint16_t ModesOfOperation;//x6060:运行模式1：Profile 位置控制模式；2：速度控制模式 3：Profile 速度控制模式 4：Profile转矩控制模式  6：原点回归位置控制模式 7：补偿位置控制模式  8：同步周期位置模式 9：同步周期速度模式 10：同步周期转矩模式
	uint16_t SyncType;//0:自由运行模式；2：SYNC0同步方式
	uint32_t SetTarget;//相应运行模式下的目标值
	uint32_t GDCIndex_Up;//上传参数索引：高16位为子索引、低16位参数索引
	uint32_t GDCIndex_Download;//下载参数索引：高16位为子索引、低16位参数索引
	uint32_t GDCIndexValue_Download;//下载参数值
	uint32_t CycleTime;//通讯周期
	uint32_t DC2DCValue;//两个DC中断时间间隔
}GDC_WR,*pGDCWR;

extern GDC_WR CPU2_CPU1;
//

#endif /* USER_GDCV05_CPU2RAM_H_ */

//非周期性通讯 每个参数有两个子索引，默认子索引值为0
