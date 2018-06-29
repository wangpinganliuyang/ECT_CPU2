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
	bool ReadySwithOn:1; //1:׼���ÿ���
	bool SwithedOn:1; //1������
	bool OperationEnabl:1; //1:����ʹ��
	bool Fault:1; //1:����
	bool VoltageEnabl:1;//1���ߵ�Դʹ�� DC��
	bool QuickStop:1;//0:���ڼ�ͣ״̬��1����֧�ּ�ͣ��ͣ����û������
	bool SwitchOnDisabl:1;//0:���ڲ��ɽ�ͨ��Դ״̬��
	bool Warning:1;//1:����������
	bool res0:1;//Ԥ��
	bool Remote:1;  //0:��Զ��ģʽ   1��Զ��ģʽ  EtherCATΪԶ��ģʽ
	bool TargetReached:1;   //1:�ﵽĿ��ָ��ڹ켣λ��ģʽ�¡�����ģʽ��
	bool InternalLimitActive:1;  //
	bool res1:4;  //Ԥ��
}STATUSWORD_BITS;

typedef union {
	STATUSWORD_BITS bits;
	uint16_t all;
}STATUSWORD;

//CPU1 TO CPU2
typedef struct {
	 FLAG Flags;        //
	 STATUSWORD StatusWord;//״̬��
	uint16_t ModesOfOperationDisplay;//0x6061���ŷ���ʾ������ģʽ��1���켣λ�ÿ���ģʽ��2���ٶȿ���ģʽ 3���켣�ٶȿ���ģʽ 4���켣ת�ؿ���ģʽ  6��ԭ��ع�λ�ÿ���ģʽ 7���ڲ�λ�ÿ���ģʽ  8��ͬ������λ��ģʽ 9��ͬ�������ٶ�ģʽ 10��ͬ������ת��ģʽ
	uint16_t Res1;
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
	bool SwitchOn:1;   //0-1:��ͨ��Դ��  1-0���жϵ�Դ
	bool EnableVoltage:1;   //0-1:ʹ�ܹ��� ��  1-0��ֹͣ����---ֱ��ĸ�ߵ�ѹʹ��
	bool QucikStop:1;  //1-0:����ֹͣ
	bool EnableOperation:1;  //0-1:ʹ�����У�  1-0:ֹͣ����
	bool res0:3;              //Ԥ��
	bool FaultRest:1;        //��λ����
	bool Halt:1;             //��ͣ
	bool res1:7;              //Ԥ��
}CONTROLWORD_BITS;

typedef union {
	CONTROLWORD_BITS bits;
	UINT16 all;
}CONTROLWORD;


//CPU2 TO CPU1
typedef struct  {
	 FLAG Flags;            //
	 CONTROLWORD ControlWord;//x6040:������
	uint16_t ModesOfOperation;//x6060:����ģʽ1��Profile λ�ÿ���ģʽ��2���ٶȿ���ģʽ 3��Profile �ٶȿ���ģʽ 4��Profileת�ؿ���ģʽ  6��ԭ��ع�λ�ÿ���ģʽ 7������λ�ÿ���ģʽ  8��ͬ������λ��ģʽ 9��ͬ�������ٶ�ģʽ 10��ͬ������ת��ģʽ
	uint16_t SyncType;//0:��������ģʽ��2��SYNC0ͬ����ʽ
	uint32_t SetTarget;//��Ӧ����ģʽ�µ�Ŀ��ֵ
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
