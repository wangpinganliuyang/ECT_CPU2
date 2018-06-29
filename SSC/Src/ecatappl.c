/**
\addtogroup EcatAppl EtherCAT application
@{
*/


/**
\file ecatappl.c
\author EthercatSSC@beckhoff.com
\brief Implementation
This file contains the Process Data interface

\version 5.11

<br>Changes to version V5.10.1:<br>
V5.11 COE3: change 0x10F3.2 (Sync Error limit) from UINT32 to UINT16 (according to the ETG.1020)<br>
V5.11 ECAT1: update EEPROM access reset operation<br>
V5.11 ECAT10: change PROTO handling to prevent compiler errors<br>
V5.11 ECAT11: create application interface function pointer, add eeprom emulation interface functions<br>
V5.11 ECAT2: update EEPROM access retry cycle (add 10ms delay between two retry cycles)<br>
V5.11 ECAT3: handle bus cycle calculation for input/output only devices and create warning diag message only if calculation failed<br>
V5.11 ECAT4: enhance SM/Sync monitoring for input/output only slaves<br>
V5.11 ECAT6: add function to calculate bus cycle time<br>
V5.11 ECAT8: call PDO_InputMapping only once if DC is enabled and COE is not supported<br>
V5.11 EEPROM1: fix compiler error during pEEPROM pointer initialization<br>
V5.11 EEPROM2: write Station alias value to EEPROM data register on EEPROM reload command<br>
V5.11 EEPROM3: clear EEPROM error bits<br>
V5.11 EEPROM4: prevent the variable in the EEPROM busy loop to be removed by the compiler<br>
V5.11 ESM7: "add Sync define for 0x22 (""SYNCTYPE_SM2_SYNCHRON""), support value 0x22 for 0x1C33.1 (SM2 sync)"<br>
<br>Changes to version V5.01:<br>
V5.10 COE1: Define one entry description for all 0x1C3x objects and change data type of SI11,12,13 to UINT16 (according ETG.1020)<br>
V5.10 ECAT1: Correct calculation of blinking and flashing sequence<br>
V5.10 ECAT13: Update Synchronisation handling (FreeRun,SM Sync, Sync0, Sync1)<br>
              Compare DC UINT configuration (by ESC Config data) vs. DC activation register settings<br>
              Update 0x1C3x entries<br>
V5.10 ECAT2: Prevent EEPROM data null pointer access (if the pointer is null an command error is set)<br>
             EEPROM emulation return command error if unknown command was received<br>
V5.10 ECAT4: Update alignment marco for 8 to 15 bit alignments (16 and 32 Bit controllers)<br>
             Bugfix calculate LED blink frequency<br>
V5.10 ECAT7: Add "bInitFinished" to indicate if the initialization is complete<br>
V5.10 HW2: Change HW_GetTimer return value to UINT32<br>
<br>Changes to version V5.0:<br>
V5.01 APPL3: Include library demo application<br>
V5.01 ESC1: Change ESC access function (if EEPROM Emulation is active)<br>
V5.01 ESC2: Add missed value swapping<br>
<br>Changes to version V4.40:<br>
V5.0 TEST1: Add test application. See Application Note ET9300 for more details.<br>
V5.0 ECAT2: Application specific functions are moved to application files.<br>
V5.0 ECAT3: Global dummy variables used for dummy ESC operations.<br>
V5.0 ESC1: ESC 32Bit Access added.<br>
V5.0 ESC3: Add EEPROM emulation support.<br>
V5.0 ESM3: Handling pending ESM transitions.<br>
V5.0 ESC5: Enhance EEPROM access handling.<br>
V5.0 PDO1: AL Event flags are not rechecked in PDO_OutputMappping(). (Already checked before call function)<br>
V5.0 SYNC1: Add missed SM event indication (0x1C32/0x1C33 SI11).<br>
<br>Changes to version V4.30:<br>
V4.40 DIAG1: add diagnosis message support<br>
V4.40 PDO1: merge content of HW_InputMapping (spihw.c/mcihw.c) to PDO_InputMapping. merge content of HW_OutputMapping (spihw.c/mcihw.c) to PDO_OutputMapping.<br>
V4.40 PDO2: Generic process data length calculation<br>
V4.40 ECAT2: call cyclic CheckIfLocalError() to check the local flags<br>
V4.40 HW0: Generic hardware access functions. Add Function (PDI_Isr()), content merged from spihw.c and mcihw.c.<br>
V4.40 WD1: define (ESC_SM_WD_SUPPORTED) to choose ESC SyncManager watchdog or local watchdog<br>
V4.40 ESM2: Change state transition behaviour from SafeOP to OP<br>
V4.40 TIMER1: Change bus cycle time calculation and trigger of ECAT_CheckTimer() if ECAT_TIMER_INT is reset<br>
V4.40 HW1: Add support for fc1100 hardware<br>
<br>Changes to version V4.20:<br>
V4.30 EL9800: EL9800_x cyclic application is moved to el9800.c<br>
V4.30 OBJ 3:    add object dictionary initialization<br>
V4.30 SYNC: add CalcSMCycleTime() (calculation of bus cycle time); change synchronisation control functions<br>
V4.30 PDO: include PDO specific functions (moved from coeappl.c).<br>
               xxx_InputMapping(); xxx_OutputMapping(); xxx_ReadInputs(); xxx_ResetOutputs(); xxx_Application()<br>
V4.30 CiA402: Add CiA402_StateMachine() and CiA402_Application() call<br>
V4.20 DC 1: Add DC pending Statemachine handling<br>
V4.20 PIC24: Add EL9800_4 (PIC24) required source code<br>
V4.20 LED 1: Modified LED Handling<br>
V4.11 APPL 1: The checkWatchdog() function should not called in checkTimer() if this function is triggered by an Interrupt<br>
<br>Changes to version V4.08:<br>
V4.10 LED 1: The handling of the EtherCAT-Error-LED was added<br>
V4.10 AOE 3: The AoE fragment size has to be initialized during the state transition<br>
                 from INIT to PREOP<br>
<br>Changes to version V4.07:<br>
V4.08 LED 1: The handling of the EtherCAT-LED can be (de-)selected by the switch LEDS_SUPPORTED<br>
                 because the ET1100 and ET1200 have an output port which could be connected directly.<br>
<br>Changes to version V4.01:<br>
V4.02 ECAT 1: The watchdog timer variables shall be initialized.<br>
<br>Changes to version V4.00:<br>
V4.01 APPL 1: If the application is running in synchron mode and no SM event<br>
              is received, the application should be called from the main loop<br>
V4.01 APPL 2: In FreeRun mode the output should only be copied if the slave is in OP<br>
<br>Changes to version V3.20:<br>
V4.00 APPL 1: The watchdog checking should be done by a microcontroller<br>
                 timer because the watchdog trigger of the ESC will be reset too<br>
                 if only a part of the sync manager data is written<br>
V4.00 APPL 2: The setting of EtherCAT state LEDs were included<br>
V4.00 APPL 3: The outputs should be reset to a safe state,<br>
                   when the state OP is left<br>
V4.00 APPL 4: An example for the EEPROM access through the ESC is shown in<br>
                   the function APPL_StartMailboxHandler<br>
V4.00 APPL 5: The inputs should be read once when the state transition<br>
                   from PREOP to SAFEOP is made<br>
V4.00 APPL 6: The main function was split in MainInit and MainLoop
*/


/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/

/* ECATCHANGE_END(V5.11) ECAT11*/

#include "GDC16.h"
#define    _ECATAPPL_ 1
#include "ecatappl.h"
#undef _ECATAPPL_
/* ECATCHANGE_START(V5.11) ECAT10*/
/*remove definition of _ECATAPPL_ (#ifdef is used in ecatappl.h)*/
/* ECATCHANGE_END(V5.11) ECAT10*/




/*--------------------------------------------------------------------------------------
------
------    local Types and Defines
------
--------------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------------
------
------    local variables and constants
------
-----------------------------------------------------------------------------------------*/

UINT16   aPdOutputData[3];//�޸ģ�����������ͨѶ�趨
UINT16   aPdInputData[6];//�޸ģ�����֧������ͬ��λ��ģʽ������״̬�ֺ�ʵ��λ�á�//����������ͬ���ٶ�ģʽ

/*variables are declared in ecatslv.c*/
extern VARVOLATILE UINT16    u16dummy;
BOOL bInitFinished = FALSE; /** < \brief indicates if the initialization is finished*/
/*-----------------------------------------------------------------------------------------
------
------    local functions
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    Functions
------
-----------------------------------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////
/**
\brief      This function will copies the inputs from the local memory to the ESC memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
#ifdef RAM_FLASH
#pragma CODE_SECTION(PDO_InputMapping, "isrfuncs");
#endif
void PDO_InputMapping(void)
{
	UINT16 addr = 0;
	UINT16 nPdInputSizei = 0;
	//CPU2��ȡ����
	Input_GDCmapping((UINT16*)aPdInputData);
	//�ڴ˴������޸�
	addr = nEscAddrInputData;
//	for (nPdInputSizei = 0; nPdInputSizei<((nPdInputSize)>>1);nPdInputSizei++)
//	{
//		ESC_writeWordNonISR(aPdInputData[nPdInputSizei], addr);
//		addr += 2;
//	}
	ESC_writeWordNonISR(aPdInputData[0], addr);
	addr +=2;
	ESC_writeWordNonISR(aPdInputData[2], addr);
	addr +=2;
	ESC_writeWordNonISR(aPdInputData[3], addr);
	if(sTxPDOassign.aEntries[0] == 0x1a02)
	{
	    addr +=2;
	    ESC_writeWordNonISR(aPdInputData[4], addr);
	    addr +=2;
	    ESC_writeWordNonISR(aPdInputData[5], addr);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
/**
\brief    This function will copies the outputs from the ESC memory to the local memory
          to the hardware. This function is only called in case of an SM2 
          (output process data) event.
*////////////////////////////////////////////////////////////////////////////////////////
#ifdef RAM_FLASH
#pragma CODE_SECTION(PDO_OutputMapping, "isrfuncs");
#endif
void PDO_OutputMapping(void)
{
	DINT;
	UINT16 iPDO_OUT = 0;
	UINT16 adrPDO= nEscAddrOutputData;
	for(iPDO_OUT=0;iPDO_OUT<((nPdOutputSize+1)>>1);iPDO_OUT++)
	{
		aPdOutputData[iPDO_OUT] = ESC_readWordNonISR(adrPDO);
		adrPDO += 2;
	}
	EINT;
  //��CPU2д����
  Output_GDCmapping((UINT16*) aPdOutputData);
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    This function shall be called every 1ms.
 \brief If the switch ECAT_TIMER_INT is 0, the watchdog control is implemented without using
 \brief interrupts. In this case a local timer register is checked every ECAT_Main cycle
 \brief and the function is triggered if 1 ms is elapsed
 *////////////////////////////////////////////////////////////////////////////////////////

void ECAT_CheckTimer(void)
{
	/*decrement the state transition timeout counter*/
	if(bEcatWaitForAlControlRes &&  (EsmTimeoutCounter > 0))
	{
	    EsmTimeoutCounter--;
	}
	DC_CheckWatchdog();
}


/*ECATCHANGE_END(V5.12) ECAT1*/
void PDI_Isr(void)
{
	if(bEscIntEnabled)
	{
		/* get the AL event register */
		UINT16 ALEvent = ESC_readWordNonISR(ESC_AL_EVENT_OFFSET);//���ܶ�ζ�ȡ������
		if ( ALEvent & PROCESS_OUTPUT_EVENT )
	  {
	  	if(bDcRunning && bDcSyncActive)
	  	{
	  	    /* Reset SM/Sync0 counter. Will be incremented on every Sync0 event*/
	  	    u16SmSync0Counter = 0;
	  	}
	  	if(sSyncManOutPar.u16SmEventMissedCounter > 0)
	  		sSyncManOutPar.u16SmEventMissedCounter--;
	  	sSyncManInPar.u16SmEventMissedCounter = sSyncManOutPar.u16SmEventMissedCounter;
	
	    /* Outputs were updated, set flag for watchdog monitoring */
	    bEcatFirstOutputsReceived = TRUE;
	    /*
	      handle output process data event
	    */
	    if ( bEcatOutputUpdateRunning )
	    {
	    	/* slave is in OP, update the outputs */
	    	PDO_OutputMapping();
	    }
	    else
	    {
	    	/* Just acknowledge the process data event in the INIT,PreOP and SafeOP state */
	    	u16dummy = ESC_readWordNonISR(nEscAddrOutputData);
	    	u16dummy = ESC_readWordNonISR(nEscAddrOutputData+nPdOutputSize-2);
	    }
	  }
	
	  /*
	      Call ECAT_Application() in SM Sync mode
	  */
//	  if (sSyncManOutPar.u16SyncType == SYNCTYPE_SM_SYNCHRON)
//	  {
//	      /* The Application is synchronized to process data Sync Manager event*/
//	      ECAT_Application();
//	  }
	
	  if ( bEcatInputUpdateRunning
	  		&& ((sSyncManInPar.u16SyncType == SYNCTYPE_SM_SYNCHRON) || (sSyncManInPar.u16SyncType == SYNCTYPE_SM2_SYNCHRON))
	  	)
	  {
	  	/* EtherCAT slave is at least in SAFE-OPERATIONAL, update inputs */
	  	PDO_InputMapping();
	  }	
	  /*
	    Check if cycle exceed
	  */
	  /*if next SM event was triggered during runtime increment cycle exceed counter*/
	  ALEvent = ESC_readWordNonISR(ESC_AL_EVENT_OFFSET);
	  if ( ALEvent & PROCESS_OUTPUT_EVENT )
	  {
	  	sSyncManOutPar.u16CycleExceededCounter++;
	  	sSyncManInPar.u16CycleExceededCounter = sSyncManOutPar.u16CycleExceededCounter;
//	  	u16dummy = ESC_readWordNonISR(nEscAddrOutputData);
//	  	u16dummy = ESC_readWordNonISR(nEscAddrOutputData+nPdOutputSize-2);
	  }
	} //if(bEscIntEnabled)
  COE_UpdateSyncErrorStatus();
}
void Sync0_Isr(void)
{
	Sync0WdCounter = 0;
	if(bDcSyncActive)
	{
	
		if ( bEcatInputUpdateRunning )
		{
		    LatchInputSync0Counter++;
		}
		if(u16SmSync0Value > 0)
		{
			/* Check if Sm-Sync sequence is invalid */
			if (u16SmSync0Counter > u16SmSync0Value)
			{
			   /*ECATCHANGE_START(V5.11) COE3*/
			   if ((nPdOutputSize > 0) && (sSyncManOutPar.u16SmEventMissedCounter <= sErrorSettings.u16SyncErrorCounterLimit))
			   {
			      /*ECATCHANGE_END(V5.11) COE3*/
			      sSyncManOutPar.u16SmEventMissedCounter = sSyncManOutPar.u16SmEventMissedCounter + 3;
			   }
			
			   /*ECATCHANGE_START(V5.11) COE3*/
			   if ((nPdInputSize > 0) && (nPdOutputSize == 0) && (sSyncManInPar.u16SmEventMissedCounter <= sErrorSettings.u16SyncErrorCounterLimit))
			   {
			   /*ECATCHANGE_END(V5.11) COE3*/
			 	  sSyncManInPar.u16SmEventMissedCounter = sSyncManInPar.u16SmEventMissedCounter + 3;
			   }
			
			} // if (u16SmSync0Counter > u16SmSync0Value)	       
		  if ((nPdOutputSize == 0) && (nPdInputSize > 0))
		  {
		  	/* Input only with DC, check if the last input data was read*/
				UINT16 ALEvent = ESC_readWordNonISR(ESC_AL_EVENT_OFFSET);
		  	if ((ALEvent & PROCESS_INPUT_EVENT) == 0)
		  	{
		  	   /* no input data was read by the master, increment the sm missed counter*/
		  	   u16SmSync0Counter++;
		  	}
		  	else
		  	{
		  	   /* Reset SM/Sync0 counter*/
		  	   u16SmSync0Counter = 0;
		  	
		  	   sSyncManInPar.u16SmEventMissedCounter = 0;
		  	
		  	}
		  }
		  else if (u16SmSync0Counter <= u16SmSync0Value)
		  {
		     u16SmSync0Counter++;
		  }
		}//SM -Sync monitoring enabled
	  /* Application is synchronized to SYNC0 event*/
	  ECAT_Application();	
	  if ( bEcatInputUpdateRunning 
	     && (LatchInputSync0Value > 0) && (LatchInputSync0Value == LatchInputSync0Counter) ) /* Inputs shall be latched on a specific Sync0 event */
	  {
	  	/* EtherCAT slave is at least in SAFE-OPERATIONAL, update inputs */
	  	PDO_InputMapping();	
	  	if(LatchInputSync0Value == 1)
	  	{
	  	    /* if inputs are latched on every Sync0 event (otherwise the counter is reset on the next Sync1 event) */
	  	    LatchInputSync0Counter = 0;
	  	}
	  } 	
	}
  COE_UpdateSyncErrorStatus();
}

/////////////////////////////////////////////////////////////////////////////////////////
/**

 \brief    This function shall called within a 1ms cycle.
        Set Run and Error Led depending on the Led state

*////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param     pObjectDictionary   Pointer to application specific object dictionary.
                                NULL if no specific object are available.
\return     0 if initialization was successful

 \brief    This function initialize the EtherCAT Sample Code

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 MainInit(void)
{
    UINT16 Error = 0;
/*Hardware init function need to be called from the application layer*/
    /* initialize the EtherCAT Slave Interface */
    ECAT_Init();
    /* initialize the objects */
    COE_ObjInit();

    /*indicate that the slave stack initialization finished*/
    bInitFinished = TRUE;

/*Application Init need to be called from the application layer*/
    return Error;
}


/////////////////////////////////////////////////////////////////////////////////////////
/**

 \brief    This function shall be called cyclically from main

*////////////////////////////////////////////////////////////////////////////////////////

void MainLoop(void)
{
    /*return if initialization not finished */
    if(bInitFinished == FALSE)
        return;
        /* FreeRun-Mode:  bEscIntEnabled = FALSE, bDcSyncActive = FALSE
           Synchron-Mode: bEscIntEnabled = TRUE, bDcSyncActive = FALSE
           DC-Mode:       bEscIntEnabled = TRUE, bDcSyncActive = TRUE */
    if (
        (!bEscIntEnabled || !bEcatFirstOutputsReceived)     /* SM-Synchronous, but not SM-event received */
      && !bDcSyncActive                                               /* DC-Synchronous */
        )
    {
        /* if the application is running in ECAT Synchron Mode the function ECAT_Application is called
           from the ESC interrupt routine (in mcihw.c or spihw.c),
           in ECAT Synchron Mode it should be additionally checked, if the SM-event is received
           at least once (bEcatFirstOutputsReceived = 1), otherwise no interrupt is generated
           and the function ECAT_Application has to be called here (with interrupts disabled,
           because the SM-event could be generated while executing ECAT_Application) */
        if ( !bEscIntEnabled )
        {
            /* application is running in ECAT FreeRun Mode,
               first we have to check, if outputs were received */
        	UINT16 ALEvent = ESC_readWordNonISR(ESC_AL_EVENT_OFFSET);

          if ( ALEvent & PROCESS_OUTPUT_EVENT )
          {
              /* set the flag for the state machine behaviour */
              bEcatFirstOutputsReceived = TRUE;
              if ( bEcatOutputUpdateRunning )
              {
                  /* update the outputs */
                  PDO_OutputMapping();
              }
          }
          else if ( nPdOutputSize == 0 )
          {
              /* if no outputs are transmitted, the watchdog must be reset, when the inputs were read */
              if ( ALEvent & PROCESS_INPUT_EVENT )
              {
                  /* Outputs were updated, set flag for watchdog monitoring */
                  bEcatFirstOutputsReceived = TRUE;
              }
          }
        }

        DINT;
//      ECAT_Application();
        if ( bEcatInputUpdateRunning )
        {
            /* EtherCAT slave is at least in SAFE-OPERATIONAL, update inputs */
           PDO_InputMapping();
        }
        EINT;
    }

    //��ʱ���������ѭ����
    /* there is no interrupt routine for the hardware timer so check the timer register if the desired cycle elapsed*/
    UINT32 CurTimer = (UINT32)ESC_getTimer();
    if(CurTimer>= ECAT_TIMER_INC_P_MS)
    {
        ECAT_CheckTimer();
        ESC_clearTimer();
    }
    /* call EtherCAT functions */
    ECAT_Main();
     /* call lower prior application part */
    COE_Main();
//    CheckIfEcatError();
    if(bEcatInputUpdateRunning)
    {
      CiA402_StateMachine();
    }
}

/*The main function was moved to the application files.*/
/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    ECAT_Application (prev. SSC versions "COE_Application")
 this function calculates and the physical process signals and triggers the input mapping
*////////////////////////////////////////////////////////////////////////////////////////
void ECAT_Application(void)
{
    /*Axis configuration is written in state change from PREOP to SAFEOP
    => trigger CiA402 Application if device is in SAFEOP or OP
    (Motion Controller function is only triggered if DC Synchronisation is active and valid mode of operation is set)*/
    if(bEcatInputUpdateRunning)
    {
        APPL_Application();
    }
/* PDO Input mapping is called from the specific trigger ISR */
}
/** @} */
