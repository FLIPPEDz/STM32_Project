#include "led.h"  
#include "delay.h"
//LED灯初始化
void LED_Init(void)
{
	GPIO_InitTypeDef ledgpio;
	//使能PA端口时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	ledgpio.GPIO_Pin = GPIO_Pin_7;
	ledgpio.GPIO_Mode = GPIO_Mode_OUT; //通用输出
	ledgpio.GPIO_OType = GPIO_OType_PP; //推挽输出
	ledgpio.GPIO_Speed = GPIO_Fast_Speed;//快速
	ledgpio.GPIO_PuPd = GPIO_PuPd_NOPULL; //无上下拉
	GPIO_Init(GPIOA,&ledgpio);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);
}
//闪烁灯
void LED_flash(void)
{
//		GPIOA->ODR &=~ (1<<7);//点亮
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
		Delay_ms(500);
//		GPIOA->ODR |= (1<<7); 
		GPIO_SetBits(GPIOA,GPIO_Pin_7);
		Delay_ms(500);
}

