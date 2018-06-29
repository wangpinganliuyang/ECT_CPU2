/**
 * \addtogroup CoE CAN Application Profile over EtherCAT
 * @{
 */

/**
\file coeappl.h
\author EthercatSSC@beckhoff.com

\version 5.11

<br>Changes to version V5.01:<br>
V5.11 ECAT10: change PROTO handling to prevent compiler errors<br>
<br>Changes to version - :<br>
V5.01 : Start file change log
 */
#ifndef _COEAPPL_H_
#define _COEAPPL_H_

/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "objdef.h"

/*---------------------------------------------
-    0x1018
-----------------------------------------------*/
/**
* \brief 0x1018 (Identity) object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
    UINT16   u16SubIndex0; /**< \brief SubIndex 0*/
    UINT32   u32VendorID; /**< \brief EtherCAT vendor ID */
    UINT32   u32Productcode; /**< \brief Product code*/
    UINT32   u32Revision; /**< \brief Revision number*/
    UINT32   u32Serialnumber; /**< \brief Serial number*/
} OBJ_STRUCT_PACKED_END
TOBJ1018;

/*---------------------------------------------
-    0x1C00
-----------------------------------------------*/
/**
* \brief 0x1C00 (Sync manager type) object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
    UINT16   u16SubIndex0; /**< \brief SubIndex 0*/
    UINT16   aEntries[2]; /**< \brief Entry buffer (one for two SyncManagers)*/
} OBJ_STRUCT_PACKED_END
TOBJ1C00;

#define CHECK_DC_OVERRUN_IN_MS      4000 /**<\brief cycle time in ms to check the DC system time for overrun*/


#endif //_COEAPPL_H_

/* ECATCHANGE_START(V5.11) ECAT10*/
#if defined(_COEAPPL_) && (_COEAPPL_ == 1)
/* ECATCHANGE_END(V5.11) ECAT10*/
    #define PROTO
#else
    #define PROTO extern
#endif

/*-----------------------------------------------------------------------------------------
------
------    Global functions
------
-----------------------------------------------------------------------------------------*/
PROTO void COE_UpdateSyncErrorStatus(void);
PROTO    void COE_ObjInit(void);
PROTO    void COE_Main(void);
PROTO UINT16 COE_ObjDictionaryInit(void);
PROTO UINT16 COE_AddObjectToDic(TOBJECT OBJMEM * pNewObjEntry);
PROTO void COE_RemoveDicEntry(UINT16 index);
PROTO void COE_ClearObjDictionary(void);
PROTO OBJCONST TOBJECT OBJMEM * COE_GetObjectDictionary(void);

#undef PROTO
/** @}*/
