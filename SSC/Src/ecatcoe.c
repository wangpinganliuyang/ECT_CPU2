/**
\addtogroup CoE CAN Application Profile over EtherCAT
@{
*/

/**
\file ecatcoe.c
\author EthercatSSC@beckhoff.com
\brief Implementation
This file contains the CoE mailbox interface

\version 5.11

<br>Changes to version V5.0:<br>
V5.11 COE4: "change prototype of ""COE_ContinueInd()"" return <> 0 if a failure occurred"<br>
V5.11 ECAT10: change PROTO handling to prevent compiler errors<br>
V5.11 TEST6: add test object to trigger Slave-to-Slave communication<br>
V5.11 TEST7: add test behaviour to send an emergency on every SDO request (in SafeOP)<br>
<br>Changes to version V4.40:<br>
V5.0 SDO7: "SDOS_SdoInfoInd()" never return pending SDO Info service. Delete "NOERROR_INWORK" handling.<br>
<br>Changes to version V4.08:<br>
V4.40 SDO1: add initial value for "nSdoInfoFragmentsLeft"<br>
V4.40 MBX6: change return value if no mailbox buffer is available<br>
V4.08 MBX 1: If the switch MAILBOX_QUEUE was set, we have to put all SDO Info Responses in the Send Queue
*/

/*---------------------------------------------------------------------------------------
------
------    Includes
------
---------------------------------------------------------------------------------------*/

#include "GDC16.h"


#define    _ECATCOE_    1
#include "ecatcoe.h"
#undef      _ECATCOE_

/*---------------------------------------------------------------------------------------
------
------    internal Types and Defines
------
---------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------
------
------    static variables
------
---------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------
------
------    static functions
------
---------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------
------
------    functions
------
---------------------------------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////////////////////
/**

 \brief    This function intialize the CoE Interface.
*////////////////////////////////////////////////////////////////////////////////////////

void COE_Init(void)
{
    pCoeSendStored = 0;
    nSdoInfoFragmentsLeft = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param     pCoeMbx      Pointer to the received mailbox data from the master.

 \return    result of the operation (0 (success) or mailbox error code (MBXERR_.... defined in
            mailbox.h))

 \brief    This function is called when a CoE (CAN application layer over EtherCAT) service is received from
             the master.
*////////////////////////////////////////////////////////////////////////////////////////
UINT8 COE_ServiceInd(TCOEMBX MBXMEM *pCoeMbx)
{
    UINT8 result = 0;

    switch ((pCoeMbx->CoeHeader & COEHEADER_COESERVICEMASK) >> COEHEADER_COESERVICESHIFT)
    {
    case COESERVICE_SDOREQUEST:
        /* SDO-Request received, call SDOS_SdoInd to process the SDO-Request
           if an existing SDO-Stack shall be used, the corresponding function
            should be called */
        result = SDOS_SdoInd( (TINITSDOMBX MBXMEM *) pCoeMbx );
        break;

    case COESERVICE_SDOINFO:
    case COESERVICE_SDORESPONSE:
    case COESERVICE_EMERGENCY:
    case COESERVICE_TXPDO:
    case COESERVICE_RXPDO:
    case COESERVICE_TXPDOREMREQ:
    case COESERVICE_RXPDOREMREQ:
        /* these CoE services are not supported yet */
        result = MBXERR_SERVICENOTSUPPORTED;
        break;

    default:
        result = MBXERR_INVALIDHEADER;
        break;
    }
    return result;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param     pMbx      Pointer to the free mailbox to sent.

 \return    result of the operation (0 (success)

 \brief    This function is called when a CoE service to be sent is stored and can
 \brief  be put in the send mailbox.
*////////////////////////////////////////////////////////////////////////////////////////
UINT8 COE_ContinueInd(TMBX MBXMEM * pMbx)
/*ECATCHANGE_END(V5.11) COE4*/
{
    if (pCoeSendStored)
    {
        /* send the stored CoE service which could not be sent before */
        MBX_MailboxSendReq(pCoeSendStored, 0);
        pCoeSendStored = 0;
    }
    else
    {
        /* send the next fragment of the last CoE service (only for SDO-Information possible) */
        /* in mailbox queue mode pMbx is always 0, so a mailbox buffer shall be get */
        pMbx = (TMBX MBXMEM *) APPL_AllocMailboxBuffer((SIZEOF(TMBX)));
//         it shall be checked if a valid pointer was returned
        if (pMbx == NULL)
        {
            return MBXERR_NOMOREMEMORY;
        }
        else
        {
        	//修改代码
        	pMbx->MbxHeader.Length = aSdoInfoHeader[0];
        	pMbx->MbxHeader.Address = aSdoInfoHeader[1];
        	pMbx->MbxHeader.Flags = aSdoInfoHeader[2];
        	pMbx->Data[0] = aSdoInfoHeader[3];
        	pMbx->Data[1] = aSdoInfoHeader[4];
        	pMbx->Data[2] = aSdoInfoHeader[5];
        	pMbx->Data[3] = aSdoInfoHeader[6];
        	//备注，aSdoInfoHeader，6字节邮箱头+2字节COE头+4字节SDO INFO头+2字节SDO list头
            /* call SDOS_SdoInfoInd to generate and send the next fragment */
            SDOS_SdoInfoInd( (TSDOINFORMATION MBXMEM *) pMbx );
        }
    }

    return 0;
}

/** @} */



