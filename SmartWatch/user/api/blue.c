#include "blue.h"

//������ʼ��
void Blue_Init(void)
{
	GPIO_InitTypeDef bluegpio;
	//��ʱ��  PB 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	bluegpio.GPIO_Pin = GPIO_Pin_6;
	bluegpio.GPIO_Mode = GPIO_Mode_OUT;//ͨ�����
	bluegpio.GPIO_OType = GPIO_OType_PP;//�������
	bluegpio.GPIO_Speed = GPIO_Speed_50MHz;//����ٶ�
	bluegpio.GPIO_PuPd = GPIO_PuPd_NOPULL;//��������
	GPIO_Init(GPIOB,&bluegpio);
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);//��������
}


