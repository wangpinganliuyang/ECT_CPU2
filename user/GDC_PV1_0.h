/*
 * GDC_PV1_0.h
 *
 *  Created on: 2018��6��25��
 *      Author: wangpingan
 *      ���������ϵͳ�����������ֵ�
 */

#ifndef USER_GDC_PV1_0_H_
#define USER_GDC_PV1_0_H_

#include "objdef.h"
//��ect�ķ�ʽ�����ŷ������ֵ䣬�ݶ�Ϊ16�������ֵ������ϵͳ����

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
