/*-----------------------------------------------------------------------------------------
------	
------	ecat_def.h
------  SSC version : 5.11
-----------------------------------------------------------------------------------------*/

#ifndef _ECATDEF_H_
#define _ECATDEF_H_

/*-----------------------------------------------------------------------------------------
------	
------	Includes
------ 
-----------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------------------------------
------	
------	Slave Sample Code Configuration Defines
------	
-----------------------------------------------------------------------------------------*/

/** 
PREOPTIMEOUT: Specify timeout value for the state transition from Init to PreOP/Boot.(ESI Value : "PreopTimeout").<br>
NOTE: Within the stack this value - 50ms will be used to react before the master run into the timeout. */
#ifndef PREOPTIMEOUT
#define PREOPTIMEOUT                              0xC350
#endif

/** 
SAFEOP2OPTIMEOUT: Specifiy the timeout from SafeOP to OP. (ESI Value : "SafeopOpTimeout")<br>
NOTE: Within the stack this value - 50ms will be used to react before the master run into the timeout. */
#ifndef SAFEOP2OPTIMEOUT
#define SAFEOP2OPTIMEOUT                          0x2710
#endif

/*-----------------------------------------------------------------------------------------
------	
------	Compiler Defines
------	
-----------------------------------------------------------------------------------------*/

/** 
FALSE: Will be used for variables from type BOOL */
#ifndef FALSE
#define FALSE                                     0
#endif

/** 
TRUE: Will be used for variables from type BOOL  */
#ifndef TRUE
#define TRUE                                      1
#endif

/** 
BOOL: Should be adapted to the boolean type of the microcontroller */
#ifndef BOOL
#define BOOL                                      unsigned char
#endif

/** 
UINT8: Should be adapted to the unsigned8 type of the microcontroller  */
#ifndef UINT8
#define UINT8                                     unsigned char
#endif

/** 
UINT16: Should be adapted to the unsigned16 type of the microcontroller  */
#ifndef UINT16
#define UINT16                                    unsigned int
#endif

/** 
UINT32: Should be adapted to the unsigned32 type of the microcontroller  */
#ifndef UINT32
#define UINT32                                    unsigned long
#endif

/** 
UINT64: Should be adapted to the unsigned64 type of the microcontroller  */
#ifndef UINT64
#define UINT64                                    unsigned long long
#endif

/**
USHORT: Should be adapted to the unsigned16 type of the microcontroller */
#ifndef USHORT
#define USHORT                                    unsigned short
#endif

/** 
INT8: Should be adapted to the integer8 type of the microcontroller */
#ifndef INT8
#define INT8                                      char
#endif

/** 
INT16: Should be adapted to the integer16 type of the microcontroller  */
#ifndef INT16
#define INT16                                     int
#endif

/** 
INT32: Should be adapted to the integer32 type of the microcontroller */
#ifndef INT32
#define INT32                                     long
#endif

/** 
INT64: Should be adapted to the integer64 type of the microcontroller */
#ifndef INT64
#define INT64                                     long long
#endif

/**
CHAR: Should be adapted to the character type of the microcontroller */
#ifndef CHAR
#define CHAR                                      char
#endif

/** 
UCHAR: Should be adapted to the unsigned character type of the microcontroller */
#ifndef UCHAR
#define UCHAR                                     unsigned char
#endif

/** 
REAL32: Should be adapted to the 32bit real type of the microcontroller */
#ifndef REAL32
#define REAL32                                    float
#endif

/**
REAL64: Should be adapted to the 64bit real type of the microcontroller */
#ifndef REAL64
#define REAL64                                    long double
#endif


/**
SIZEOF(x): Used to calculate the size in Bytes */
#ifndef SIZEOF
#define SIZEOF(x)                                 sizeof(x)
#endif


/** 
HMEMSET: Should be defined to the memset function for huge memory, if the microcontroller<br>
does not support a huge type, HMEMSET shall be defined to a 'normal' memset function */
#ifndef HMEMSET
#define HMEMSET                                   memset
#endif

/** 
HMEMCPY: Should be defined to the memcpy function for huge memory, if the microcontroller<br>
does not support a huge type, HMEMCPY shall be defined to a 'normal' memcpy function */
#ifndef HMEMCPY
#define HMEMCPY                                   memcpy
#endif

/** 
ESCMEM: Should be defined to select the memory type of the ESC memory (e.g. near, far or huge), if the microcontroller<br>
does not support different memory types, ESCMEM shall be defined to nothing */
#ifndef ESCMEM
#define ESCMEM 
#endif

/** 
ESCMEMCPY: Should be defined to the memcpy function for ESCMEM memory, if the microcontroller<br>
does not support different memory types, ESCMEMCPY shall be defined to a 'normal' memcpy function */
#ifndef ESCMEMCPY
#define ESCMEMCPY                                 memcpy
#endif

/** 
ESCMEMSET: Should be defined to the memset function for ESCMEM memory, if the microcontroller<br>
does not support different memory types, ESCMEMSET shall be defined to a 'normal' memset function */
#ifndef ESCMEMSET
#define ESCMEMSET                                 memset
#endif

/** 
ESCMBXMEMCPY: Should be defined to the memcpy function for copying ESCMEM memory to or from MBXMEM memory, if the microcontroller<br>
does not support different memory types, ESCMBXMEMCPY shall be defined to a 'normal' memcpy function */
#ifndef ESCMBXMEMCPY
#define ESCMBXMEMCPY                              memcpy
#endif

/** 
MBXMEM: Should be defined to select the memory type of the memory used for mailbox communication (e.g. near, far or huge), <br>
if the microcontroller does not support different memory types, MBXMEM shall be defined to nothing */
#ifndef MBXMEM
#define MBXMEM 
#endif

/** 
MBXMEMCPY: Should be defined to the memcpy function for MBXMEM memory, if the microcontroller<br>
does not support different memory types, MBXMEMCPY shall be defined to a 'normal' memcpy function */
#ifndef MBXMEMCPY
#define MBXMEMCPY                                 memcpy
#endif

/** 
MBXMEMCMP: Should be defined to the memcmp function for MBXMEM memory, if the microcontroller<br>
does not support different memory types, MBXMEMCMP shall be defined to a 'normal' memcmp function */
#ifndef MBXMEMCMP
#define MBXMEMCMP                                 memcmp
#endif

/** 
MBXMEMSET: Should be defined to the memcpy function for MBXMEM memory, if the microcontroller<br>
does not support different memory types, MBXMEMSET shall be defined to a 'normal' memset function */
#ifndef MBXMEMSET
#define MBXMEMSET                                 memset
#endif

/** 
MBXSTRLEN: Should be defined to the strlen function for MBXMEM memory, if the microcontroller<br>
does not support different memory types, MBXSTRLEN shall be defined to a 'normal' strlen function */
#ifndef MBXSTRLEN
#define MBXSTRLEN                                 strlen
#endif

/** 
MBXSTRCPY: Should be defined to the strcpy function for MBXMEM memory, if the microcontroller<br>
does not support different memory types, MBXSTRCPY shall be defined to a 'normal' strcpy function */
#ifndef MBXSTRCPY
#define MBXSTRCPY                                 memcpy
#endif

/** 
OBJCONST: Should be used to define the object dictionary in ROM (f.e. define OBJCONST const) or<br>
in RAM (e.g. define OBJCONST) */
#ifndef OBJCONST
#define OBJCONST                                  const
#endif

/** 
VARCONST: Should be used to define the constant variables in ROM (f.e. define VARCONST const) or<br>
in RAM (e.g. define VARCONST) */
#ifndef VARCONST
#define VARCONST 
#endif

/** 
VARVOLATILE: Should be used to prevent dummy variables to be deleted due to compiler optimization.  */
#ifndef VARVOLATILE
#define VARVOLATILE                               volatile
#endif

/** 
OBJMEM: Should be defined to select the memory type of the memory used for the object dictionary (e.g. near, far or huge), <br>
if the microcontroller does not support different memory types, OBJMEM shall be defined to nothing */
#ifndef OBJMEM
#define OBJMEM 
#endif

/** 
OBJTOMBXMEMCPY: Should be defined to the memcpy function for copying OBJMEM memory to MBXMEM memory, if the microcontroller<br>
does not support different memory types, OBJTOMBXMEMCPY shall be defined to a 'normal' memcpy function */
#ifndef OBJTOMBXMEMCPY
#define OBJTOMBXMEMCPY                            memcpy
#endif

/** 
OBJTOMBXSTRCPY: Should be defined to the strcpy function for copying OBJMEM memory to MBXMEM memory, if the microcontroller<br>
does not support different memory types, OBJTOMBXSTRCPY shall be defined to a 'normal' memcpy function */
#ifndef OBJTOMBXSTRCPY
#define OBJTOMBXSTRCPY                            memcpy
#endif

/** 
OBJMEMCPY: Should be defined to the memcpy function for OBJMEM memory, if the microcontroller<br>
does not support different memory types, OBJMEMCPY shall be defined to a 'normal' memcpy function */
#ifndef OBJMEMCPY
#define OBJMEMCPY                                 memcpy
#endif

/** 
OBJSTRLEN: Should be defined to the strlen function for OBJMEM memory, if the microcontroller<br>
does not support different memory types, OBJSTRLEN shall be defined to a 'normal' strlen function */
#ifndef OBJSTRLEN
#define OBJSTRLEN                                 strlen
#endif

/** 
OBJSTRCPY: Should be defined to the strcpy function for OBJMEM memory, if the microcontroller<br>
does not support different memory types, OBJSTRCPY shall be defined to a 'normal' strcpy function */
#ifndef OBJSTRCPY
#define OBJSTRCPY                                 memcpy
#endif


/** 
EMCYMEMCPY: Should be defined to the memcpy function for EMCYMEM memory, if the microcontroller<br>
does not support different memory types, EMCYMEMCPY shall be defined to a 'normal' memcpy function */
#ifndef EMCYMEMCPY
#define EMCYMEMCPY                                memcpy
#endif

/** 
EMCYMEMSET: Should be defined to the memset function for EMCYMEM memory, if the microcontroller<br>
does not support different memory types, EMCYMEMSET shall be defined to a 'normal' memcset function */
#ifndef EMCYMEMSET
#define EMCYMEMSET                                memset
#endif

/** 
EMCYMEM: Should be defined to select the memory type of the memory used for the emergencies (e.g. near, far or huge), <br>
if the microcontroller does not support different memory types, EMCYMEM shall be defined to nothing */
#ifndef EMCYMEM
#define EMCYMEM 
#endif

/** 
MEMCPY: Should be defined to copy data within local memory. */
#ifndef MEMCPY
#define MEMCPY                                    memcpy
#endif

/** 
ALLOCMEM(size): Should be defined to the alloc function to get dynamic memory */
#ifndef ALLOCMEM
#define ALLOCMEM(size)                            malloc((size))
#endif

/** 
FREEMEM(pointer): Should be defined to the free function to put back dynamic memory */
#ifndef FREEMEM
#define FREEMEM(pointer)                          free((pointer))
#endif

/** 
VARMEMSET: Should be defined to the memset function for VARMEM memory, if the microcontroller<br>
does not support different memory types, EMCYMEMSET shall be defined to a 'normal' memcset function */
#ifndef VARMEMSET
#define VARMEMSET                                 memset
#endif

/** 
VARMEM: Should be defined to select the memory type of the memory used for dynamic memory (e.g. near, far or huge), <br>
if the microcontroller does not support different memory types, VARMEM shall be defined to nothing */
#ifndef VARMEM
#define VARMEM 
#endif

/** 
MEM_ADDR: Type to access local memory addresses */
#ifndef MEM_ADDR
#define MEM_ADDR                                  UINT16
#endif

/** 
GET_MEM_SIZE(ByteSize): Round up the byte size to next matching memory boundary depending on "MEM_ADDR" */
#ifndef GET_MEM_SIZE
#define GET_MEM_SIZE(ByteSize)                    (((ByteSize)+1) >> 1)
#endif

/** 
APPL_AllocMailboxBuffer(size): Should be defined to a function to get a buffer for a mailbox service,<br>
this is only used if the switch MAILBOX_QUEUE is set */
#ifndef APPL_AllocMailboxBuffer
#define APPL_AllocMailboxBuffer(size)             malloc((size))
#endif

/** 
APPL_FreeMailboxBuffer(pointer): Should be defined to a function to put back a buffer for a mailbox service,<br>
this is only used if the switch MAILBOX_QUEUE is set */
#ifndef APPL_FreeMailboxBuffer
#define APPL_FreeMailboxBuffer(pointer)           free((pointer))
#endif

/** 
STRUCT_PACKED_START: Is defined before the typedef struct construct to pack the generic structures if necessary */
#ifndef STRUCT_PACKED_START
#define STRUCT_PACKED_START 
#endif

/** 
STRUCT_PACKED_END: Is defined after the typedef struct {} construct to pack the generic structures if necessary */
#ifndef STRUCT_PACKED_END
#define STRUCT_PACKED_END 
#endif

/** 
MBX_STRUCT_PACKED_START: Is defined before the typedef struct construct to pack the MAILBOX structures if necessary */
#ifndef MBX_STRUCT_PACKED_START
#define MBX_STRUCT_PACKED_START 
#endif

/** 
MBX_STRUCT_PACKED_END: Is defined after the typedef struct {} construct to pack the MAILBOX structures if necessary */
#ifndef MBX_STRUCT_PACKED_END
#define MBX_STRUCT_PACKED_END 
#endif

/** 
OBJ_STRUCT_PACKED_START: Is defined before the typedef struct construct to pack the OBJECT structures if necessary */
#ifndef OBJ_STRUCT_PACKED_START
#define OBJ_STRUCT_PACKED_START
#endif

/** 
OBJ_STRUCT_PACKED_END: Is defined after the typedef struct {} construct to pack the OBJECT structures if necessary */
#ifndef OBJ_STRUCT_PACKED_END
#define OBJ_STRUCT_PACKED_END
#endif

/** 
OBJ_DWORD_ALIGN: Shall be set if the object structures are not Byte aligned and the Code is executed on an 32bit platform */
#ifndef OBJ_DWORD_ALIGN
#define OBJ_DWORD_ALIGN                           0
#endif

/** 
OBJ_WORD_ALIGN: Shall be set if the object structures are not Byte aligned and the Code is executed on an 16bit platform */
#ifndef OBJ_WORD_ALIGN
#define OBJ_WORD_ALIGN                            1
#endif


/*-----------------------------------------------------------------------------------------
------	
------	Application Specific Defines
------	
-----------------------------------------------------------------------------------------*/

/** 
VENDOR_ID: Object 0x1018 SI1 (Vendor ID)	 <br>
An unique EtherCAT Vendor ID is required. Please find all valid Vendor IDs listed at www.ethercat.org/en/vendor_id_list.html.<br>
If your company is not listed, please assign an ID for free at www.ethercat.org/memberarea/vendor_id.asp */
#ifndef VENDOR_ID
#define VENDOR_ID                                 0x896
#endif

/** 
PRODUCT_CODE: Object 0x1018 SI2 (EtherCAT product code) */
#ifndef PRODUCT_CODE
#define PRODUCT_CODE                              0x0
#endif

/** 
REVISION_NUMBER: Object 0x1018 SI3 (EtherCAT product revision number) */
#ifndef REVISION_NUMBER
#define REVISION_NUMBER                           0x0
#endif

/** 
SERIAL_NUMBER: Object 0x1018 SI4 (EtherCAT product serial number) */
#ifndef SERIAL_NUMBER
#define SERIAL_NUMBER                             0x0
#endif

/** 
DEVICE_PROFILE_TYPE: Slave device type (Object 0x1000)  */
#ifndef DEVICE_PROFILE_TYPE
#define DEVICE_PROFILE_TYPE                       0x04020192
#endif

/** 
DEVICE_NAME: Name of the slave device (Object 0x1008) */
#ifndef DEVICE_NAME
#define DEVICE_NAME                               "GDC16"
#endif

/** 
DEVICE_NAME_LEN: Length of 'DEVICE_NAME' without '\0' */
#ifndef DEVICE_NAME_LEN
#define DEVICE_NAME_LEN                           0x5
#endif

/** 
DEVICE_HW_VERSION: Hardware version of the slave device (Object 0x1009) */
#ifndef DEVICE_HW_VERSION
#define DEVICE_HW_VERSION                         "0"
#endif

/** 
DEVICE_HW_VERSION_LEN: Length of 'DEVICE_HW_VERSION' without '\0' */
#ifndef DEVICE_HW_VERSION_LEN
#define DEVICE_HW_VERSION_LEN                     0x1
#endif

/** 
DEVICE_SW_VERSION: Software version of the slave device (Object 0x100A) */
#ifndef DEVICE_SW_VERSION
#define DEVICE_SW_VERSION                         "5.11"
#endif

/** 
DEVICE_SW_VERSION_LEN: Length of 'DEVICE_SW_VERSION' without '\0' */
#ifndef DEVICE_SW_VERSION_LEN
#define DEVICE_SW_VERSION_LEN                     0x4
#endif

/** 
MIN_PD_WRITE_ADDRESS: Minimum address for the process output data (Sync Manager 2)<br>
inside the application memory of the EtherCAT Slave Controller which could be set by the master. The setting have to be within the ranges of the user memory of the ESC (this is not checked by the tool). */
#ifndef MIN_PD_WRITE_ADDRESS
#define MIN_PD_WRITE_ADDRESS                      0x1000
#endif

/** 
MAX_PD_WRITE_ADDRESS: Maximum address for the process output data (Sync Manager 2)<br>
inside the application memory of the EtherCAT Slave Controller which could be set by the master. The setting have to be within the ranges of the user memory of the ESC (this is not checked by the tool). */
#ifndef MAX_PD_WRITE_ADDRESS
#define MAX_PD_WRITE_ADDRESS                      0x2FFF
#endif

/** 
MIN_PD_READ_ADDRESS: Minimum address for the process input data (Sync Manager 3)<br>
inside the application memory of the EtherCAT Slave Controller which could be set by the master. The setting have to be within the ranges of the user memory of the ESC (this is not checked by the tool). */
#ifndef MIN_PD_READ_ADDRESS
#define MIN_PD_READ_ADDRESS                       0x1000
#endif

/** 
MAX_PD_READ_ADDRESS: Maximum address for the process input data (Sync Manager 3)<br>
inside the application memory of the EtherCAT Slave Controller which could be set by the master. The setting have to be within the ranges of the user memory of the ESC (this is not checked by the tool). */
#ifndef MAX_PD_READ_ADDRESS
#define MAX_PD_READ_ADDRESS                       0x2FFF
#endif

/** 
MIN_MBX_SIZE: Minimum mailbox size (Sync Manager 0 and 1) which could be set by the master. The SSC don't support fragmented SDO info object/entry service => at least entry info including 12byte name shall fit in the mailbox buffer */
#ifndef MIN_MBX_SIZE
#define MIN_MBX_SIZE                              0x0022
#endif

/** 
MAX_MBX_SIZE: Maximum mailbox size (Sync Manager 0 and 1) which could be set by the master. */
#ifndef MAX_MBX_SIZE
#define MAX_MBX_SIZE                              0x0400
#endif

/** 
MIN_MBX_WRITE_ADDRESS: Minimum address for the write (receive) mailbox (Sync Manager 0). The setting have to be within the ranges of the user memory of the ESC (this is not checked by the tool). */
#ifndef MIN_MBX_WRITE_ADDRESS
#define MIN_MBX_WRITE_ADDRESS                     0x1000
#endif

/** 
MAX_MBX_WRITE_ADDRESS: Maximum address for the write (receive) mailbox (Sync Manager 0). The setting have to be within the ranges of the user memory of the ESC (this is not checked by the tool). */
#ifndef MAX_MBX_WRITE_ADDRESS
#define MAX_MBX_WRITE_ADDRESS                     0x2FFF
#endif

/** 
MAX_PD_INPUT_SIZE: Maximum size of the process input data (Sync Manager 3) for cyclic exchange. */
#ifndef MAX_PD_INPUT_SIZE
#define MAX_PD_INPUT_SIZE                         0x0400 //This define was already evaluated by ET9300 Project Handler(V. 1.3.3.0)!
#endif

/** 
MIN_MBX_READ_ADDRESS: Minimum address for the read (send) mailbox (Sync Manager 1). */
#ifndef MIN_MBX_READ_ADDRESS
#define MIN_MBX_READ_ADDRESS                      0x1000
#endif

/** 
MAX_MBX_READ_ADDRESS: Maximum address for the read (send) mailbox (Sync Manager 1). */
#ifndef MAX_MBX_READ_ADDRESS
#define MAX_MBX_READ_ADDRESS                      0x2FFF
#endif

/** 
MAX_PD_OUTPUT_SIZE: Maximum size of the process output data (Sync Manager 2) for cyclic exchange. */
#ifndef MAX_PD_OUTPUT_SIZE
#define MAX_PD_OUTPUT_SIZE                        0x0400 //This define was already evaluated by ET9300 Project Handler(V. 1.3.3.0)!
#endif

/** 
MIN_PD_CYCLE_TIME: Minimum cycle time in ns the slave is supporting <br>
(entry 0x1C32:05 or entry 0x1C33:05) */
#ifndef MIN_PD_CYCLE_TIME
#define MIN_PD_CYCLE_TIME                         0x3D090
#endif

/** 
MAX_PD_CYCLE_TIME: Maximum cycle time in ns the slave is supporting */
#ifndef MAX_PD_CYCLE_TIME
#define MAX_PD_CYCLE_TIME                         0xC3500000
#endif

/** 
PD_OUTPUT_DELAY_TIME: Minimum output delay time in ns the slave is supporting (entry 0x1C32:09) */
#ifndef PD_OUTPUT_DELAY_TIME
#define PD_OUTPUT_DELAY_TIME                      0x0
#endif

/** 
PD_OUTPUT_CALC_AND_COPY_TIME: Output calc+copy time in ns the slave is supporting (entry 0x1C32:06) */
#ifndef PD_OUTPUT_CALC_AND_COPY_TIME
#define PD_OUTPUT_CALC_AND_COPY_TIME              0x0
#endif

/** 
PD_INPUT_CALC_AND_COPY_TIME: Input calc+copy time in ns the slave is supporting (entry 0x1C33:06) */
#ifndef PD_INPUT_CALC_AND_COPY_TIME
#define PD_INPUT_CALC_AND_COPY_TIME               0x0
#endif

/** 
PD_INPUT_DELAY_TIME: Input delay time in ns the slave is supporting (entry 0x1C33:09) */
#ifndef PD_INPUT_DELAY_TIME
#define PD_INPUT_DELAY_TIME                       0x0
#endif



/*-----------------------------------------------------------------------------------------
------	
------	Test Configuration Defines
------	
-----------------------------------------------------------------------------------------*/


#endif // _ECATDEF_H_

