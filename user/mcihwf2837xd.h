
#ifndef MCIHWF2837XD_H_
#define MCIHWF2837XD_H_


/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include <string.h>
#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include <stdlib.h>

#define ECAT_TIMER_INC_P_MS   ESC_timerIncPerMilliSec()
/*-----------------------------------------------------------------------------------------
------
------    Global functions
------
-----------------------------------------------------------------------------------------*/
extern interrupt void  xint1_irq_isr(void);
//extern interrupt void xint2_irq_isr(void);
extern interrupt void  xint3_irq_isr(void);
extern uint16_t f2837xd_Init(void);
extern uint32_t ESC_getTimer();
extern void ESC_clearTimer(void);
extern uint32_t ESC_timerIncPerMilliSec(void);
extern uint16_t ESC_readWordNonISR(uint16_t offset);
extern void ESC_writeWordNonISR(uint16_t WordValue, uint16_t Address);
extern void setup_emif1_pinmux_async_16bit_option2(Uint16 cpu_sel); // EMIF driver call

#endif /* MCIHWF2837XD_H_ */
/** @}*/
