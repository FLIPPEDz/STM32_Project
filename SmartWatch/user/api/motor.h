#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "stm32f4xx.h"

#define Motor_ON()  GPIO_SetBits(GPIOB,GPIO_Pin_10)
#define Motor_OFF()  GPIO_ResetBits(GPIOB,GPIO_Pin_10)

void Motor_Init(void);

#endif

