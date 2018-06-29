/*
 * GDC_PV1_0.c
 *
 *  Created on: 2018年6月25日
 *      Author: wangpingan
 *      初始化和数控系统交互的参数
 */
#include "GDC16.h"
#include "GDC_PV1_0.h"

GDC_P Gdc_Para;
const TSDOINFOENTRYDESC sEntryDesc0x2452 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};
const TSDOINFOENTRYDESC sEntryDesc0x23FD = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
const TSDOINFOENTRYDESC sEntryDesc0x23FE = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
const unsigned char aName0x2452[] = "Dcshifting";
const unsigned char aName0x23FD[] = "Warning1";
const unsigned char aName0x23FE[] = "Warning2";
TOBJECT DefGDC_PV1_0ObjDic[]= {
  //object 0x2452 --p1107 母线电压偏移量
  {NULL,NULL, 0x2452, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2452, aName0x2452, NULL, NULL, NULL, 0x0000 },
  //object 0x23FD --r1021 子报警信息
  {NULL,NULL, 0x23FD, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x23FD, aName0x23FD, NULL, NULL, NULL, 0x0000 },
   //object 0x23FE --r1022 主报警信息
  {NULL,NULL, 0x23FE, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x23FE, aName0x23FE, NULL, NULL, NULL, 0x0000 },
  {NULL,NULL, 0xFFFF, {0, 0}, NULL, NULL, NULL, NULL, NULL, 0x000}
};

void GDC_PV1_0_Init(void)
{
    GDC_P *v = &Gdc_Para;
    memset(&Gdc_Para,0,sizeof(GDC_P));
    v->Objects.p1106 = 0;
    v->Objects.r1021 = 0;
    v->Objects.r1022 = 0;
    v->ObjDic = (TOBJECT *) malloc(sizeof(DefGDC_PV1_0ObjDic));
    memcpy(v->ObjDic,&DefGDC_PV1_0ObjDic,sizeof(DefGDC_PV1_0ObjDic));
    TOBJECT  *pDiCEntry = Gdc_Para.ObjDic;
    while(pDiCEntry->Index != 0xFFFF)
    {
        switch(pDiCEntry->Index)
        {
        case 0x2452:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.p1106;
            break;
        case 0x23FD:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.r1021;
//            pDiCEntry->Read = OBJ_Read;
            break;
        case 0x23FE:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.r1022;
//            pDiCEntry->Read = OBJ_Read;
            break;
        default :
            break;
        }
        pDiCEntry++;
    }

}

void Gdc_Para_RemObject(void)
{
    if(Gdc_Para.ObjDic != NULL)
    {
        TOBJECT  *pEntry = Gdc_Para.ObjDic;

        while(pEntry->Index != 0xFFFF)
        {
            COE_RemoveDicEntry(pEntry->Index);

            pEntry++;
        }
        free(Gdc_Para.ObjDic);
    }
}

UINT16 Gdc_Para_AddObject(void)
{
    UINT16 result = 0;
    TOBJECT *pDiCEntry = NULL;
    pDiCEntry = Gdc_Para.ObjDic;
    while(pDiCEntry->Index != 0xFFFF)
    {
        result = COE_AddObjectToDic(pDiCEntry);
        if(result != 0)
        {
            return result;
        }
        pDiCEntry++;    //get next entry
    }
    return 0;
}
