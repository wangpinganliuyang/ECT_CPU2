/**
\addtogroup CiA402appl CiA402 Sample Application
@{
*/

/**
\file cia402appl.c
\author EthercatSSC@beckhoff.com
\brief Implementation
This file contains all ciA402 specific functions

\version 5.11

<br>Changes to version V5.10:<br>
V5.11 ECAT11: create application interface function pointer, add eeprom emulation interface functions<br>
<br>Changes to version V5.01:<br>
V5.10 CIA402 1: Update complete access handling for 0xF030<br>
V5.10 ECAT6: Add "USE_DEFAULT_MAIN" to enable or disable the main function<br>
<br>Changes to version V5.0:<br>
V5.01 ESC2: Add missed value swapping<br>
<br>Changes to version V4.40:<br>
V5.0 CIA402 1: Syntax bugfix in dummy motion controller<br>
V5.0 CIA402 2: Handle 0xF030/0xF050 in correlation do PDO assign/mapping objects<br>
V5.0 CIA402 3: Trigger dummy motion controller if valid mode of operation is set.<br>
V5.0 CIA402 4: Change Axes structure handling and resources allocation.<br>
V5.0 ECAT2: Create generic application interface functions. Documentation in Application Note ET9300.<br>
<br>Changes to version V4.30:<br>
V4.40 CoE 6: add AL Status code to Init functions<br>
V4.40 CIA402 2: set motion control trigger depending on "Synchronisation", "mode of operation" and "cycle time"<br>
V4.40 CIA402 1: change behaviour and name of bit12 of the status word (0x6041) (WG CIA402 24.02.2010)<br>
V4.30 : create file (state machine; handling state transition options; input feedback)
*/

/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/



#include "GDC16.h"

#define _CiA402_
#include "cia402appl.h"
#undef _CiA402_


/*--------------------------------------------------------------------------------------
------
------    local types and defines
------
--------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    local variables and constants
------
-----------------------------------------------------------------------------------------*/
const TSDOINFOENTRYDESC    OBJMEM asPDOAssignEntryDesc[] = {
   {DEFTYPE_UNSIGNED8, 0x08, (ACCESS_READ|ACCESS_WRITE_PREOP)},
   {DEFTYPE_UNSIGNED16, 0x10, (ACCESS_READ|ACCESS_WRITE_PREOP)}};


/**
 * \brief Object 0x1C12 (Sync Manager 2 assign) object and entry names
 *
 * In this example no specific entry name is defined ("SubIndex xxx" is used)
 */
const UCHAR OBJMEM aName0x1C12[] = "R";

/**
 * \brief Object 0x1C13 (Sync Manager 3 assign) object and entry names
 *
 * In this example no specific entry name is defined ("SubIndex xxx" is used)
 */
const UCHAR OBJMEM aName0x1C13[] = "T";
/** @}*/


/**
* \addtogroup PdoMappingObjects PDO Mapping Objects
* @{
*/
/**
 * \brief Object 0x1601 (csp RxPDO) entry descriptions
 */
OBJCONST TSDOINFOENTRYDESC  OBJMEM asEntryDesc0x1601[] = {
   {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ }, /* Subindex 000 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}, /* SubIndex 001*/
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}}; /* SubIndex 002*/


/**
 * \brief Object 0x1601 (csp RxPDO) object and entry names
 *
 * In this example no specific entry name is defined ("SubIndex xxx" is used)
 */
OBJCONST UCHAR OBJMEM aName0x1601[] = "c\000\377";


/**
 * \brief Object 0x1602 (csv RxPDO) entry descriptions
 */
OBJCONST TSDOINFOENTRYDESC  OBJMEM asEntryDesc0x1602[] = {
   {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ }, /* Subindex 000 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}, /* SubIndex 001*/
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}}; /* SubIndex 002*/


/**
 * \brief Object 0x1602 (csv RxPDO) object and entry names
 *
 * In this example no specific entry name is defined ("SubIndex xxx" is used)
 */
OBJCONST UCHAR OBJMEM aName0x1602[] = "c\000\377";



/**
 * \brief Object 0x1603 (cst RxPDO) entry descriptions
 */
OBJCONST TSDOINFOENTRYDESC  OBJMEM asEntryDesc0x1603[] = {
   {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ }, /* Subindex 000 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}, /* SubIndex 001*/
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}}; /* SubIndex 002*/


/**
 * \brief Object 0x1603 (csv RxPDO) object and entry names
 *
 * In this example no specific entry name is defined ("SubIndex xxx" is used)
 */
OBJCONST UCHAR OBJMEM aName0x1603[] = "c\000\377";

/**
 * \brief Object 0x1A01 (csp RxPDO) entry descriptions
 */
OBJCONST TSDOINFOENTRYDESC  OBJMEM asEntryDesc0x1A01[] = {
   {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ }, /* Subindex 000 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}, /* SubIndex 001*/
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}}; /* SubIndex 002 */


/**
 * \brief Object 0x1A01 (csp TxPDO) object and entry names
 *
 * In this example no specific entry name is defined ("SubIndex xxx" is used)
 */
OBJCONST UCHAR OBJMEM aName0x1A01[] = "c\000\377";



/**
 * \brief Object 0x1A02 (csv RxPDO) entry descriptions
 */
OBJCONST TSDOINFOENTRYDESC  OBJMEM asEntryDesc0x1A02[] = {
   {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ }, /* Subindex 000 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}, /* SubIndex 001*/
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}, /* SubIndex 002*/
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}}; /* SubIndex 003 */


/**
 * \brief Object 0x1A02 (csv TxPDO) object and entry names
 *
 * In this example no specific entry name is defined ("SubIndex xxx" is used)
 */
OBJCONST UCHAR OBJMEM aName0x1A02[] = "c\000\377";


/**
 * \brief Object 0x1A03 (cst RxPDO) entry descriptions
 */
OBJCONST TSDOINFOENTRYDESC  OBJMEM asEntryDesc0x1A03[] = {
   {DEFTYPE_UNSIGNED8, 0x8, ACCESS_READ }, /* Subindex 000 */
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}, /* SubIndex 001*/
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}, /* SubIndex 002*/
   {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ}}; /* SubIndex 003 */


/**
 * \brief Object 0x1A03 (cst TxPDO) object and entry names
 *
 * In this example no specific entry name is defined ("SubIndex xxx" is used)
 */
OBJCONST UCHAR OBJMEM aName0x1A03[] = "c\000\377";
/** @}*/



/**
 * \addtogroup CiA402Objects CiA402 Axis Objects
 * @{
 */

/** \brief Object 0x603F (Error Code) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x603F = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READ};

/** \brief Object 0x603F (Error Code) object name*/
OBJCONST UCHAR OBJMEM aName0x603F[] = "E";

/** \brief Object 0x6040 (Control Word) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6040 = {DEFTYPE_UNSIGNED16, 0x10, (ACCESS_READWRITE|OBJACCESS_RXPDOMAPPING)};

/** \brief Object 0x6040 (Control Word) object name*/
OBJCONST UCHAR OBJMEM aName0x6040[] = "C";

/** \brief Object 0x6041 (Status Word) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6041 = {DEFTYPE_UNSIGNED16, 0x10, (ACCESS_READ|OBJACCESS_TXPDOMAPPING)};

/** \brief Object 0x6041 (Status Word) object name*/
OBJCONST UCHAR OBJMEM aName0x6041[] = "S";

/** \brief Object 0x6060 (Modes of Operation) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6060 = {DEFTYPE_INTEGER8, 0x08, (ACCESS_READWRITE|OBJACCESS_RXPDOMAPPING)};

/** \brief Object 0x6060 (Modes of Operation) object name*/
OBJCONST UCHAR OBJMEM aName0x6060[] = "M";

/** \brief Object 0x6061 (Modes of Operation Display) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6061 = {DEFTYPE_INTEGER8, 0x08, (ACCESS_READ|OBJACCESS_TXPDOMAPPING)};

/** \brief Object 0x6061 (Modes of Operation Display) object name*/
OBJCONST UCHAR OBJMEM aName0x6061[] = "M";

/** \brief Object 0x6063 (Position actual internal value) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6063 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};

/** \brief Object 0x6063 (Position actual internal value) object name*/
OBJCONST UCHAR OBJMEM aName0x6063[] = "P";

/** \brief Object 0x6064 (Position Actual Value) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6064 = {DEFTYPE_INTEGER32, 0x20, (ACCESS_READ|OBJACCESS_TXPDOMAPPING)};

/** \brief Object 0x6064 (Position Actual Value) object name*/
OBJCONST UCHAR OBJMEM aName0x6064[] = "P";

/** \brief Object 0x6065 (Following error window) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6065 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

/** \brief Object 0x6065 (Following error window) object name*/
OBJCONST UCHAR OBJMEM aName0x6065[] = "F";

/** \brief Object 0x606B (Velocity demand value) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x606B = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};

/** \brief Object 0x606B (Velocity demand value) object name*/
OBJCONST UCHAR OBJMEM aName0x606B[] = "V";

/** \brief Object 0x606C (Velocity Actual Value) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x606C = {DEFTYPE_INTEGER32, 0x20, (ACCESS_READ|OBJACCESS_TXPDOMAPPING)};

/** \brief Object 0x606C (Velocity Actual Value) object name*/
OBJCONST UCHAR OBJMEM aName0x606C[] = "V";

/** \brief Object 0x606D (Velocity window) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x606D = {DEFTYPE_INTEGER16, 0x10, (ACCESS_READWRITE|OBJACCESS_RXPDOMAPPING)};

/** \brief Object 0x606D (Velocity window) object name*/
OBJCONST UCHAR OBJMEM aName0x606D[] = "V";

/** \brief Object 0x606E (Velocity window Time) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x606E = {DEFTYPE_INTEGER16, 0x10, (ACCESS_READWRITE|OBJACCESS_RXPDOMAPPING)};

/** \brief Object 0x606E (Velocity window Time) object name*/
OBJCONST UCHAR OBJMEM aName0x606E[] = "V";

/** \brief Object 0x6071 (Target torque) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6071 = {DEFTYPE_INTEGER16, 0x10, (ACCESS_READWRITE|OBJACCESS_RXPDOMAPPING)};

/** \brief Object 0x6071 (Target torque) object name*/
OBJCONST UCHAR OBJMEM aName0x6071[] = "T";

/** \brief Object 0x6072 (Max torque) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6072 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

/** \brief Object 0x6072 (Max torque) object name*/
OBJCONST UCHAR OBJMEM aName0x6072[] = "M";

/** \brief Object 0x6077 (Torque Actual Value) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6077 = {DEFTYPE_INTEGER16, 0x10, ACCESS_READ};

/** \brief Object 0x6077 (Torque Actual Value) object name*/
OBJCONST UCHAR OBJMEM aName0x6077[] = "T";

/** \brief Object 0x607A (Target Position) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x607A = {DEFTYPE_INTEGER32, 0x20, (ACCESS_READWRITE|OBJACCESS_RXPDOMAPPING)};

/** \brief Object 0x607A (Target Position) object name*/
OBJCONST UCHAR OBJMEM aName0x607A[] = "T";

/** \brief Object 0x607C (Home offset) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x607C = {DEFTYPE_UNSIGNED16, 0x20, ACCESS_READWRITE};

/** \brief Object 0x607C (Home offset) object name*/
OBJCONST UCHAR OBJMEM aName0x607C[] = "H";

/**
 * \brief Object 0x607D (Software Position Limit) entry description
 *
 * Subindex 0<br>
 * Subindex 1 : Min Position range limit<br>
 * Subindex 2 : Max Position range limit
 */
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x607D[] = {
    {DEFTYPE_UNSIGNED8, 0x08, ACCESS_READ},
    {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE},
    {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE}};


/** \brief Object 0x607D (Software Position Limit) object and entry names*/
OBJCONST UCHAR OBJMEM aName0x607D[] = "S\000M\000M\000\377";

/** \brief Object 0x6081 (Profile velocity in pp-mode) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6081 = {DEFTYPE_UNSIGNED32, 0x20, (ACCESS_READWRITE|OBJACCESS_RXPDOMAPPING)};

/** \brief Object 0x6081 (Profile velocity in pp-mode) object name*/
OBJCONST UCHAR OBJMEM aName0x6081[] = "P";

/** \brief Object 0x6083 (Profile acceleration) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6083 = {DEFTYPE_UNSIGNED32, 0x20, (ACCESS_READWRITE|OBJACCESS_RXPDOMAPPING)};

/** \brief Object 0x6083 (Profile acceleration) object name*/
OBJCONST UCHAR OBJMEM aName0x6083[] = "P";

/** \brief Object 0x6084 (Profile deceleration) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6084 = {DEFTYPE_UNSIGNED32, 0x20, (ACCESS_READWRITE|OBJACCESS_RXPDOMAPPING)};

/** \brief Object 0x6084 (Profile deceleration) object name*/
OBJCONST UCHAR OBJMEM aName0x6084[] = "P";

/** \brief Object 0x6087 (Torque slope) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6087 = {DEFTYPE_UNSIGNED32, 0x20, (ACCESS_READWRITE|OBJACCESS_RXPDOMAPPING)};

/** \brief Object 0x6087 (Torque slope) object name*/
OBJCONST UCHAR OBJMEM aName0x6087[] = "T";

/** \brief Object 0x6098 (Homing method) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6098 = {DEFTYPE_UNSIGNED8, 0x08, ACCESS_READWRITE};

/** \brief Object 0x6098 (Homing method) object name*/
OBJCONST UCHAR OBJMEM aName0x6098[] = "H";

/**
 * \brief Object 0x6099 (Homing speeds) entry description
 *
 * Subindex 0<br>
 * Subindex 1 : Fast homing speed<br>
 * Subindex 2 : Slow homing speed
 */
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6099[] = {
    {DEFTYPE_UNSIGNED8, 0x08, ACCESS_READ},
    {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},
    {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE}};

/** \brief Object 0x6099 (Homing speeds) object and entry names*/
OBJCONST UCHAR OBJMEM aName0x6099[] = "H\000F\000S\000\377";

/** \brief Object 0x609A (Homing acceleration) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x609A = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE};

/** \brief Object 0x609A (Homing acceleration) object name*/
OBJCONST UCHAR OBJMEM aName0x609A[] = "H";

/** \brief Object 0x60B1 (Velocity offset) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60B1 = {DEFTYPE_INTEGER32, 0x20, (ACCESS_READWRITE|OBJACCESS_RXPDOMAPPING)};

/** \brief Object 0x60B1 (Velocity offset) object name*/
OBJCONST UCHAR OBJMEM aName0x60B1[] = "V";

/** \brief Object 0x60B2 (Torque offset) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60B2 = {DEFTYPE_INTEGER16, 0x10, (ACCESS_READWRITE|OBJACCESS_RXPDOMAPPING)};

/** \brief Object 0x60B2 (Torque offset) object name*/
OBJCONST UCHAR OBJMEM aName0x60B2[] = "T";

/** \brief Object 0x60B8 (Touch probe function) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60B8 = {DEFTYPE_UNSIGNED16, 0x10, (ACCESS_READWRITE|OBJACCESS_RXPDOMAPPING)};

/** \brief Object 0x60B8 (Touch probe function) object name*/
OBJCONST UCHAR OBJMEM aName0x60B8[] = "T";

/** \brief Object 0x60B9 (Touch probe status) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60B9 = {DEFTYPE_UNSIGNED16, 0x10, (ACCESS_READWRITE|OBJACCESS_TXPDOMAPPING)};

/** \brief Object 0x60B9 (Touch probe status) object name*/
OBJCONST UCHAR OBJMEM aName0x60B9[] = "T";

/** \brief Object 0x60BA (Touch probe 1 positive edge) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60BA = {DEFTYPE_INTEGER32, 0x20, (ACCESS_READ|OBJACCESS_TXPDOMAPPING)};

/** \brief Object 0x60BA (Touch probe 1 positive edge) object name*/
OBJCONST UCHAR OBJMEM aName0x60BA[] = "T";

/** \brief Object 0x60BB (Touch probe 1 negative edge) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60BB = {DEFTYPE_INTEGER32, 0x20, (ACCESS_READ|OBJACCESS_TXPDOMAPPING)};

/** \brief Object 0x60BB (Touch probe 1 negative edge) object name*/
OBJCONST UCHAR OBJMEM aName0x60BB[] = "T";

/** \brief Object 0x60BC (Touch probe 2 positive edge) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60BC = {DEFTYPE_INTEGER32, 0x20, (ACCESS_READ|OBJACCESS_TXPDOMAPPING)};

/** \brief Object 0x60BC (Touch probe 2 positive edge) object name*/
OBJCONST UCHAR OBJMEM aName0x60BC[] = "T";

/** \brief Object 0x60BD (Touch probe 2 negative edge) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60BD = {DEFTYPE_INTEGER32, 0x20, (ACCESS_READ|OBJACCESS_TXPDOMAPPING)};

/** \brief Object 0x60BD (Touch probe 1 negative edge) object name*/
OBJCONST UCHAR OBJMEM aName0x60BD[] = "T";

/** \brief Object 0x60C0 (Interpolation sub mode select) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60C0 = {DEFTYPE_INTEGER16, 0x10, ACCESS_READWRITE};

/** \brief Object 0x60C0 (Interpolation sub mode select) object name*/
OBJCONST UCHAR OBJMEM aName0x60C0[] = "I";

/**
 * \brief Object 0x60C2 (Interpolation Time Period) entry description
 *
 * Subindex 0<br>
 * Subindex 1 : Interpolation time period value<br>
 * Subindex 2 : Interpolation time index
 */
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x60C2[] = {
    {DEFTYPE_UNSIGNED8, 0x08, ACCESS_READ},
    {DEFTYPE_UNSIGNED8, 0x08, ACCESS_READWRITE},
    {DEFTYPE_INTEGER8, 0x08, ACCESS_READWRITE}};

/** \brief Object 0x60C2 (Interpolation Time Period) object and entry names*/
OBJCONST UCHAR OBJMEM aName0x60C2[] = "I\000I \000I\000\377";

/** \brief Object 0x60E0 (Positive torque limit) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60E0 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

/** \brief Object 0x60E0 (Positive torque limit) object name*/
OBJCONST UCHAR OBJMEM aName0x60E0[] = "P";


/** \brief Object 0x60E1 (Negative torque limit) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60E1 = {DEFTYPE_UNSIGNED16, 0x10, ACCESS_READWRITE};

/** \brief Object 0x60E1 (Negative torque limit) object name*/
OBJCONST UCHAR OBJMEM aName0x60E1[] = "N";

/** \brief Object 0x60F4 (Following error actual value) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60F4 = {DEFTYPE_INTEGER32, 0x20, (ACCESS_READ|OBJACCESS_TXPDOMAPPING)};

/** \brief Object 0x60F4 (Following error actual value) object name*/
OBJCONST UCHAR OBJMEM aName0x60F4[] = "F";

/** \brief Object 0x60FC (Position demand internal value) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60FC = {DEFTYPE_INTEGER32, 0x20, (ACCESS_READ|OBJACCESS_TXPDOMAPPING)};

/** \brief Object 0x60FC (Position demand internal value) object name*/
OBJCONST UCHAR OBJMEM aName0x60FC[] = "P";

/** \brief Object 0x60FD (Digital inputs) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60FD = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};

/** \brief Object 0x60FD (Digital inputs) object name*/
OBJCONST UCHAR OBJMEM aName0x60FD[] = "D";

/**
 * \brief Object 0x60FE (Digital outputs) entry description
 *
 * Subindex 0<br>
 * Subindex 1 : Interpolation time period value<br>
 * Subindex 2 : Interpolation time index
 */
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x60FE[] = {
    {DEFTYPE_UNSIGNED8, 0x08, ACCESS_READ},
    {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE},
    {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READWRITE}};

/** \brief Object 0x60FE (Digital outputs) object and entry names*/
OBJCONST UCHAR OBJMEM aName0x60FE[] = "D\000P\000O\000\377";

/** \brief Object 0x60FF (Target Velocity) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60FF = {DEFTYPE_INTEGER32, 0x20, (ACCESS_READWRITE|OBJACCESS_RXPDOMAPPING)};

/** \brief Object 0x60FF (Target Velocity) object name*/
OBJCONST UCHAR OBJMEM aName0x60FF[] = "T";


/** \brief Object 0x6502 (Supported Drive Modes) entry description*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6502 = {DEFTYPE_UNSIGNED32, 0x20, ACCESS_READ};

/** \brief Object 0x6502 (Supported Drive Modes) object name*/
OBJCONST UCHAR OBJMEM aName0x6502[] = "S";

TOBJ1C12 sRxPDOassign = {1,0x1601};

TOBJ1C13 sTxPDOassign = {1,0x1A01};

CiA402Objects DefCiA402ObjectValues
= {
{2, {0x60400010,0x607A0020}}, /*TOBJ1601*/
{2, {0x60400010,0x60FF0020}}, /*TOBJ1602*/
{2, {0x60400010,0x60710010}}, /*TOBJ1603*/
{2, {0x60410010,0x60640020}}, /*TOBJ1A01*/
{3, {0x60410010,0x60640020,0x606C0020}},/*TOBJ1A02*/
{3, {0x60410010,0x60640020,0x60770010}},/*TOBJ1A03*/
0x0,/*(UINT16) ErrorCode 0x603F*/
0x0,/*(UINT16) ControlWord 0x6040*/
0x0,/*(UINT16) StatusWord 0x6041*/
0x0,/*(INT16) ModeOfOperation 0x6060*/
0x0,/*(INT16) Mode Of Operation Display 0x6061*/
0x0,/*(UINT32) Position actual internal value 0x6063*/
0x0,/*(INT32) Position Actual Value 0x6064*/
0x0,/*(UINT32) Following error window 0x6065*/
0x0,/*(INT32) Velocity demand value 0x606B*/
0x0,/*(INT32) Velocity Actual Value 0x606C*/
0x0,/*(UINT16) Velocity window 0x606D*/
0x0,/*(UINT16) Velocity window time 0x606E*/
0x0,/*(INT16) Target Torque 0x6071*/
0x0,/*(UINT16) Max Torque 0x6072*/
0x0,/*(INT16) Torque Actual Value 0x6077*/
0x0,/*(INT32) Target Position 0x607A*/
0x0,/*(INT32) Home offset 0x607C*/
{2,0x0,0x0},/*TOBJ607D Software Position Limit (minLimit: -2000000000 / maxLimit: 2000000000)*/
0x0,/*(UINT32)Profile velocity in pp-mode 0x6081*/
0x0,/*(UINT32)Profile acceleration 0x6083*/
0x0,/*(UINT32)Profile deceleration 0x6084*/
0x0,/*(UINT32)Torque slope 0x6087*/
0x0,/*(INT8)Homing method 0x6098*/
{2,0x0,0x0},/*TOBJ6099 Homing speeds*/
0x0,/*(UINT32)Homing acceleratio 0x609A*/
0x0,/*(UINT32)Velocity offset 0x60B1*/
0x0,/*(UINT32)Torque offset 0x60B2*/
0x0,/*(UINT16)Touch probe function 0x60B8*/
0x0,/*(UINT16)Touch probe status 0x60B9*/
0x0,/*(INT32)Touch probe 1 positive edge 0x60BA*/
0x0,/*(INT32)Touch probe 1 negative edge 0x60BB*/
0x0,/*(INT32)Touch probe 2 positive edge 0x60BC*/
0x0,/*(INT32)Touch probe 2 negative edge 0x60BD*/
0x0,/*(INT16)Interpolation sub mode select 0x60C0*/
{2,1,-3},/*TOBJ60C2 Interpolation Time Period*/
0x0,/*(UINT16) Positive torque limit 0x60E0*/
0x0,/*(UINT16) Negative torque limit 0x60E1*/
0x0,/*(INT32) Following error actual value 0x60F4*/
0x0,/*(INT32) Position demand internal value 0x60FC*/
0x0,/*(UINT32) Digital inputs 0x60FD*/
{2,0x0,0x0},/*0x60FE (Software Position Limit) data*/
0x0,/*(INT32) Target Velocity    0x60FF*/
0x0/*(UINT32) Supported Drive Modes 0x6502*/
};

TOBJECT    OBJMEM ApplicationObjDic[3]
= {/* Object 0x1C12 */
   {NULL,NULL, 0x1C12, {DEFTYPE_UNSIGNED16, MAX_AXES | (OBJCODE_ARR << 8)}, asPDOAssignEntryDesc, aName0x1C12, &sRxPDOassign, NULL, NULL, 0x0000 },
   /* Object 0x1C13 */
   {NULL,NULL, 0x1C13, {DEFTYPE_UNSIGNED16, MAX_AXES | (OBJCODE_ARR << 8)}, asPDOAssignEntryDesc, aName0x1C13, &sTxPDOassign, NULL, NULL, 0x0000 },
/*ECATCHANGE_START(V5.11) COE1*/
   {NULL,NULL, 0xFFFF, {0, 0}, NULL, NULL, NULL, NULL, NULL, 0x000}}
/*ECATCHANGE_END(V5.11) COE1*/
;

TOBJECT    OBJMEM DefCiA402AxisObjDic[]
= {
    /* Object 0x1601 */
   {NULL,NULL, 0x1601, {DEFTYPE_PDOMAPPING, 2 | (OBJCODE_REC << 8)}, asEntryDesc0x1601, aName0x1601,NULL, NULL, NULL, 0x0000 },
    /* Object 0x1602 */
   {NULL,NULL, 0x1602, {DEFTYPE_PDOMAPPING, 2 | (OBJCODE_REC << 8)}, asEntryDesc0x1602, aName0x1602, NULL, NULL, NULL, 0x0000 },
   /* Object 0x1603 */
   {NULL,NULL, 0x1603, {DEFTYPE_PDOMAPPING, 2 | (OBJCODE_REC << 8)}, asEntryDesc0x1603, aName0x1603, NULL, NULL, NULL, 0x0000 },
   /* Object 0x1A01 */
   {NULL,NULL, 0x1A01, {DEFTYPE_PDOMAPPING, 2 | (OBJCODE_REC << 8)}, asEntryDesc0x1A01, aName0x1A01, NULL, NULL, NULL, 0x0000 },
   /* Object 0x1A02 */
   {NULL,NULL, 0x1A02, {DEFTYPE_PDOMAPPING, 3 | (OBJCODE_REC << 8)}, asEntryDesc0x1A02, aName0x1A02, NULL, NULL, NULL, 0x0000 },
   /* Object 0x1A03 */
   {NULL,NULL, 0x1A03, {DEFTYPE_PDOMAPPING, 3 | (OBJCODE_REC << 8)}, asEntryDesc0x1A03, aName0x1A03, NULL, NULL, NULL, 0x0000 },
   /* Object 0x603F */
   {NULL,NULL, 0x603F, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x603F, aName0x603F, NULL, NULL, NULL, 0x0000 },
   /* Object 0x6040 */
   {NULL,NULL, 0x6040, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6040, aName0x6040, NULL, NULL, NULL, 0x0000 },
   /* Object 0x6041 */
   {NULL,NULL, 0x6041, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6041, aName0x6041, NULL, NULL, NULL, 0x0000 },
   /* Object 0x6060 */
    {NULL,NULL, 0x6060, {DEFTYPE_INTEGER8 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6060, aName0x6060, NULL, NULL, NULL, 0x0000 },
   /* Object 0x6061 */
   {NULL,NULL, 0x6061, {DEFTYPE_INTEGER8 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6061, aName0x6061, NULL, NULL, NULL, 0x0000 },
   /* Object 0x6063 */
   {NULL,NULL, 0x6063, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6063, aName0x6063, NULL, NULL, NULL, 0x0000 },
   /* Object 0x6064 */
   {NULL,NULL, 0x6064, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6064, aName0x6064, NULL, NULL, NULL, 0x0000 },
   /* Object 0x6065 */
   {NULL,NULL, 0x6065, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6065, aName0x6065, NULL, NULL, NULL, 0x0000 },
   /* Object 0x606B */
   {NULL,NULL, 0x606B, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x606B, aName0x606B, NULL, NULL, NULL, 0x0000 },
   /* Object 0x606C */
   {NULL,NULL, 0x606C, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x606C, aName0x606C, NULL, NULL, NULL, 0x0000 },
   /* Object 0x606D */
   {NULL,NULL, 0x606D, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x606D, aName0x606D, NULL, NULL, NULL, 0x0000 },
   /* Object 0x606E */
   {NULL,NULL, 0x606E, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x606E, aName0x606E, NULL, NULL, NULL, 0x0000 },
   /* Object 0x6071 */
   {NULL,NULL, 0x6071, {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6071, aName0x6071, NULL, NULL, NULL, 0x0000 },
   /* Object 0x6072 */
   {NULL,NULL, 0x6072, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6072, aName0x6072, NULL, NULL, NULL, 0x0000 },
   /* Object 0x6077 */
   {NULL,NULL, 0x6077, {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6077, aName0x6077, NULL, NULL, NULL, 0x0000 },
   /* Object 0x607A */
   {NULL,NULL, 0x607A, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x607A, aName0x607A, NULL, NULL, NULL, 0x0000 },
   /* Object 0x607C */
   {NULL,NULL, 0x607C, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x607C, aName0x607C, NULL, NULL, NULL, 0x0000 },
   /* Object 0x607D */
   {NULL,NULL, 0x607D, {DEFTYPE_INTEGER32 , 2 | (OBJCODE_ARR << 8)}, asEntryDesc0x607D, aName0x607D, NULL, NULL, NULL, 0x0000 },
   /* Object 0x6081 */
   {NULL,NULL, 0x6081, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6081, aName0x6081, NULL, NULL, NULL, 0x0000 },
   /* Object 0x6083 */
   {NULL,NULL, 0x6083, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6083, aName0x6083, NULL, NULL, NULL, 0x0000 },
   /* Object 0x6084 */
   {NULL,NULL, 0x6084, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6084, aName0x6084, NULL, NULL, NULL, 0x0000 },
   /* Object 0x6087 */
   {NULL,NULL, 0x6087, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6087, aName0x6087, NULL, NULL, NULL, 0x0000 },
   /* Object 0x6098 */
   {NULL,NULL, 0x6098, {DEFTYPE_INTEGER8 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6098, aName0x6098, NULL, NULL, NULL, 0x0000 },
   /* Object 0x6099 */
   {NULL,NULL, 0x6099, {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)}, asEntryDesc0x6099, aName0x6099, NULL, NULL, NULL, 0x0000 },
   /* Object 0x609A */
   {NULL,NULL, 0x609A, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x609A, aName0x609A, NULL, NULL, NULL, 0x0000 },
   /* Object 0x60B1 */
   {NULL,NULL, 0x60B1, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x60B1, aName0x60B1, NULL, NULL, NULL, 0x0000 },
   /* Object 0x60B2 */
   {NULL,NULL, 0x60B2, {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x60B2, aName0x60B2, NULL, NULL, NULL, 0x0000 },
   /* Object 0x60B8 */
   {NULL,NULL, 0x60B8, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x60B8, aName0x60B8, NULL, NULL, NULL, 0x0000 },
   /* Object 0x60B9 */
   {NULL,NULL, 0x60B9, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x60B9, aName0x60B9, NULL, NULL, NULL, 0x0000 },
   /* Object 0x60BA */
   {NULL,NULL, 0x60BA, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x60BA, aName0x60BA, NULL, NULL, NULL, 0x0000 },
   /* Object 0x60B1 */
   {NULL,NULL, 0x60BB, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x60BB, aName0x60BB, NULL, NULL, NULL, 0x0000 },
   /* Object 0x60BC */
   {NULL,NULL, 0x60BC, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x60BC, aName0x60BC, NULL, NULL, NULL, 0x0000 },
   /* Object 0x60BD */
   {NULL,NULL, 0x60BD, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x60BD, aName0x60BD, NULL, NULL, NULL, 0x0000 },
   /* Object 0x60C0 */
   {NULL,NULL, 0x60C0, {DEFTYPE_INTEGER16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x60C0, aName0x60C0, NULL, NULL, NULL, 0x0000 },
   /* Object 0x60C2 */
   {NULL,NULL, 0x60C2, {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)}, asEntryDesc0x60C2, aName0x60C2, NULL, NULL, NULL, 0x0000 },
   /* Object 0x60E0 */
   {NULL,NULL, 0x60E0, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x60E0, aName0x60E0, NULL, NULL, NULL, 0x0000 },
   /* Object 0x60E1 */
   {NULL,NULL, 0x60E1, {DEFTYPE_UNSIGNED16 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x60E1, aName0x60E1, NULL, NULL, NULL, 0x0000 },
   /* Object 0x60F4 */
   {NULL,NULL, 0x60F4, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x60F4, aName0x60F4, NULL, NULL, NULL, 0x0000 },
   /* Object 0x60FC */
   {NULL,NULL, 0x60FC, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x60FC, aName0x60FC, NULL, NULL, NULL, 0x0000 },
   /* Object 0x60FD */
   {NULL,NULL, 0x60FD, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x60FD, aName0x60FD, NULL, NULL, NULL, 0x0000 },
   /* Object 0x60FE */
   {NULL,NULL, 0x60FE, {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)}, asEntryDesc0x60FE, aName0x60FE, NULL, NULL, NULL, 0x0000 },
   /* Object 0x60FF */
   {NULL,NULL, 0x60FF, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x60FF, aName0x60FF, NULL, NULL, NULL, 0x0000 },
   /* Object 0x6502 */
   {NULL,NULL, 0x6502, {DEFTYPE_UNSIGNED32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x6502, aName0x6502, NULL, NULL, NULL, 0x0000 },
   {NULL,NULL, 0xFFFF, {0, 0}, NULL, NULL, NULL, NULL, NULL, 0x000}}
;
/*-----------------------------------------------------------------------------------------
------
------    application specific functions
------
-----------------------------------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    0               Init CiA402 device successful
            ALSTATUSCODE_XX Init CiA402 device failed

 \brief    This function initializes the Axes structures
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 CiA402_Init(void)
{
    UINT16 result = 0;
     /*Reset Axis buffer*/
    HMEMSET(&LocalAxes,0,SIZEOF(TCiA402Axis));

    LocalAxes.bAxisIsActive = FALSE;
    LocalAxes.bBrakeApplied = TRUE;
    LocalAxes.bLowLevelPowerApplied = TRUE;
    LocalAxes.bHighLevelPowerApplied = FALSE;
    LocalAxes.bAxisFunctionEnabled = FALSE;
    LocalAxes.bConfigurationAllowed = TRUE;

    LocalAxes.i16State = STATE_NOT_READY_TO_SWITCH_ON;
    LocalAxes.u16PendingOptionCode = 0x00;

    LocalAxes.fCurPosition = 0;
    LocalAxes.u32CycleTime = 2000;
    LocalAxes.bAxisIsActive = 0;
    /***********************************
        init objects
    *************************************/
    /*set default values*/
    HMEMCPY(&LocalAxes.Objects,&DefCiA402ObjectValues,CIA402_OBJECTS_SIZE);

    /***********************************
        init objects dictionary entries
    *************************************/
    LocalAxes.ObjDic = (TOBJECT *) ALLOCMEM(SIZEOF(DefCiA402AxisObjDic));
    HMEMCPY(LocalAxes.ObjDic,&DefCiA402AxisObjDic,SIZEOF(DefCiA402AxisObjDic));

    //设定轴对象字典默认值
    LocalAxes.Objects.objModesOfOperation = CYCLIC_SYNC_POSITION_MODE;

    TOBJECT OBJMEM *pDiCEntry = LocalAxes.ObjDic;

    /*adapt Object index and assign Var pointer*/
    while(pDiCEntry->Index != 0xFFFF)
    {

        switch(pDiCEntry->Index)
        {
        case 0x1601:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.sRxPDOMap1;
            break;
        case 0x1602:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.sRxPDOMap2;
            break;
        case 0x1603:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.sRxPDOMap3;
            break;
        case 0x1A01:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.sTxPDOMap1;
            break;
        case 0x1A02:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.sTxPDOMap2;
            break;
        case 0x1A03:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.sTxPDOMap3;
            break;
        case 0x603F:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objErrorCode;
            break;
        case 0x6040:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objControlWord;
            break;
        case 0x6041:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objStatusWord;
            break;
        case 0x6060:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objModesOfOperation;
            break;
        case 0x6061:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objModesOfOperationDisplay;
            break;
        case 0x6063:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objPositionActualInValue;
            break;
        case 0x6064:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objPositionActualValue;
            break;
        case 0x6065:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objFollowingErrorWindow;
            break;
        case 0x606B:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objVelocityDemandValue;
            break;
        case 0x606C:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objVelocityActualValue;
            break;
        case 0x606D:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objVelocityWindow;
            break;
        case 0x606E:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objVelocityWindowTime;
            break;
        case 0x6071:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objTargetTorque;
            break;
        case 0x6072:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objMaxTorque;
            break;
        case 0x6077:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objTorqueActualValue;
            break;
        case 0x607A:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objTargetPosition;
            break;
        case 0x607C:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objHomeOffset;
            break;
        case 0x607D:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objSoftwarePositionLimit;
            break;
        case 0x6081:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objProfileVelocity;
            break;
        case 0x6083:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objProfileAcceleration;
            break;
        case 0x6084:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objProfileDeceleration;
            break;
        case 0x6087:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objTorqueSlope;
            break;
        case 0x6098:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objHomingMethod;
            break;
        case 0x6099:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objHomingSpeeds;
            break;
        case 0x609A:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objHomingAcceleration;
            break;
        case 0x60B1:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objVelocityOffset;
            break;
        case 0x60B2:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objTorqueOffset;
            break;
        case 0x60B8:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objTouchProbeFunction;
            break;
        case 0x60B9:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objTouchProbeStatus;
            break;
        case 0x60BA:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objTouchProbe1Positive;
            break;
        case 0x60BB:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objTouchProbe1Negative;
            break;
        case 0x60BC:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objTouchProbe2Positive;
            break;
        case 0x60BD:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objTouchProbe2Negative;
            break;
        case 0x60C0:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objInterpolationMode;
            break;
        case 0x60C2:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objInterpolationTimePeriod;
            break;
        case 0x60E0:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objPositiveTorqueLimit;
            break;
        case 0x60E1:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objNegativeTorqueLimit;
            break;
        case 0x60F4:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objFollowingErrorActual;
            break;
        case 0x60FC:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objPositionDemandInternal;
            break;
        case 0x60FD:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objDigitalInputs;
            break;
        case 0x60FE:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objDigitalOutputs;
            break;
        case 0x60FF:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objTargetVelocity;
            break;
        case 0x6502:
            pDiCEntry->pVarPtr = &LocalAxes.Objects.objSupportedDriveModes;
            break;
        default :
        break;
        }//switch(pDiCEntry->Index)

        /*increment object index*/
        pDiCEntry++;
    }//while(pDiCEntry->Index != 0xFFFF)
    return result;
}
/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    CiA402_DeallocateAxis
 \brief    Remove all allocated axes resources
*////////////////////////////////////////////////////////////////////////////////////////
void CiA402_DeallocateAxis(void)
{
    /*Remove object dictionary entries*/
    if(LocalAxes.ObjDic != NULL)
    {
        TOBJECT OBJMEM *pEntry = LocalAxes.ObjDic;

        while(pEntry->Index != 0xFFFF)
        {
            COE_RemoveDicEntry(pEntry->Index);

            pEntry++;
        }

        FREEMEM(LocalAxes.ObjDic);
    }
    nPdOutputSize = 0;
    nPdInputSize = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    CiA402-Statemachine
        This function handles the state machine for devices using the CiA402 profile.
        called cyclic from MainLoop()
        All described transition numbers are referring to the document
        "ETG Implementation Guideline for the CiA402 Axis Profile" located on the EtherCAT.org download section

*////////////////////////////////////////////////////////////////////////////////////////
void CiA402_StateMachine(void)
{
    TCiA402Axis *pCiA402Axis;
    UINT16 StatusWord = 0;
    UINT16 ControlWord6040 = 0;


    pCiA402Axis = &LocalAxes;
    StatusWord = pCiA402Axis->Objects.objStatusWord;
    ControlWord6040 = pCiA402Axis->Objects.objControlWord;

    /*clear statusword state and controlword processed complete bits*/
    StatusWord &= ~(STATUSWORD_STATE_MASK | STATUSWORD_REMOTE);

    /*skip state state transition if the previous transition is pending*/
    if(pCiA402Axis->u16PendingOptionCode!= 0x0)
    {
        return;
    }
    /*skip transition 1 and 2*/
    if(pCiA402Axis->i16State < STATE_READY_TO_SWITCH_ON && nAlStatus == STATE_OP)
        pCiA402Axis->i16State = STATE_READY_TO_SWITCH_ON;

    switch(pCiA402Axis->i16State)
    {
    case STATE_NOT_READY_TO_SWITCH_ON://未准备好接通电源
        StatusWord |= (STATUSWORD_STATE_NOTREADYTOSWITCHON);
        if(nAlStatus == STATE_OP)
        {
            // Automatic transition -> Communication shall be activated
            pCiA402Axis->i16State = STATE_SWITCH_ON_DISABLED; // Transition 1
        }
        else
        {
            /*
            CiA402 statemachine shall stay in "STATE_NOT_READY_TO_SWITCH_ON" if EtherCAT state is not OP.
            */
            pCiA402Axis->i16State = STATE_NOT_READY_TO_SWITCH_ON; // stay in current state
        }

        break;
    case STATE_SWITCH_ON_DISABLED://不可接通电源
        StatusWord |= (STATUSWORD_STATE_SWITCHEDONDISABLED);
        if ((ControlWord6040 & CONTROLWORD_COMMAND_SHUTDOWN_MASK) == CONTROLWORD_COMMAND_SHUTDOWN)
        {
            pCiA402Axis->i16State = STATE_READY_TO_SWITCH_ON;
        }
        break;
    case STATE_READY_TO_SWITCH_ON://准备好接通电源
        StatusWord |= (STATUSWORD_STATE_READYTOSWITCHON);
        if (((ControlWord6040 & CONTROLWORD_COMMAND_QUICKSTOP_MASK) == CONTROLWORD_COMMAND_QUICKSTOP)
            || ((ControlWord6040 & CONTROLWORD_COMMAND_DISABLEVOLTAGE_MASK) == CONTROLWORD_COMMAND_DISABLEVOLTAGE))//disablevoltage
        {
            pCiA402Axis->i16State = STATE_SWITCH_ON_DISABLED;
        }
        else if (((ControlWord6040 & CONTROLWORD_COMMAND_SWITCHON_MASK) == CONTROLWORD_COMMAND_SWITCHON) ||
                ((ControlWord6040 & CONTROLWORD_COMMAND_SWITCHON_ENABLEOPERATION_MASK) == CONTROLWORD_COMMAND_SWITCHON_ENABLEOPERATION))//enableoperation
            {
                pCiA402Axis->i16State = STATE_SWITCHED_ON;
            }
        break;
    case STATE_SWITCHED_ON://已开始供电
        StatusWord |= (STATUSWORD_STATE_SWITCHEDON);

        if ((ControlWord6040 & CONTROLWORD_COMMAND_SHUTDOWN_MASK) == CONTROLWORD_COMMAND_SHUTDOWN)
        {
            pCiA402Axis->i16State = STATE_READY_TO_SWITCH_ON;

        }
        else if (((ControlWord6040 & CONTROLWORD_COMMAND_QUICKSTOP_MASK) == CONTROLWORD_COMMAND_QUICKSTOP
                || (ControlWord6040 & CONTROLWORD_COMMAND_DISABLEVOLTAGE_MASK) == CONTROLWORD_COMMAND_DISABLEVOLTAGE))
        {
            pCiA402Axis->i16State = STATE_SWITCH_ON_DISABLED;

        }
        else if ((ControlWord6040 & CONTROLWORD_COMMAND_ENABLEOPERATION_MASK) == CONTROLWORD_COMMAND_ENABLEOPERATION)
        {
            pCiA402Axis->i16State = STATE_OPERATION_ENABLED;
            //The Axis function shall be enabled and all internal set-points cleared.
        }
        break;
    case STATE_OPERATION_ENABLED://可操作
        StatusWord |= (STATUSWORD_STATE_OPERATIONENABLED);

        if ((ControlWord6040 & CONTROLWORD_COMMAND_DISABLEOPERATION_MASK) == CONTROLWORD_COMMAND_DISABLEOPERATION)
        {
           pCiA402Axis->i16State = STATE_SWITCHED_ON;
        }
        else if ((ControlWord6040 & CONTROLWORD_COMMAND_QUICKSTOP_MASK) == CONTROLWORD_COMMAND_QUICKSTOP)
        {
           pCiA402Axis->i16State = STATE_QUICK_STOP_ACTIVE;
        }
        else if ((ControlWord6040 & CONTROLWORD_COMMAND_SHUTDOWN_MASK) == CONTROLWORD_COMMAND_SHUTDOWN)
        {
           pCiA402Axis->i16State = STATE_READY_TO_SWITCH_ON;
        }
        else if ((ControlWord6040 & CONTROLWORD_COMMAND_DISABLEVOLTAGE_MASK) == CONTROLWORD_COMMAND_DISABLEVOLTAGE)
        {
           pCiA402Axis->i16State = STATE_SWITCH_ON_DISABLED;
        }
        break;
    case STATE_QUICK_STOP_ACTIVE://急停状态
        StatusWord |= STATUSWORD_STATE_QUICKSTOPACTIVE;
        if ((ControlWord6040 & CONTROLWORD_COMMAND_DISABLEVOLTAGE_MASK) == CONTROLWORD_COMMAND_DISABLEVOLTAGE)
        {
            pCiA402Axis->i16State = STATE_SWITCH_ON_DISABLED;
        }
        /*NOTE: it is not recommend to support transition 16 */
        break;
    case STATE_FAULT_REACTION_ACTIVE://出错反应
        StatusWord |= (STATUSWORD_STATE_FAULTREACTIONACTIVE);
        // Automatic transition
        pCiA402Axis->i16State = STATE_FAULT;// Transition 14
        break;
    case STATE_FAULT://出错
        StatusWord |= (STATUSWORD_STATE_FAULT);
        if ((ControlWord6040 & CONTROLWORD_COMMAND_FAULTRESET_MASK) == CONTROLWORD_COMMAND_FAULTRESET)
        {
            pCiA402Axis->i16State = STATE_SWITCH_ON_DISABLED;// Transition 15
        }
        break;

    default:    //the sate variable is set to in invalid value => rest Axis
        StatusWord = (STATUSWORD_STATE_NOTREADYTOSWITCHON);
        pCiA402Axis->i16State = STATE_NOT_READY_TO_SWITCH_ON;
        break;

    }// switch(current state)

    /*Update operational functions (the low level power supply is always TRUE*/
    switch(pCiA402Axis->i16State)
    {
    case STATE_NOT_READY_TO_SWITCH_ON://为准备好接通电源
    case STATE_SWITCH_ON_DISABLED://不可接通电源
    case STATE_READY_TO_SWITCH_ON://准备好接通电源
        pCiA402Axis->bBrakeApplied = TRUE;
        pCiA402Axis->bHighLevelPowerApplied =  FALSE;
        pCiA402Axis->bAxisFunctionEnabled = FALSE;
        pCiA402Axis->bConfigurationAllowed = TRUE;
        break;
    case STATE_SWITCHED_ON://已开始供电
        pCiA402Axis->bBrakeApplied = TRUE;
        pCiA402Axis->bHighLevelPowerApplied =  TRUE;
        pCiA402Axis->bAxisFunctionEnabled = FALSE;
        pCiA402Axis->bConfigurationAllowed = TRUE;
        break;
    case STATE_OPERATION_ENABLED://可操作
    case STATE_QUICK_STOP_ACTIVE://急停状态
    case STATE_FAULT_REACTION_ACTIVE://出错反应
        pCiA402Axis->bBrakeApplied = TRUE;
        pCiA402Axis->bHighLevelPowerApplied =  TRUE;
        pCiA402Axis->bAxisFunctionEnabled = TRUE;
        pCiA402Axis->bConfigurationAllowed = FALSE;
        break;
    case STATE_FAULT://出错
        pCiA402Axis->bBrakeApplied = TRUE;
        pCiA402Axis->bHighLevelPowerApplied =  FALSE;
        pCiA402Axis->bAxisFunctionEnabled = FALSE;
        pCiA402Axis->bConfigurationAllowed = TRUE;
        break;
    default:
        pCiA402Axis->bBrakeApplied = TRUE;
        pCiA402Axis->bHighLevelPowerApplied =  FALSE;
        pCiA402Axis->bAxisFunctionEnabled = FALSE;
        pCiA402Axis->bConfigurationAllowed = TRUE;
        break;
    }
    if( pCiA402Axis->bHighLevelPowerApplied == TRUE)
        StatusWord |= STATUSWORD_VOLTAGE_ENABLED;
    else
        StatusWord &= ~STATUSWORD_VOLTAGE_ENABLED;
    /*state transition finished set controlword complete bit and update status object 0x6041*/
    pCiA402Axis->Objects.objStatusWord = (StatusWord | STATUSWORD_REMOTE);

}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    CiA402_DummyMotionControl
 \brief this functions provides an simple feedback functionality
*////////////////////////////////////////////////////////////////////////////////////////
void CiA402_DummyMotionControl(TCiA402Axis *pCiA402Axis)
{
    float IncFactor    = (float)0.0010922 * (float) pCiA402Axis->u32CycleTime;

    INT32 i32TargetVelocity = 0;

    /*Motion Controller shall only be triggered if application is trigger by DC Sync Signals,
    and a valid mode of operation is set*/

    /*calculate actual position */
    pCiA402Axis->fCurPosition += ((double)pCiA402Axis->Objects.objVelocityActualValue) * IncFactor;
    pCiA402Axis->Objects.objPositionActualValue = (INT32)(pCiA402Axis->fCurPosition);


    if(pCiA402Axis->bAxisFunctionEnabled &&
    pCiA402Axis->bLowLevelPowerApplied &&
    pCiA402Axis->bHighLevelPowerApplied &&
    !pCiA402Axis->bBrakeApplied)
    {
        if((pCiA402Axis->Objects.objSoftwarePositionLimit.i32MaxLimit> pCiA402Axis->Objects.objPositionActualValue
            || pCiA402Axis->Objects.objPositionActualValue > pCiA402Axis->Objects.objTargetPosition) &&
            (pCiA402Axis->Objects.objSoftwarePositionLimit.i32MinLimit < pCiA402Axis->Objects.objPositionActualValue
            || pCiA402Axis->Objects.objPositionActualValue < pCiA402Axis->Objects.objTargetPosition))
        {
            pCiA402Axis->Objects.objStatusWord &= ~STATUSWORD_INTERNAL_LIMIT;

            switch(pCiA402Axis->Objects.objModesOfOperationDisplay)
            {
            case CYCLIC_SYNC_POSITION_MODE:
                if(IncFactor != 0)
                    i32TargetVelocity = (pCiA402Axis->Objects.objTargetPosition - pCiA402Axis->Objects.objPositionActualValue) / ((long)IncFactor);
                else
                    i32TargetVelocity = 0;
                break;
            case CYCLIC_SYNC_VELOCITY_MODE:
                if(pCiA402Axis->i16State == STATE_OPERATION_ENABLED)
                    i32TargetVelocity = pCiA402Axis->Objects.objTargetVelocity;
                else
                        i32TargetVelocity = 0;
                break;
            default:
                break;
            }
        }
        else
        {
            pCiA402Axis->Objects.objStatusWord |= STATUSWORD_INTERNAL_LIMIT;
        }
    }
    pCiA402Axis->Objects.objVelocityActualValue= i32TargetVelocity;

    /*Accept new mode of operation*/
    pCiA402Axis->Objects.objModesOfOperationDisplay = pCiA402Axis->Objects.objModesOfOperation;

}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    CiA402-Application
 \brief check if a state transition is pending and pass desired ramp-code to CiA402TransitionAction()
 \brief if this functions returns true the state transition is finished.
*////////////////////////////////////////////////////////////////////////////////////////
void CiA402_Application(TCiA402Axis *pCiA402Axis)
{
    /*clear "Drive follows the command value" flag if the target values from the master overwritten by the local application*/
    if(pCiA402Axis->u16PendingOptionCode != 0 &&
        (pCiA402Axis->Objects.objModesOfOperationDisplay == CYCLIC_SYNC_POSITION_MODE ||
        pCiA402Axis->Objects.objModesOfOperationDisplay == CYCLIC_SYNC_VELOCITY_MODE))
    {
        pCiA402Axis->Objects.objStatusWord &= ~ STATUSWORD_DRIVE_FOLLOWS_COMMAND;//drive follows command
    }
    else
        pCiA402Axis->Objects.objStatusWord |= STATUSWORD_DRIVE_FOLLOWS_COMMAND;


/*    switch(pCiA402Axis->u16PendingOptionCode)
    {
    case 0x605A:
        state transition 11 is pending analyse shutdown option code (0x605A)
        {
            UINT16 ramp = pCiA402Axis->Objects.objQuickStopOptionCode;
            masked and execute specified quick stop ramp characteristic
            if(pCiA402Axis->Objects.objQuickStopOptionCode > 4 && pCiA402Axis->Objects.objQuickStopOptionCode <9)
            {
                if(pCiA402Axis->Objects.objQuickStopOptionCode == 5)
                    ramp = 1;
                if(pCiA402Axis->Objects.objQuickStopOptionCode == 6)
                    ramp = 2;
                if(pCiA402Axis->Objects.objQuickStopOptionCode == 7)
                    ramp = 3;
                if(pCiA402Axis->Objects.objQuickStopOptionCode == 8)
                    ramp = 4;
            }

            if(CiA402_TransitionAction(ramp,pCiA402Axis))
            {
                quick stop ramp is finished complete state transition
                pCiA402Axis->u16PendingOptionCode = 0x0;
                if(pCiA402Axis->Objects.objQuickStopOptionCode > 0 && pCiA402Axis->Objects.objQuickStopOptionCode < 5)
                {
                    pCiA402Axis->i16State = STATE_SWITCH_ON_DISABLED;    //continue state transition 12
                }
                else if(pCiA402Axis->Objects.objQuickStopOptionCode > 4 && pCiA402Axis->Objects.objQuickStopOptionCode < 9)
                    pCiA402Axis->Objects.objStatusWord |= STATUSWORD_TARGET_REACHED;
            }
        }
        break;
    case 0x605B:
        state transition 8 is pending analyse shutdown option code (0x605B)
        {
            if(CiA402_TransitionAction(pCiA402Axis->Objects.objShutdownOptionCode,pCiA402Axis))
            {
                shutdown ramp is finished complete state transition
                pCiA402Axis->u16PendingOptionCode = 0x0;
                pCiA402Axis->i16State = STATE_READY_TO_SWITCH_ON;    //continue state transition 8
            }
        }
        break;
    case 0x605C:
        state transition 5 is pending analyse Disable operation option code (0x605C)
        {
            if(CiA402_TransitionAction(pCiA402Axis->Objects.objDisableOperationOptionCode,pCiA402Axis))
            {
                disable operation ramp is finished complete state transition
                pCiA402Axis->u16PendingOptionCode = 0x0;
                pCiA402Axis->i16State = STATE_SWITCHED_ON;    //continue state transition 5
            }
        }
        break;

    case 0x605E:
        state transition 14 is pending analyse Fault reaction option code (0x605E)
        {
            if(CiA402_TransitionAction(pCiA402Axis->Objects.objFaultReactionCode,pCiA402Axis))
            {
                fault reaction ramp is finished complete state transition
                pCiA402Axis->u16PendingOptionCode = 0x0;
                pCiA402Axis->i16State = STATE_FAULT;    //continue state transition 14
            }
        }
        break;
    default:
        //pending transition code is invalid => values from the master are used
        pCiA402Axis->Objects.objStatusWord |= STATUSWORD_DRIVE_FOLLOWS_COMMAND;
        break;
    }*/
    if(bDcSyncActive
        && (pCiA402Axis->u32CycleTime != 0)
        && ((pCiA402Axis->Objects.objSupportedDriveModes >> (pCiA402Axis->Objects.objModesOfOperation - 1)) & 0x1)) //Mode of Operation (0x6060) - 1 specifies the Bit within Supported Drive Modes (0x6502)
    {
        CiA402_DummyMotionControl(pCiA402Axis);
    }



}
/////////////////////////////////////////////////////////////////////////////////////////
/**
\brief    This function will called from the synchronisation ISR 
            or from the mainloop if no synchronisation is supported
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_Application(void)
{

        if(LocalAxes.bAxisIsActive)
            CiA402_Application(&LocalAxes);

}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param ErrorCode

 \brief    CiA402_LocalError
 \brief this function is called if an error was detected
*////////////////////////////////////////////////////////////////////////////////////////

void CiA402_LocalError(UINT16 ErrorCode)
{
        if(LocalAxes.bAxisIsActive)
        {
            LocalAxes.i16State = STATE_FAULT_REACTION_ACTIVE;
            LocalAxes.Objects.objErrorCode = ErrorCode;
        }

}

/*-----------------------------------------------------------------------------------------
------
------    generic functions
------
-----------------------------------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    The function is called when an error state was acknowledged by the master

*////////////////////////////////////////////////////////////////////////////////////////

void    APPL_AckErrorInd(UINT16 stateTrans)
{

}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from INIT to PREOP when
           all general settings were checked to start the mailbox handler. This function
           informs the application about the state transition, the application can refuse
           the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete
           the transition by calling ECAT_StateChange.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from PREEOP to INIT
           to stop the mailbox handler. This functions informs the application
           about the state transition, the application cannot refuse
           the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from SAFEOP to PREEOP
             to stop the input handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopInputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from SAFEOP to OP when
             all general settings were checked to start the output handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete
           the transition by calling ECAT_StateChange.
*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartOutputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from OP to SAFEOP
             to stop the output handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopOutputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\return     0(ALSTATUSCODE_NOERROR), NOERROR_INWORK
\param      pInputSize  pointer to save the input process data length
\param      pOutputSize  pointer to save the output process data length

\brief    This function calculates the process data sizes from the actual SM-PDO-Assign
            and PDO mapping
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_GenerateMapping(UINT16 *pInputSize,UINT16 *pOutputSize)
{
    UINT16 result = ALSTATUSCODE_NOERROR;
    UINT16 u16cnt = 0;
    UINT16 InputSize = 0;
    UINT16 OutputSize = 0;
    TOBJECT OBJMEM *pDiCEntry = NULL;
    if(!LocalAxes.bAxisIsActive)
    {
    /*add objects to dictionary*/
       pDiCEntry = LocalAxes.ObjDic;
       while(pDiCEntry->Index != 0xFFFF)
       {
          result = COE_AddObjectToDic(pDiCEntry);
          if(result != 0)
          {
            return result;
          }
          pDiCEntry++;    //get next entry
       }
       LocalAxes.bAxisIsActive = TRUE;
     }
    /*Scan object 0x1C12 RXPDO assign*/

     switch ((sRxPDOassign.aEntries[0] & 0x000F))    //mask Axis type (supported modes)
     {
         case 1:
             /*drive mode supported    csp (cyclic sync position) : bit 7*/
             LocalAxes.Objects.objSupportedDriveModes = 0x80;
             for(u16cnt =0 ; u16cnt < LocalAxes.Objects.sRxPDOMap1.u16SubIndex0;u16cnt++)
             {
                 OutputSize +=(UINT16)(LocalAxes.Objects.sRxPDOMap1.aEntries[u16cnt] & 0xFF);
             }
             break;
         case 2:
                 /*drive mode supported    csv(cyclic sync velocity) : bit 8*/
             LocalAxes.Objects.objSupportedDriveModes= 0x100;
             for(u16cnt =0 ; u16cnt < LocalAxes.Objects.sRxPDOMap2.u16SubIndex0;u16cnt++)
             {
                 OutputSize += (UINT16)(LocalAxes.Objects.sRxPDOMap2.aEntries[u16cnt] & 0xFF);;
             }
             break;
         case 3:
                 /*drive mode supported    cst(cyclic sync torque) : bit 9*/
             LocalAxes.Objects.objSupportedDriveModes= 0x200;
             for(u16cnt =0 ; u16cnt < LocalAxes.Objects.sRxPDOMap3.u16SubIndex0;u16cnt++)
             {
                 OutputSize += (UINT16)(LocalAxes.Objects.sRxPDOMap3.aEntries[u16cnt] & 0xFF);;
             }
             break;
         default:
        	 LocalAxes.Objects.objSupportedDriveModes = 0x80;
        	 for(u16cnt =0 ; u16cnt < LocalAxes.Objects.sRxPDOMap1.u16SubIndex0;u16cnt++)
        	 {
        		 OutputSize +=(UINT16)(LocalAxes.Objects.sRxPDOMap1.aEntries[u16cnt] & 0xFF);
        	 }
        	 break;
     }
    OutputSize = OutputSize >> 3;
    if(result == 0)
    {
        /*Scan Object 0x1C13 TXPDO assign*/
        switch ((sTxPDOassign.aEntries[0] & 0x000F))    //mask Axis type (supported modes)
        {
        case 1: /*csp*/
            for(u16cnt =0 ; u16cnt < LocalAxes.Objects.sTxPDOMap1.u16SubIndex0;u16cnt++)
            {
                InputSize +=(UINT16)(LocalAxes.Objects.sTxPDOMap1.aEntries[u16cnt] & 0xFF);
            }
            break;
        case 2: /*csv*/
            for(u16cnt =0 ; u16cnt < LocalAxes.Objects.sTxPDOMap2.u16SubIndex0;u16cnt++)
            {
                InputSize +=(UINT16)(LocalAxes.Objects.sTxPDOMap2.aEntries[u16cnt] & 0xFF);
            }
            break;
        case 3: /*cst*/
            for(u16cnt =0 ; u16cnt < LocalAxes.Objects.sTxPDOMap3.u16SubIndex0;u16cnt++)
            {
                InputSize +=(UINT16)(LocalAxes.Objects.sTxPDOMap3.aEntries[u16cnt] & 0xFF);
            }
            break;
        default:
            for(u16cnt =0 ; u16cnt < LocalAxes.Objects.sTxPDOMap1.u16SubIndex0;u16cnt++)
            {
                InputSize +=(UINT16)(LocalAxes.Objects.sTxPDOMap1.aEntries[u16cnt] & 0xFF);
            }
            break;
        }
        InputSize = InputSize >> 3;
    }
    *pInputSize = InputSize;
    *pOutputSize = OutputSize;
    return result;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param    pIntMask    pointer to the AL Event Mask which will be written to the AL event Mask
                        register (0x204) when this function is succeeded. The event mask can be adapted
                        in this function
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from PREOP to SAFEOP when
             all general settings were checked to start the input handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
            The return code NOERROR_INWORK can be used, if the application cannot confirm
            the state transition immediately, in that case the application need to be complete
            the transition by calling ECAT_StateChange.
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_StartInputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}


/** @} */

