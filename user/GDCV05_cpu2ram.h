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
	bool ReadySwithOn:1;          //bit0   1:准备好开启
	bool SwithedOn:1;             //bit1   1：开启
	bool OperationEnabl:1;        //bit2   1:运行使能
	bool Fault:1;                 //bit3   1:故障
	bool VoltageEnabl:1;          //bit4   1：高电源使能 DC有
	bool QuickStop:1;             //bit5   0:处于急停状态；1：不支持急停或急停功能没有运行,，默认置1，不支持急停
	bool SwitchOnDisabl:1;        //bit6   0:处于不可接通电源状态；
	bool Warning:1;               //bit7   1:发生报警；
	bool res0:1;                  //bit8          预留
	bool Remote:1;                //bit9   0:非远程模式   1：远程模式  EtherCAT为远程模式，默认置1
	bool TargetReached:1;         //bit10     回零模式下：若控制字.stop为0--0：未达到回零位置，1达到回零位置，stop为1---0，转速未为0,1转速为0；其它模式下忽略
	bool InternalLimitActive:1;   //bit11
	bool homingattained:1;        //bit12      回零模式下：1实现回零；周期性同步位置/速度模式下：0忽略总线的目标，1采用总线目标；
	bool homingerror:1;           //bit13     回零模式下：1出现回零错误；周期性同步位置模式下：1出现跟随错误；其它模式下：忽略该位
	bool res1:2;                  //bit14-15      预留
}STATUSWORD_BITS;

typedef union {
	STATUSWORD_BITS bits;
	uint16_t all;
}STATUSWORD;

typedef struct {
    bool TouchProbe1Enabled:1;      //bit0    0:1通道处于关闭状态      1:1通道处于开启状态
    bool TouchProbe1PStored:1;      //bit1    1:1通道上升沿锁存
    bool TouchProbe1NStored:1;      //bit2     1:1通道在下降沿锁存有值
    bool res0:3;                    //bit3-5   预留
    bool user1:1;                    //bit6
    bool TouchProbe1PStoredC:1;     //bit7    在连续模式下，上升沿锁存触发
    bool TouchProbe2Enabled:1;      //bit8    0:2通道处于关闭状态      1:2通道处于开启状态
    bool TouchProbe2PStored:1;      //bit9    1:2通道上升沿锁存
    bool TouchProbe2NStored:1;      //bit10   1:2通道在下降沿锁存有值
    bool res1:3;                    //bit11-13   预留
    bool user2:1;                   //bit14
    bool TouchProbe2PStoredC:1;     //bit15    在连续模式下，上升沿锁存触发
}TOUCHPROBESTATUS_BITS;
typedef union {
    TOUCHPROBESTATUS_BITS bit;
    uint16_t all;
}TOUCHPROBESTATUS;

//CPU1 TO CPU2
typedef struct {
	 FLAG Flags;        //
	 STATUSWORD StatusWord;//状态字
	uint16_t ModesOfOperationDisplay;//0x6061：伺服显示的运行模式，1：轨迹位置控制模式；2：速度控制模式 3：轨迹速度控制模式 4：轨迹转矩控制模式  6：原点回归位置控制模式 7：内插位置控制模式  8：同步周期位置模式 9：同步周期速度模式 10：同步周期转矩模式
	TOUCHPROBESTATUS TouchProbestatus;    //捕获状态
	int32_t TouchProbesP;         //捕获位置
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
	bool SwitchOn:1;             //bit0    0-1:接通电源；  1-0：切断电源
	bool EnableVoltage:1;        //bit1    0-1:使能供电 ；  1-0：停止供电---直流母线电压使能
	bool QucikStop:1;            //bit2    1-0:紧急停止
	bool EnableOperation:1;      //bit3    0-1:使能运行；  1-0:停止运行
	bool Homing:1;               //bit4              回零模式下：1 回零启动；周期性同步位置模式/速度模式下，忽略该位
	bool res0:2;                 //bit5-6         预留
	bool FaultRest:1;            //bit7     0-1上升沿复位错误
	bool Stop:1;                 //bit8                 回零模式下： 停止；   周期性同步位置模式/速度模式子啊，忽略该位
	bool OP;                     //bit9     1：通讯建立
	bool res1:6;                 //bit10-bit15  预留
}CONTROLWORD_BITS;

typedef union {
	CONTROLWORD_BITS bits;
	UINT16 all;
}CONTROLWORD;

typedef struct {
    bool TouchProbe1On:1;           //bit0 1：开启1通道                   0:关闭1通道
    bool TouchProbe1Continuous:1;   //bit1 1:连续
    bool Probe1ZPulse:1;             //bit2 1:1通道Z脉冲
    bool res0:1;                    //bit3 预留
    bool Probe1PositiveEnable:1;    //bit4 1：在上升沿进行1通道采样
    bool Probe1NegatibeEnable:1;    //bit5 1：在下降沿进行1通道采样
    bool res1:2;                    //bit6-7 预留
    bool TouchProbe2On:1;           //bit8 1:开启通道2     0：关闭2通道
    bool Probe2Continuous:1;        //bit9 1:连续
    bool Probe2ZPulse:1;            //bit10 1：通道2z脉冲
    bool res2:1;                    //bit11 预留
    bool Probe2PositiveEnable:1;    //bit12 1：在上升沿进行2通道采样
    bool Probe2NegatibeEnable:1;    //bit13 1：在下降沿进行2通道采样
    bool res3:2;                    //bit14-15 预留
}TOUCHPROBEFUNCTION_BITS;

typedef union {
    TOUCHPROBEFUNCTION_BITS bits;
    uint16_t all;
}TOUCHPROBEFUNCTION;

//CPU2 TO CPU1
typedef struct  {
	 FLAG Flags;            //
	 CONTROLWORD ControlWord;//x6040:控制字
	uint16_t ModesOfOperation;//x6060:运行模式1：Profile 位置控制模式；2：速度控制模式 3：Profile 速度控制模式 4：Profile转矩控制模式  6：原点回归位置控制模式 7：补偿位置控制模式  8：同步周期位置模式 9：同步周期速度模式 10：同步周期转矩模式
	uint16_t SyncType;//2:同步运行方式
	TOUCHPROBEFUNCTION TouchProbeFunction;//捕获函数
	uint16_t res1;                //保留
	uint32_t TargetPosition;//目标位置
	uint32_t TargetVelocity;//目标速度
	uint32_t TargetTorque;//目标转矩
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
