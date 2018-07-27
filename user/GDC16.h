/**
 * \addtogroup GDC16 GDC16
 * @{
 */

/**
\file GDC16.h
\brief GDC16 function prototypes and defines

\version 1.0.0.11
 */

 
 #ifndef _GDC16_H_
#define _GDC16_H_


/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#define PROTO extern
#define RAM_FLASH 1 //0--RAM,1--FLASH
#define FLASH_FLAG 1  //FLASH刷写标记


#include "F28x_Project.h"
#include "F2837xD_Ipc_drivers.h"
#include "ecatappl.h"
#include "ecatslv.h"
#include "ecat_def.h"
#include "mcihwf2837xd.h"
#include "ecatcoe.h"
#include "esc.h"
#include "mailbox.h"
#include "GDCV05_cpu2ram.h"
#include "objdef.h"
#include "cia402appl.h"
#include "coeappl.h"
#include "sdoserv.h"
#include "GDC_PV1_0.h"


extern uint16_t count;//对同步中断进行计数
extern uint16_t Data_input1;//测试写
extern uint16_t Data_input2;//测试写
extern uint16_t Data_input3;//测试写
extern uint16_t Data_input4;

extern void Output_GDCmapping(UINT16* pData);
extern void Input_GDCmapping(UINT16* pData);
extern void Shared_Ram_cpu2_WR_Upload(UINT16 index,UINT16 subindex);
extern void InitRAM(void);
#endif //_GDC16_H_

/** @}*/

