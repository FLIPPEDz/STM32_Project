#ifndef __KEY_H_
#define __KEY_H_

#include "stm32f4xx.h"

#define KEY  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)


void Key_Init(void);
void KEY_ADC_Init(void);
u16 KEY_Get_ADC(void);


#endif

