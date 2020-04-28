#include "motor.h"

//电机初始化  -- PB10 
void Motor_Init(void)
{
	GPIO_InitTypeDef motorgpio;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//通用推挽输出
	motorgpio.GPIO_Pin = GPIO_Pin_10;
	motorgpio.GPIO_Mode = GPIO_Mode_OUT;
	motorgpio.GPIO_OType = GPIO_OType_PP;
	motorgpio.GPIO_Speed = GPIO_Speed_50MHz;
	motorgpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&motorgpio);
}


