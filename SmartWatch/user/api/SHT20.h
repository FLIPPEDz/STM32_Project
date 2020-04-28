#ifndef _SHT20_H_
#define _SHT20_H_
#include "stm32f4xx.h"
#include "bitband.h"
#include "delay.h"
#include "i2c.h"
#define Read_Temp_COMD 0xf3  //��ȡ�¶�����
#define Read_Hum_COMD  0xf5  //��ȡʪ������
#define SHT20_addr     0x80  //SHT20��ַ
float SHT20_readTemOrHum(u8 commod);
#endif
