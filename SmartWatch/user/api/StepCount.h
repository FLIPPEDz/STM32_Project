/*********************************************Copyright (c)***********************************************
** Name: smallmount
**
**--------------File Info---------------------------------------------------------------------------------
** Last modified date:      2014-02-11
** Descriptions:            LCD Driver
**
*********************************************************************************************************/
#ifndef _StepCount_H_
#define _StepCount_H_
#include "stm32f4xx.h"
typedef signed short      DATATYPE;
#define DATASIZE    50
typedef struct __DATA {
    DATATYPE Data[DATASIZE];
    DATATYPE Max;
    DATATYPE MaxMark;
    DATATYPE Min;
    DATATYPE MinMark;
    DATATYPE Base;
    DATATYPE UpLimit;
    DATATYPE DownLimit;
}__DATA;

typedef struct _SensorData {
    __DATA X;
    __DATA Y;
    __DATA Z;
}SensorData;

void DataInit(SensorData *SData);
unsigned char DataSelect(SensorData *GMeter);
void CountStepInit(void);
u8 CountStep(signed short X,signed short Y,signed short Z);
void UartSendPacket(unsigned char *ucData, unsigned char ucSize);

#endif
