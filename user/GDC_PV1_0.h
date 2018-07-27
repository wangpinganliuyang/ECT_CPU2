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
    UINT16   u16SubIndex0;
    UINT32   p03601;
    UINT32   p03602;
}TOBJp0360;

typedef struct {
    UINT16   u16SubIndex0;
    UINT32   p04071;
    UINT32   p04072;
}TOBJp0407;

typedef struct {
    UINT16   u16SubIndex0;
    UINT32   p04101;
    UINT32   p04102;
}TOBJp0410;

typedef struct {
    UINT16   u16SubIndex0;
    UINT32   p04411;
    UINT32   p04412;
}TOBJp0441;

typedef struct {
		UINT32 r0004;
		UINT32 r0005;
		UINT32 r0007;
		UINT32 r0009;
		UINT32 r0011;
		UINT32 r0012;
		UINT32 r0024;
		UINT32 r0052;
		TOBJp0360 p0360;
		UINT32 p0380;
		UINT32 p0382;
		UINT32 p0384;
		UINT32 p0385;
		TOBJp0407 p0407;
		TOBJp0410 p0410;
		UINT32 p0422;
		UINT32 p0424;
		UINT32 p0425;
		TOBJp0441 p0441;
		UINT32 r1021;
		UINT32 r1022;
		UINT32 p1106;
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
