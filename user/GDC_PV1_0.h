/*
 * GDC_PV1_0.h
 *
 *  Created on: 2018年6月25日
 *      Author: wangpingan
 *      定义和数控系统交互的数据字典
 */

#ifndef USER_GDC_PV1_0_H_
#define USER_GDC_PV1_0_H_

#include "objdef.h"
//以ect的方式定义伺服参数字典，暂定为16个参数字典和数控系统交互

typedef struct {
    UINT32 p1106;
    UINT32 r1021;
    UINT32 r1022;
}GDC_PV1_0Objects;

typedef struct {
    GDC_PV1_0Objects    Objects;
    TOBJECT            * ObjDic;
}GDC_P, *pGDC_P;
extern TOBJECT DefGDC_PV1_0ObjDic[];
extern GDC_P Gdc_Para;
extern void GDC_PV1_0_Init(void);
extern void Gdc_Para_RemObject(void);
extern UINT16 Gdc_Para_AddObject(void);

#endif /* USER_GDC_PV1_0_H_ */
