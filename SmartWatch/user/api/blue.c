#include "blue.h"

//蓝牙初始化
void Blue_Init(void)
{
	GPIO_InitTypeDef bluegpio;
	//打开时钟  PB 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	bluegpio.GPIO_Pin = GPIO_Pin_6;
	bluegpio.GPIO_Mode = GPIO_Mode_OUT;//通用输出
	bluegpio.GPIO_OType = GPIO_OType_PP;//推挽输出
	bluegpio.GPIO_Speed = GPIO_Speed_50MHz;//输出速度
	bluegpio.GPIO_PuPd = GPIO_PuPd_NOPULL;//无上下拉
	GPIO_Init(GPIOB,&bluegpio);
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);//开启蓝牙
}


