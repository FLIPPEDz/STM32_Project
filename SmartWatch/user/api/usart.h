#ifndef __USART_H_
#define __USART_H_

#include "stm32f4xx.h"

extern uint8_t rxbuff[64];
extern uint16_t rxcount;

void Usart_Init(uint32_t brr);


#endif

