#ifndef _BITBAND_H_
#define _BITBAND_H_
#include "stm32f4xx.h"
#define BITBAND(addr,bitnum)  (((u32)addr & 0xf0000000)+0x2000000+(((u32)addr & 0xfffff)*32)+(4*bitnum))
#define MEMADDR(addr)  *((volatile unsigned int *)(addr))
#define BITband(addr,bitnum)  MEMADDR(BITBAND(addr,bitnum))

#define PA_OUT(n)  BITband(&GPIOA->ODR,n)
#define PB_OUT(n)  BITband(&GPIOB->ODR,n)
#define PC_OUT(n)  BITband(&GPIOC->ODR,n)
#define PD_OUT(n)  BITband(&GPIOD->ODR,n)
#define PE_OUT(n)  BITband(&GPIOE->ODR,n)
#define PF_OUT(n)  BITband(&GPIOF->ODR,n)

#define PA_IN(n)  BITband(&GPIOA->IDR,n)
#define PB_IN(n)  BITband(&GPIOB->IDR,n)
#define PC_IN(n)  BITband(&GPIOC->IDR,n)
#define PD_IN(n)  BITband(&GPIOD->IDR,n)
#define PE_IN(n)  BITband(&GPIOE->IDR,n)
#define PF_IN(n)  BITband(&GPIOF->IDR,n)
#endif
