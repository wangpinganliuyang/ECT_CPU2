/*
 * GDC_PV1_0.c
 *
 *  Created on: 2018年6月25日
 *      Author: wangpingan
 *      初始化和数控系统交互的参数
 *      测试数据
 */
#include "GDC16.h"
#include "GDC_PV1_0.h"

GDC_P Gdc_Para;
const TSDOINFOENTRYDESC sEntryDesc0x2004 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
const TSDOINFOENTRYDESC sEntryDesc0x2005 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
const TSDOINFOENTRYDESC sEntryDesc0x2007 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
const TSDOINFOENTRYDESC sEntryDesc0x2009 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
const TSDOINFOENTRYDESC sEntryDesc0x200B = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
const TSDOINFOENTRYDESC sEntryDesc0x200C = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
const TSDOINFOENTRYDESC sEntryDesc0x2018 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
const TSDOINFOENTRYDESC sEntryDesc0x2034 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};

const TSDOINFOENTRYDESC sEntryDesc0x2168[] = {
                                            {DEFTYPE_UNSIGNED8, 0x08, ACCESS_READ},
                                            {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE},
                                            {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE}};

const TSDOINFOENTRYDESC sEntryDesc0x217C = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};
const TSDOINFOENTRYDESC sEntryDesc0x217E = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};
const TSDOINFOENTRYDESC sEntryDesc0x2180 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};
const TSDOINFOENTRYDESC sEntryDesc0x2181 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};


const TSDOINFOENTRYDESC sEntryDesc0x2197[] = {
                                              {DEFTYPE_UNSIGNED8, 0x08, ACCESS_READ},
                                              {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE},
                                              {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE}};


const TSDOINFOENTRYDESC sEntryDesc0x219A[] = {
                                              {DEFTYPE_UNSIGNED8, 0x08, ACCESS_READ},
                                              {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE},
                                              {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE}};

const TSDOINFOENTRYDESC sEntryDesc0x21A6 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};
const TSDOINFOENTRYDESC sEntryDesc0x21A8 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};
const TSDOINFOENTRYDESC sEntryDesc0x21A9 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};

const TSDOINFOENTRYDESC sEntryDesc0x21B9[] = {
                                            {DEFTYPE_UNSIGNED8, 0x08, ACCESS_READ},
                                            {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE},
                                            {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE}};

const TSDOINFOENTRYDESC sEntryDesc0x23FD = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
const TSDOINFOENTRYDESC sEntryDesc0x23FE = {DEFTYPE_INTEGER32, 0x20, ACCESS_READ};
const TSDOINFOENTRYDESC sEntryDesc0x2452 = {DEFTYPE_INTEGER32, 0x20, ACCESS_READWRITE};

const unsigned char aName0x2004[] = "p";
const unsigned char aName0x2005[] = "p";
const unsigned char aName0x2007[] = "p";
const unsigned char aName0x2009[] = "p";
const unsigned char aName0x200B[] = "p";
const unsigned char aName0x200C[] = "p";
const unsigned char aName0x2018[] = "p";
const unsigned char aName0x2034[] = "p";

const unsigned char aName0x2168[] = "S\000M\000M\000\377";

const unsigned char aName0x217C[] = "p";
const unsigned char aName0x217E[] = "p";
const unsigned char aName0x2180[] = "p";
const unsigned char aName0x2181[] = "p";

const unsigned char aName0x2197[] = "S\000M\000M\000\377";
const unsigned char aName0x219A[] = "S\000M\000M\000\377";

const unsigned char aName0x21A6[] = "p";
const unsigned char aName0x21A8[] = "p";
const unsigned char aName0x21A9[] = "p";
const unsigned char aName0x21B9[] = "S\000M\000M\000\377";

const unsigned char aName0x23FD[] = "Warning1";
const unsigned char aName0x23FE[] = "Warning2";
const unsigned char aName0x2452[] = "Dcshifting";


TOBJECT DefGDC_PV1_0ObjDic[]= {
  {NULL,NULL, 0x2004, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2004, aName0x2004, NULL, NULL, NULL, 0x0000 },////object 0x2452 --p1107 母线电压偏移量
  {NULL,NULL, 0x2005, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2005, aName0x2005, NULL, NULL, NULL, 0x0000 },////object 0x23FD --r1021 子报警信息
  {NULL,NULL, 0x2007, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2007, aName0x2007, NULL, NULL, NULL, 0x0000 },//object 0x23FE --r1022 主报警信息
  {NULL,NULL, 0x2009, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2009, aName0x2009, NULL, NULL, NULL, 0x0000 },////object 0x2452 --p1107 母线电压偏移量
  {NULL,NULL, 0x200B, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x200B, aName0x200B, NULL, NULL, NULL, 0x0000 },////object 0x23FD --r1021 子报警信息
  {NULL,NULL, 0x200C, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x200C, aName0x200C, NULL, NULL, NULL, 0x0000 },//object 0x23FE --r1022 主报警信息
  {NULL,NULL, 0x2018, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2018, aName0x2018, NULL, NULL, NULL, 0x0000 },////object 0x2452 --p1107 母线电压偏移量
  {NULL,NULL, 0x2034, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2034, aName0x2034, NULL, NULL, NULL, 0x0000 },////object 0x23FD --r1021 子报警信息
  {NULL,NULL, 0x2168, {DEFTYPE_INTEGER32 , 2 | (OBJCODE_ARR << 8)}, sEntryDesc0x2168, aName0x2168, NULL, NULL, NULL, 0x0000 },//object 0x23FE --r1022 主报警信息
  {NULL,NULL, 0x217C, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x217C, aName0x217C, NULL, NULL, NULL, 0x0000 },////object 0x2452 --p1107 母线电压偏移量
  {NULL,NULL, 0x217E, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x217E, aName0x217E, NULL, NULL, NULL, 0x0000 },////object 0x23FD --r1021 子报警信息
  {NULL,NULL, 0x2180, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2180, aName0x2180, NULL, NULL, NULL, 0x0000 },//object 0x23FE --r1022 主报警信息
  {NULL,NULL, 0x2181, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2181, aName0x2181, NULL, NULL, NULL, 0x0000 },////object 0x2452 --p1107 母线电压偏移量
  {NULL,NULL, 0x2197, {DEFTYPE_INTEGER32 , 2 | (OBJCODE_ARR << 8)}, sEntryDesc0x2197, aName0x2197, NULL, NULL, NULL, 0x0000 },////object 0x23FD --r1021 子报警信息
  {NULL,NULL, 0x219A, {DEFTYPE_INTEGER32 , 2 | (OBJCODE_ARR << 8)}, sEntryDesc0x219A, aName0x219A, NULL, NULL, NULL, 0x0000 },//object 0x23FE --r1022 主报警信息
  {NULL,NULL, 0x21A6, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x21A6, aName0x21A6, NULL, NULL, NULL, 0x0000 },////object 0x2452 --p1107 母线电压偏移量
  {NULL,NULL, 0x21A8, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x21A8, aName0x21A8, NULL, NULL, NULL, 0x0000 },////object 0x23FD --r1021 子报警信息
  {NULL,NULL, 0x21A9, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x21A9, aName0x21A9, NULL, NULL, NULL, 0x0000 },//object 0x23FE --r1022 主报警信息
  {NULL,NULL, 0x21B9, {DEFTYPE_INTEGER32 , 2 | (OBJCODE_ARR << 8)}, sEntryDesc0x21B9, aName0x21B9, NULL, NULL, NULL, 0x0000 },//object 0x23FE --r1022 主报警信息
  {NULL,NULL, 0x23FD, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x23FD, aName0x23FD, NULL, NULL, NULL, 0x0000 },////object 0x23FD --r1021 子报警信息
  {NULL,NULL, 0x23FE, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x23FE, aName0x23FE, NULL, NULL, NULL, 0x0000 },//object 0x23FE --r1022 主报警信息
  {NULL,NULL, 0x2452, {DEFTYPE_INTEGER32 , 0 | (OBJCODE_VAR << 8)}, &sEntryDesc0x2452, aName0x2452, NULL, NULL, NULL, 0x0000 },////object 0x2452 --p1107 母线电压偏移量
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
        case 0x2004:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.r0004;
            break;
        case 0x2005:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.r0005;
            break;
        case 0x2007:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.r0007;
            break;
        case 0x2009:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.r0009;
            break;
        case 0x200B:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.r0011;
            break;
        case 0x200C:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.r0012;
            break;
        case 0x2018:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.r0024;
            break;
        case 0x2034:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.r0052;
            break;
        case 0x2168:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.p0360;
            break;
        case 0x217C:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.p0380;
            break;
        case 0x217E:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.p0382;
            break;
        case 0x2180:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.p0384;
            break;
        case 0x2181:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.p0385;
            break;
        case 0x2197:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.p0407;
            break;
        case 0x219A:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.p0410;
            break;
        case 0x21A6:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.p0422;
            break;
        case 0x21A8:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.p0424;
            break;
        case 0x21A9:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.p0425;
            break;                    
        case 0x21B9:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.p0441;
            break;
        case 0x23FD:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.r1021;
            break;
        case 0x23FE:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.r1022;
            break;             
        case 0x2452:
            pDiCEntry->pVarPtr = &Gdc_Para.Objects.p1106;
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
