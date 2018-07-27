/*
 * GDCV05_cpu2ram.h
CPU1��CPU2����ṹ�嶨��
 */

#ifndef USER_GDCV05_CPU2RAM_H_
#define USER_GDCV05_CPU2RAM_H_
#include "stdbool.h"

typedef struct {
	bool CycleOrder:1;   //��ת����
	bool UpPara:2;  //0������״̬ 2���ϴ��������
	bool DownPara:2; // 0: ����״̬ 2�����ز������
	bool res0:11;          //Ԥ��
}FLAG_BITS;

typedef union {
	FLAG_BITS bits;
	uint16_t all;
}FLAG;

//״̬�ֶ���
typedef struct {
	bool ReadySwithOn:1;          //bit0   1:׼���ÿ���
	bool SwithedOn:1;             //bit1   1������
	bool OperationEnabl:1;        //bit2   1:����ʹ��
	bool Fault:1;                 //bit3   1:����
	bool VoltageEnabl:1;          //bit4   1���ߵ�Դʹ�� DC��
	bool QuickStop:1;             //bit5   0:���ڼ�ͣ״̬��1����֧�ּ�ͣ��ͣ����û������,��Ĭ����1����֧�ּ�ͣ
	bool SwitchOnDisabl:1;        //bit6   0:���ڲ��ɽ�ͨ��Դ״̬��
	bool Warning:1;               //bit7   1:����������
	bool res0:1;                  //bit8          Ԥ��
	bool Remote:1;                //bit9   0:��Զ��ģʽ   1��Զ��ģʽ  EtherCATΪԶ��ģʽ��Ĭ����1
	bool TargetReached:1;         //bit10     ����ģʽ�£���������.stopΪ0--0��δ�ﵽ����λ�ã�1�ﵽ����λ�ã�stopΪ1---0��ת��δΪ0,1ת��Ϊ0������ģʽ�º���
	bool InternalLimitActive:1;   //bit11
	bool homingattained:1;        //bit12      ����ģʽ�£�1ʵ�ֻ��㣻������ͬ��λ��/�ٶ�ģʽ�£�0�������ߵ�Ŀ�꣬1��������Ŀ�ꣻ
	bool homingerror:1;           //bit13     ����ģʽ�£�1���ֻ������������ͬ��λ��ģʽ�£�1���ָ����������ģʽ�£����Ը�λ
	bool res1:2;                  //bit14-15      Ԥ��
}STATUSWORD_BITS;

typedef union {
	STATUSWORD_BITS bits;
	uint16_t all;
}STATUSWORD;

typedef struct {
    bool TouchProbe1Enabled:1;      //bit0    0:1ͨ�����ڹر�״̬      1:1ͨ�����ڿ���״̬
    bool TouchProbe1PStored:1;      //bit1    1:1ͨ������������
    bool TouchProbe1NStored:1;      //bit2     1:1ͨ�����½���������ֵ
    bool res0:3;                    //bit3-5   Ԥ��
    bool user1:1;                    //bit6
    bool TouchProbe1PStoredC:1;     //bit7    ������ģʽ�£����������津��
    bool TouchProbe2Enabled:1;      //bit8    0:2ͨ�����ڹر�״̬      1:2ͨ�����ڿ���״̬
    bool TouchProbe2PStored:1;      //bit9    1:2ͨ������������
    bool TouchProbe2NStored:1;      //bit10   1:2ͨ�����½���������ֵ
    bool res1:3;                    //bit11-13   Ԥ��
    bool user2:1;                   //bit14
    bool TouchProbe2PStoredC:1;     //bit15    ������ģʽ�£����������津��
}TOUCHPROBESTATUS_BITS;
typedef union {
    TOUCHPROBESTATUS_BITS bit;
    uint16_t all;
}TOUCHPROBESTATUS;

//CPU1 TO CPU2
typedef struct {
	 FLAG Flags;        //
	 STATUSWORD StatusWord;//״̬��
	uint16_t ModesOfOperationDisplay;//0x6061���ŷ���ʾ������ģʽ��1���켣λ�ÿ���ģʽ��2���ٶȿ���ģʽ 3���켣�ٶȿ���ģʽ 4���켣ת�ؿ���ģʽ  6��ԭ��ع�λ�ÿ���ģʽ 7���ڲ�λ�ÿ���ģʽ  8��ͬ������λ��ģʽ 9��ͬ�������ٶ�ģʽ 10��ͬ������ת��ģʽ
	TOUCHPROBESTATUS TouchProbestatus;    //����״̬
	int32_t TouchProbesP;         //����λ��
	int32_t PositionActualValue;//��������ʵ��λ��
	int32_t VelocityActualValue;//�����綯����ǰʵ��ת��
	int32_t TorqueActualValue;//����ת��
	uint32_t GDCIndex_Up;//�ϴ���������:��16λΪ����������16λΪ��������
	uint32_t GDCIndexValue_Up;//�ϴ�GDC��������ֵ
	uint32_t GDCIndex_Download;//���ز�����������16λ����������16λΪ��������
	uint32_t GDCIndexValue_Download;//���ز�������ֵ
}GDC_R,*pGDC_R;
extern GDC_R  CPU1_CPU2;

//�����ֶ���   ��վ���˷���0x6 0x7 0xf

typedef struct {
	bool SwitchOn:1;             //bit0    0-1:��ͨ��Դ��  1-0���жϵ�Դ
	bool EnableVoltage:1;        //bit1    0-1:ʹ�ܹ��� ��  1-0��ֹͣ����---ֱ��ĸ�ߵ�ѹʹ��
	bool QucikStop:1;            //bit2    1-0:����ֹͣ
	bool EnableOperation:1;      //bit3    0-1:ʹ�����У�  1-0:ֹͣ����
	bool Homing:1;               //bit4              ����ģʽ�£�1 ����������������ͬ��λ��ģʽ/�ٶ�ģʽ�£����Ը�λ
	bool res0:2;                 //bit5-6         Ԥ��
	bool FaultRest:1;            //bit7     0-1�����ظ�λ����
	bool Stop:1;                 //bit8                 ����ģʽ�£� ֹͣ��   ������ͬ��λ��ģʽ/�ٶ�ģʽ�Ӱ������Ը�λ
	bool OP;                     //bit9     1��ͨѶ����
	bool res1:6;                 //bit10-bit15  Ԥ��
}CONTROLWORD_BITS;

typedef union {
	CONTROLWORD_BITS bits;
	UINT16 all;
}CONTROLWORD;

typedef struct {
    bool TouchProbe1On:1;           //bit0 1������1ͨ��                   0:�ر�1ͨ��
    bool TouchProbe1Continuous:1;   //bit1 1:����
    bool Probe1ZPulse:1;             //bit2 1:1ͨ��Z����
    bool res0:1;                    //bit3 Ԥ��
    bool Probe1PositiveEnable:1;    //bit4 1���������ؽ���1ͨ������
    bool Probe1NegatibeEnable:1;    //bit5 1�����½��ؽ���1ͨ������
    bool res1:2;                    //bit6-7 Ԥ��
    bool TouchProbe2On:1;           //bit8 1:����ͨ��2     0���ر�2ͨ��
    bool Probe2Continuous:1;        //bit9 1:����
    bool Probe2ZPulse:1;            //bit10 1��ͨ��2z����
    bool res2:1;                    //bit11 Ԥ��
    bool Probe2PositiveEnable:1;    //bit12 1���������ؽ���2ͨ������
    bool Probe2NegatibeEnable:1;    //bit13 1�����½��ؽ���2ͨ������
    bool res3:2;                    //bit14-15 Ԥ��
}TOUCHPROBEFUNCTION_BITS;

typedef union {
    TOUCHPROBEFUNCTION_BITS bits;
    uint16_t all;
}TOUCHPROBEFUNCTION;

//CPU2 TO CPU1
typedef struct  {
	 FLAG Flags;            //
	 CONTROLWORD ControlWord;//x6040:������
	uint16_t ModesOfOperation;//x6060:����ģʽ1��Profile λ�ÿ���ģʽ��2���ٶȿ���ģʽ 3��Profile �ٶȿ���ģʽ 4��Profileת�ؿ���ģʽ  6��ԭ��ع�λ�ÿ���ģʽ 7������λ�ÿ���ģʽ  8��ͬ������λ��ģʽ 9��ͬ�������ٶ�ģʽ 10��ͬ������ת��ģʽ
	uint16_t SyncType;//2:ͬ�����з�ʽ
	TOUCHPROBEFUNCTION TouchProbeFunction;//������
	uint16_t res1;                //����
	uint32_t TargetPosition;//Ŀ��λ��
	uint32_t TargetVelocity;//Ŀ���ٶ�
	uint32_t TargetTorque;//Ŀ��ת��
	uint32_t GDCIndex_Up;//�ϴ�������������16λΪ����������16λ��������
	uint32_t GDCIndex_Download;//���ز�����������16λΪ����������16λ��������
	uint32_t GDCIndexValue_Download;//���ز���ֵ
	uint32_t CycleTime;//ͨѶ����
	uint32_t DC2DCValue;//����DC�ж�ʱ����
}GDC_WR,*pGDCWR;

extern GDC_WR CPU2_CPU1;
//

#endif /* USER_GDCV05_CPU2RAM_H_ */

//��������ͨѶ ÿ��������������������Ĭ��������ֵΪ0
