#include "led.h"  
#include "delay.h"
//LED�Ƴ�ʼ��
void LED_Init(void)
{
	GPIO_InitTypeDef ledgpio;
	//ʹ��PA�˿�ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	ledgpio.GPIO_Pin = GPIO_Pin_7;
	ledgpio.GPIO_Mode = GPIO_Mode_OUT; //ͨ�����
	ledgpio.GPIO_OType = GPIO_OType_PP; //�������
	ledgpio.GPIO_Speed = GPIO_Fast_Speed;//����
	ledgpio.GPIO_PuPd = GPIO_PuPd_NOPULL; //��������
	GPIO_Init(GPIOA,&ledgpio);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);
}
//��˸��
void LED_flash(void)
{
//		GPIOA->ODR &=~ (1<<7);//����
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
		Delay_ms(500);
//		GPIOA->ODR |= (1<<7); 
		GPIO_SetBits(GPIOA,GPIO_Pin_7);
		Delay_ms(500);
}

