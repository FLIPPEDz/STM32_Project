#ifndef _I2C_H_
#define _I2C_H_
#include "stm32f4xx.h"
#include "bitband.h"
#include "delay.h"
//#define SDA_OUT() { GPIOB->MODER &=~(3<<18);GPIOB->MODER |=(1<<18);}//PB9设置为输出
//#define SDA_IN() { GPIOB->MODER &=~(3<<18);GPIOB->MODER |=(0<<18);}//PB9设置为输入
#define PA 0
#define PB 1
#define Read_SDA(x)  x ? (PB_IN(9)):(PA_IN(1))
#define IIC_SCL_H(x) x ? (PB_OUT(8)=1):(PA_OUT(2)=1)
#define IIC_SCL_L(x) x ? (PB_OUT(8)=0):(PA_OUT(2)=0)
#define IIC_SDA_H(x) x ? (PB_OUT(9)=1):(PA_OUT(1)=1)
#define IIC_SDA_L(x) x ? (PB_OUT(9)=0):(PA_OUT(1)=0)
void IIC_Init(void);
void IIC_Start(u8 cate);
void IIC_Stop(u8 cate);
u8 IIC_SendByte(u8 cate,u8 data);
u8 IIC_ReadByte(u8 cate,u8 ack);

#endif
