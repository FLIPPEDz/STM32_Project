#ifndef _HP6_H_
#define _HP6_H_
#include "stm32f4xx.h"
#include "string.h"
#include "bitband.h"
#include "delay.h"
#include "usart.h"
#include "i2c.h"
#define hp6_addr     0x66  //SHT20地址
#define buff_lenth  24
#define hp_6_Power(x)  (PC_OUT(13)=x) //0 打开 1 关闭
void HP6_Init(void);
uint16_t Crc16(uint8_t *data,uint16_t len);
void HP6_IIC_Write(uint8_t *data);
void HP6_IIC_Read(uint8_t *data);
void HP6_Get_ResultDate(uint8_t *data);
uint8_t HP6_Send_Get(uint8_t *HP6_Send_buff,uint8_t *HP6_Result_buff);
uint8_t HP6_Open_Rate(void);
uint8_t HP6_Get_RateDate(void);
uint8_t HP6_Close_Rate(void);
uint8_t HP6_Open_BP(void);
uint8_t HP6_Get_BPDate(void);
uint8_t HP6_Close_BP(void);
uint8_t HP6_Power_Saving(void);
uint8_t HP6_Get_Version(void);
#endif
