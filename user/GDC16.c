/**
1、	占用的资源
a.中断:GPIO84 输入引脚、上升沿有效、XINT2
b.使用XMIF1 片选为CS3 读、写、忙、16位数据线、14位地址线
c.主循环中使用定时器Timer0，每隔1ms，进行清零，重新计数
2、user文件夹下为外部接口函数定义文件
	GDC16.c:主函数文件
mcihwf2837xd.c：对F2837xd初始化、管脚、中断定义
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
/////////////////////////////////////////////////////////////////////////////////////////
/** 主函数
*////////////////////////////////////////////////////////////////////////////////////////
void main(void)
{
//	GDC_WR* v = &CPU2_CPU1;
    UINT16 u16PdiCtrl = 0;
    count = 0;
	f2837xd_Init();//初始化F28377D
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

//初始化时和通讯处于初始化状态
void InitRAM(void)
{
    GDC_WR* v = &CPU2_CPU1;
    memset(&CPU2_CPU1,0,sizeof(CPU2_CPU1));
    v->ModesOfOperation = 8;
    v->CycleTime = 2000;
    v->SyncType = 2;
    v->DC2DCValue = 2000;
}
//周期性通讯往CPU1写入数据
#ifdef RAM_FLASH
#pragma CODE_SECTION(Output_GDCmapping, "isrfuncs");
#endif
void Output_GDCmapping(UINT16* pData)
{
	GDC_WR* v = &CPU2_CPU1;
//	data1 = v->Flags.bits.CycleOrder;
	switch ((sRxPDOassign.aEntries[0] & 0x000F))
    {
        case 1:    //csp RxPDO    entries
            {
            TCiA402PDO1601 *pOutputs = (TCiA402PDO1601 *)pData;
            v->ControlWord.all = pOutputs->ObjControlWord;
            v->SetTarget = pOutputs->ObjTargetPosition;
            v->ModesOfOperation = 8;
            //中间隔离
            LocalAxes.Objects.objControlWord = pOutputs->ObjControlWord;
            LocalAxes.Objects.objTargetPosition = pOutputs->ObjTargetPosition;

            }
            break;
        case 2:    //csv RxPDO    entries
            {
            TCiA402PDO1602 *pOutputs = (TCiA402PDO1602 *)pData;
            v->ControlWord.all = pOutputs->ObjControlWord;
            v->SetTarget    = pOutputs->ObjTargetVelocity;
            v->ModesOfOperation = 9;
            //中间隔离
            LocalAxes.Objects.objControlWord = pOutputs->ObjControlWord;
            LocalAxes.Objects.objTargetVelocity    = pOutputs->ObjTargetVelocity;

            }
            break;
        case 3:    //cst RxPDO    entries
            {
            TCiA402PDO1603 *pOutputs = (TCiA402PDO1603 *)pData;
            v->ControlWord.all = pOutputs->ObjControlWord;
            v->SetTarget    = pOutputs->ObjTargetTorque;
            v->ModesOfOperation = 10;
            //中间隔离
            LocalAxes.Objects.objControlWord = pOutputs->ObjControlWord;
            LocalAxes.Objects.objTargetTorque    = pOutputs->ObjTargetTorque;
            }
            break;
      }
	v->Flags.bits.CycleOrder = !(v->Flags.bits.CycleOrder);
}
#ifdef RAM_FLASH
#pragma CODE_SECTION(Input_GDCmapping, "isrfuncs");
#endif
//周期性通讯，从CPU1中读参数
void Input_GDCmapping(UINT16* pData)
{
	GDC_R* v = &CPU1_CPU2;
	GDC_WR* v2 = &CPU2_CPU1;
	{
	    switch ((sTxPDOassign.aEntries[0]& 0x000F))
	    {
	    case 1://copy csp TxPDO entries
	        {
	            TCiA402PDO1A01 *pInputs = (TCiA402PDO1A01 *)pData;
	            pInputs->ObjStatusWord = v->StatusWord.all;
	            pInputs->ObjPositionActualValue = v->PositionActualValue;
	            //中间做了个隔离，模拟CPU1对CIA402控制
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
	            //中间隔离
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
	            //中间隔离，模拟运行
                pInputs->ObjStatusWord = LocalAxes.Objects.objStatusWord;
                pInputs->ObjPositionActualValue = LocalAxes.Objects.objPositionActualValue;
                pInputs->ObjTorqueActualValue = LocalAxes.Objects.objTorqueActualValue;

	        }
	        break;
	    }    //switch TXPDO entry
	}
}

//非周期性通信，读相应参数的值
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
//IRQ中断
interrupt void xint1_irq_isr(void)
{
	PDI_Isr();
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

#ifdef RAM_FLASH
#pragma CODE_SECTION(xint3_irq_isr, "isrfuncs");
#endif
//IRQ中断
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


//调试参数 bDcRunning
//bSmSyncSequenceValid


/** @} */


