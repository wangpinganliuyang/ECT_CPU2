/**
1��	ռ�õ���Դ
a.�ж�:GPIO84 �������š���������Ч��XINT2
b.ʹ��XMIF1 ƬѡΪCS3 ����д��æ��16λ�����ߡ�14λ��ַ��
c.��ѭ����ʹ�ö�ʱ��Timer0��ÿ��1ms���������㣬���¼���
2��user�ļ�����Ϊ�ⲿ�ӿں��������ļ�
	GDC16.c:�������ļ�
mcihwf2837xd.c����F2837xd��ʼ�����ܽš��ж϶���
*/


/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "GDC16.h"
GDC_R  CPU1_CPU2;
GDC_WR CPU2_CPU1;
#pragma DATA_SECTION(CPU1_CPU2,"SHARERAMGS14");
#pragma DATA_SECTION(CPU2_CPU1,"SHARERAMGS15");
uint16_t count;
uint16_t CountFault;
uint16_t CountRest;
uint16_t Data_input1;
uint16_t Data_input2;
uint16_t Data_input3;
uint16_t Data_input4;
/////////////////////////////////////////////////////////////////////////////////////////
/** ������
*////////////////////////////////////////////////////////////////////////////////////////
void main(void)
{
//	GDC_WR* v = &CPU2_CPU1;
    UINT16 u16PdiCtrl = 0;
    count = 0;
    CountFault = 0;
    CountRest = 0;
    Count1C12 = 0;
    Count1C13 = 0;
    Count6060 = 0;
    Count6061 = 0;
    CountGdub = 0;
    Data_input1 = 0;
    Data_input2 = 0;
    Data_input3 = 0;
    Data_input4 = 0;

	f2837xd_Init();//��ʼ��F28377D
    do
    {
   	   u16PdiCtrl = ESC_readWordNonISR(ESC_PDI_CONTROL_OFFSET);
     } while ((u16PdiCtrl & 0xFF) != 0x8 );
    InitRAM();
    MainInit();
    CiA402_Init();
    GDC_PV1_0_Init();
    Gdc_Para_AddObject();
//    APPL_GenerateMapping(&nPdInputSize,&nPdOutputSize);
    bRunApplication = TRUE;
    do
    {
        MainLoop();
    } while (bRunApplication == TRUE);
    Gdc_Para_RemObject();
    CiA402_DeallocateAxis();
}

//��ʼ��ʱ��ͨѶ���ڳ�ʼ��״̬
void InitRAM(void)
{
    GDC_WR* v = &CPU2_CPU1;
    memset(&CPU2_CPU1,0,sizeof(CPU2_CPU1));
    v->ModesOfOperation = 8;
    v->CycleTime = 2000;
    v->SyncType = 2;
    v->DC2DCValue = 2000;
    v->ControlWord.all = 0x0004;
}
//������ͨѶ��CPU1д������
#ifdef RAM_FLASH
#pragma CODE_SECTION(Output_GDCmapping, "isrfuncs");
#endif
void Output_GDCmapping(UINT16* pData)
{
	GDC_WR* v = &CPU2_CPU1;
	GDC_R* v1 = &CPU1_CPU2;
//	data1 = v->Flags.bits.CycleOrder;
	switch ((sRxPDOassign.aEntries[0] & 0x000F))
    {
	    case 0:    //csp/csv RxPDO    entries
            {
                TCiA402PDO1600 *pOutputs = (TCiA402PDO1600 *)pData;
                v->ControlWord.all = pOutputs->ObjControlWord;
                v->ControlWord.all |= 0x0200;
                v->TargetPosition = pOutputs->ObjTargetPosition;
                v->TargetVelocity = pOutputs->ObjTargetVelocity;
                v->ModesOfOperation = pData[5];
                v->TouchProbeFunction.all = (((uint16_t)pData[5])>>8) + ((((uint16_t)pData[6]) &0x00FF)<<8);
                //�м����
                LocalAxes.Objects.objControlWord = (pOutputs->ObjControlWord);
                LocalAxes.Objects.objTargetPosition = (pOutputs->ObjTargetPosition);
                LocalAxes.Objects.objTargetVelocity    = (pOutputs->ObjTargetVelocity);
                LocalAxes.Objects.objModesOfOperation = ((pOutputs->ObjModesOfOperation & 0x00FF));
            }
            break;

        case 1:    //csp RxPDO    entries
            {
            TCiA402PDO1601 *pOutputs = (TCiA402PDO1601 *)pData;
            v->ControlWord.all = pOutputs->ObjControlWord;
            v->ControlWord.all |= 0x0200;
            v->TargetPosition = pOutputs->ObjTargetPosition;
            v->ModesOfOperation = 8;
            //�м����
            LocalAxes.Objects.objControlWord = pOutputs->ObjControlWord;
            LocalAxes.Objects.objTargetPosition = pOutputs->ObjTargetPosition;

            }
            break;
        case 2:    //csv RxPDO    entries
            {
            TCiA402PDO1602 *pOutputs = (TCiA402PDO1602 *)pData;
            v->ControlWord.all = pOutputs->ObjControlWord;
            v->ControlWord.all |= 0x0200;
            v->TargetVelocity    = (pOutputs->ObjTargetVelocity) ;
            v->TargetVelocity    = ((uint32_t)((v->TargetVelocity) * 5592 ));
            v->ModesOfOperation = 9;
            //�м����
            LocalAxes.Objects.objControlWord = pOutputs->ObjControlWord;
            LocalAxes.Objects.objTargetVelocity    = pOutputs->ObjTargetVelocity;

            }
            break;
        case 3:    //cst RxPDO    entries
            {
            TCiA402PDO1603 *pOutputs = (TCiA402PDO1603 *)pData;
            v->ControlWord.all = pOutputs->ObjControlWord;
            v->ControlWord.all |= 0x0200;
            v->TargetTorque    = pOutputs->ObjTargetTorque;
            v->ModesOfOperation = 10;
            //�м����
            LocalAxes.Objects.objControlWord = pOutputs->ObjControlWord;
            LocalAxes.Objects.objTargetTorque    = pOutputs->ObjTargetTorque;
            }
            break;
      }
    v->ControlWord.all |= 0x0004;
	v->Flags.bits.CycleOrder = !(v->Flags.bits.CycleOrder);
}
#ifdef RAM_FLASH
#pragma CODE_SECTION(Input_GDCmapping, "isrfuncs");
#endif
//������ͨѶ����CPU1�ж�����
void Input_GDCmapping(UINT16* pData)
{
	GDC_R* v = &CPU1_CPU2;
	GDC_WR* v2 = &CPU2_CPU1;
	{
	    switch ((sTxPDOassign.aEntries[0]& 0x000F))
	    {
        case 0:    //copy csp/csv TxPDO entries
            {
                TCiA402PDO1A00 *pInputs = (TCiA402PDO1A00 *)pData;
                pInputs->ObjStatusWord = v->StatusWord.all;
                pInputs->ObjPositionActualValue = v->PositionActualValue;
                pInputs->ObjVelocityActualValue = v->VelocityActualValue;
                pInputs->ObjTorqueActualValue = ((uint16_t)v->TorqueActualValue);
                pInputs->ObjModesOfOperationDisplay = ((uint16_t)v->ModesOfOperationDisplay);
                pInputs->ObjTouchProbestatus = v->TouchProbestatus.all;
                pInputs->ObjTouchProbesP = v->TouchProbesP;

//                pInputs->ObjStatusWord = (LocalAxes.Objects.objStatusWord);
//                pInputs->ObjPositionActualValue = (LocalAxes.Objects.objPositionActualValue);
//                pInputs->ObjVelocityActualValue = (LocalAxes.Objects.objVelocityActualValue);
//                pInputs->ObjTorqueActualValue = LocalAxes.Objects.objTorqueActualValue;
//                pInputs->ObjModesOfOperationDisplay = ((LocalAxes.Objects.objModesOfOperationDisplay & 0x00FF));
            }
            break;
	    case 1://copy csp TxPDO entries
	        {
	            TCiA402PDO1A01 *pInputs = (TCiA402PDO1A01 *)pData;
	            pInputs->ObjStatusWord = v->StatusWord.all;
	            pInputs->ObjPositionActualValue = v->PositionActualValue;
	            //�м����˸����룬ģ��CPU1��CIA402����
//                pInputs->ObjStatusWord = LocalAxes.Objects.objStatusWord;
//                pInputs->ObjPositionActualValue = LocalAxes.Objects.objPositionActualValue;

	        }
	        break;
	    case 2://copy csv TxPDO entries
	        {
	            TCiA402PDO1A02 *pInputs = (TCiA402PDO1A02 *)pData;
	            pInputs->ObjStatusWord = v->StatusWord.all;
	            pInputs->ObjPositionActualValue = v->PositionActualValue;
	            pInputs->ObjVelocityActualValue = v->VelocityActualValue;
	            //�м����
//                pInputs->ObjStatusWord = LocalAxes.Objects.objStatusWord;
//                pInputs->ObjPositionActualValue = LocalAxes.Objects.objPositionActualValue;
//                pInputs->ObjVelocityActualValue = LocalAxes.Objects.objVelocityActualValue;

	        }
	        break;
	    case 3://copy cst TxPDO entries
	        {
	            TCiA402PDO1A03 *pInputs = (TCiA402PDO1A03 *)pData;
//	            pInputs->ObjStatusWord = v->StatusWord.all;
//	            pInputs->ObjPositionActualValue = v->PositionActualValue;
//	            pInputs->ObjTorqueActualValue = v->TorqueActualValue;
	            //�м���룬ģ������
                pInputs->ObjStatusWord = LocalAxes.Objects.objStatusWord;
                pInputs->ObjPositionActualValue = LocalAxes.Objects.objPositionActualValue;
                pInputs->ObjTorqueActualValue = LocalAxes.Objects.objTorqueActualValue;

	        }
	        break;
	    }    //switch TXPDO entry
	}
}

//��������ͨ�ţ�����Ӧ������ֵ
void Shared_Ram_cpu2_WR_Upload(UINT16 index,UINT16 subindex)
{
	GDC_WR* v = &CPU2_CPU1;
	v->GDCIndex_Up = (((UINT32)index) - 0x2000) + (((UINT32)subindex)<<16);
	v->Flags.all |= 0x0004;
	count = 0;
}


#ifdef RAM_FLASH
#pragma CODE_SECTION(xint1_irq_isr, "isrfuncs");
#endif
//IRQ�ж�
interrupt void xint1_irq_isr(void)
{
	PDI_Isr();
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

#ifdef RAM_FLASH
#pragma CODE_SECTION(xint3_irq_isr, "isrfuncs");
#endif
//IRQ�ж�
interrupt void xint3_irq_isr(void)
{
    count++;
    GDC_WR* v = &CPU2_CPU1;
    if(!bSmSyncSequenceValid)
    {
        InitRAM();
    }
    Sync0_Isr();
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
}


//���Բ��� bDcRunning
//bSmSyncSequenceValid


/** @} */


