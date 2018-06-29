
/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "GDC16.h"
#define    _MCIHWF2837XD_ 1
#include <mcihwf2837xd.h>
#undef _MCIHW_
#define    _MCIHW_ 0

extern uint16_t isrfuncLoadStart;
extern uint16_t isrfuncLoadEnd;
extern uint16_t isrfuncRunStart;
extern uint16_t isrfuncLoadSize;

/////////////////////////////////////////////////////////////////////////////////////////
/**
\return     0 if initialization was successful

 \brief    This function initialize the EtherCAT Slave Interface.
*////////////////////////////////////////////////////////////////////////////////////////

uint16_t f2837xd_Init(void)
{
    DINT;
    InitPieCtrl();
    EALLOW;
	IER = 0x0000;
	IFR = 0x0000;
	EDIS;
   InitPieVectTable();
   // Wait until Shared RAM is available.
   while(!MemCfgRegs.GSxMSEL.bit.MSEL_GS15)
   {
   }
	//FLASH程序搬运
	if(RAM_FLASH==1)
	{
		memcpy(&isrfuncRunStart, &isrfuncLoadStart, (uint32_t)&isrfuncLoadSize);
//		InitFlash();
	}
   EALLOW;
   PieVectTable.XINT1_INT = &xint1_irq_isr;
//   PieVectTable.XINT2_INT = &xint2_irq_isr;
   PieVectTable.XINT3_INT = &xint3_irq_isr;//同步中断Sync0
   EDIS;

   InitCpuTimers();

// Enable XINT1  in the PIE: Group 1 interrupt 4 & 5
// Enable INT1 which is connected to WAKEINT:

   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
   PieCtrlRegs.PIEIER1.bit.INTx4 = 1;          // Enable PIE Group 1 INT5 XINT2 IRQ
//   PieCtrlRegs.PIEIER1.bit.INTx5 = 1;
   PieCtrlRegs.PIEIER12.bit.INTx1 = 1;       //是能同步中断XINT3

   IER |= M_INT1;                              // Enable CPU INT1
   IER |= M_INT12;
   EINT;                                       // Enable Global Interrupts

//Configure to run EMIF1 on full Rate (EMIF1CLK = CPU1SYSCLK/2)
  EALLOW;
  ClkCfgRegs.PERCLKDIVSEL.bit.EMIF1CLKDIV = 0x1;
  ClkCfgRegs.PERCLKDIVSEL.bit.EMIF2CLKDIV = 0x1;
  EDIS;

//   EALLOW;
// GPIO84 inputs IRQ signal
//   GpioCtrlRegs.GPCMUX2.bit.GPIO84 = 0;         //GPIO84
//   GpioCtrlRegs.GPCDIR.bit.GPIO84 = 0;          //input
//   GpioCtrlRegs.GPCQSEL2.bit.GPIO84 = 0;       //
//   GpioCtrlRegs.GPCCTRL.bit.QUALPRD3 = 0xFF;   //  GPIO 84 Each sampling window
                                                     // is 510*SYSCLKOUT
//   EDIS;

  // GPIO84 is XINT2 IRQ,
//   GPIO_SetupXINT2Gpio(84);//IRQ GPIO84


  EALLOW;
  // Configure XINT1
   XintRegs.XINT1CR.bit.POLARITY = 1;          //up edge interrupt
   XintRegs.XINT1CR.bit.ENABLE = 1;            //Enable XINT1
   // Configure XINT2
//    XintRegs.XINT2CR.bit.POLARITY = 0;          //up edge interrupt
//    XintRegs.XINT2CR.bit.ENABLE = 1;            //Enable XINT2
   // Configure XINT3
   XintRegs.XINT3CR.bit.POLARITY = 1;          //up edge interrupt
   XintRegs.XINT3CR.bit.ENABLE = 1;            //Enable XINT3
   EDIS;


//对EMIF1进行配置
  EALLOW;
//  Emif1ConfigRegs.EMIF1MSEL.all = (uint32_t) 0x93A5CE72;//CPU2上需要修改
  // Disable Access Protection (CPU_FETCH/CPU_WR/DMA_WR)
  Emif1ConfigRegs.EMIF1ACCPROT0.all = 0x0;
  // Commit the configuration related to protection. Till this bit remains set
  // content of EMIF1ACCPROT0 register can't be changed.
  Emif1ConfigRegs.EMIF1COMMIT.all = 0x0;
  // Lock the configuration so that EMIF1COMMIT register can't be changed any more.
  Emif1ConfigRegs.EMIF1LOCK.all = 0x0;
//配置EMIF管脚
//  setup_emif1_pinmux_async_16bit_option2(GPIO_MUX_CPU2);
  //Configure the access timing for CS3 space
  Emif1Regs.ASYNC_CS3_CR.all =  (EMIF_ASYNC_ASIZE_16  	|
								 EMIF_ASYNC_TA_1 		|	// Wr to Rd turnaround
								 EMIF_ASYNC_RHOLD_6 	|	//
								 EMIF_ASYNC_RSTROBE_32 	|	//
								 EMIF_ASYNC_RSETUP_6	|	//
								 EMIF_ASYNC_WHOLD_2 	|	//
								 EMIF_ASYNC_WSTROBE_8 	|	//
								 EMIF_ASYNC_WSETUP_4	|
								 EMIF_ASYNC_EW_ENABLE	|	// EMIF_ASYNC_EW_DISABLE
								 EMIF_ASYNC_SS_DISABLE		// Strobe Select Mode Disable.
  		  	  	  	  	  	  	);
  Emif1Regs.ASYNC_WCCR.bit.WP0 = 1;             // Active-high Wait Polarity for EM1WAIT.
  Emif1Regs.ASYNC_WCCR.bit.MAX_EXT_WAIT = 0x1;
  EDIS;

  EALLOW;
  //CpuTimer0Regs.TCR.bit.TIE = 1;
  CpuTimer0Regs.TCR.bit.TSS = 0;	//start timer
  EDIS;

//	DELAY_US(500 * 1000);

    /* we have to wait here, until the ESC is started */
//    uint16_t right=0,error1=0,error2=0,error3=0,i;
//    for(i=0;i<0xfff;i+=2)
//    {
//        ESC_writeWordNonISR(0x00aa,(0x1000+i));
//        uint16_t value = ESC_readWordNonISR(0x1000+i);
//        if(value == 0x00aa)
//        {
//            right++;
//        }
//        else if(value == 0xaaaa)
//        {
//            error1++;
//        }
//        else if(value == 0x0000)
//        {
//            error2++;
//        }
//        else
//        {
//            error3++;
//        }
//    }
//    ESC_writeWordNonISR(0xaaaa,0x1002);
//    uint16_t value = ESC_readWordNonISR(0x1002);


    return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    Interrupt service routine for the interrupts from the EtherCAT Slave Controller
*////////////////////////////////////////////////////////////////////////////////////////
//时间中断

uint32_t ESC_getTimer(void)
{
    return ~ ((uint32_t)(CpuTimer0Regs.TIM.all));
}

//去除时间中断，将时间中断加入主循环中
uint32_t ESC_timerIncPerMilliSec(void)
{
    return (uint32_t) 2000000UL; //at 200MHz
}

void ESC_clearTimer(void)
{
    CpuTimer0Regs.TIM.all = 0;
}

#ifdef RAM_FLASH
#pragma CODE_SECTION(ESC_readWordNonISR, "isrfuncs");
#endif
uint16_t ESC_readWordNonISR(uint16_t offset)
{

	DINT;
	uint16_t value1=0,value=0,i;
	for(i=0;i<26;i++)
	{
		value1 = ((((volatile uint16_t *)0x300000)[((offset)>>1)]));
		value = value | value1;
	}
	EINT;
	return value;
}

#ifdef RAM_FLASH
#pragma CODE_SECTION(ESC_writeWordNonISR, "isrfuncs");
#endif
void ESC_writeWordNonISR(uint16_t WordValue, uint16_t Address)
{
	DINT;
	do
	{

	}while(Emif1ConfigRegs.EMIF1MSEL.bit.MSEL_EMIF1 == 1);
	EALLOW;
	Emif1ConfigRegs.EMIF1MSEL.all = 0x93A5CE72;
	EDIS;
	((((volatile uint16_t *)0x300000)[((Address)>>1)]) = (WordValue));
	EALLOW;
	Emif1ConfigRegs.EMIF1MSEL.all = 0x93A5CE70;
	EDIS;
	EINT;
}

/** @} */
