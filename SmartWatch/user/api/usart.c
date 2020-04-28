#include "usart.h"
#include "stdio.h"
//USART1c��ʼ��
// brr  -- ������
void Usart_Init(uint32_t brr)
{
	GPIO_InitTypeDef usartgpio;
	USART_InitTypeDef usartstru;
	NVIC_InitTypeDef usartnvic;
	//��ʱ�� PA USART1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//��USART1 ӳ�䵽PA9  PA10
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	//PA9  PA10 ���ù���
	usartgpio.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	usartgpio.GPIO_Mode = GPIO_Mode_AF; //����
	usartgpio.GPIO_OType = GPIO_OType_PP; //����
	usartgpio.GPIO_Speed = GPIO_Fast_Speed; //����
	usartgpio.GPIO_PuPd = GPIO_PuPd_NOPULL; //��������
	GPIO_Init(GPIOA,&usartgpio);
	//USART1    1+8+0+1
	usartstru.USART_BaudRate = brr; //������
	usartstru.USART_WordLength = USART_WordLength_8b;//�ֳ�8λ
	usartstru.USART_StopBits = USART_StopBits_1;//ֹͣλ1λ
	usartstru.USART_Parity = USART_Parity_No;//��ֹУ��
	usartstru.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;//�շ�ģʽ
	usartstru.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ��������
	USART_Init(USART1,&usartstru);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//ʹ�ܽ����ж�
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���ȼ�����
	
	usartnvic.NVIC_IRQChannel = USART1_IRQn; //�ж�ͨ��
	usartnvic.NVIC_IRQChannelPreemptionPriority  =  0; //ռ�����ȼ�0
	usartnvic.NVIC_IRQChannelSubPriority = 0; //�μ����ȼ�0
	usartnvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&usartnvic);

	USART_Cmd(USART1,ENABLE);//ʹ�ܴ���1
}

//�ض���fputc 
//�ı���������ķ������������
//����  \r\n
int fputc(int c, FILE * stream)
{
	//�ȴ��ϴε����ݷ������
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	//��������
	USART_SendData(USART1,c);
	return c;
}

uint8_t rxbuff[64]={0};//������յ�������
uint16_t rxcount = 0;//������յ������ݵĸ���

#include "ucos_ii.h"
//�жϷ�����
void USART1_IRQHandler(void)
{
	OSIntEnter();
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
		USART_ClearFlag(USART1,USART_FLAG_RXNE);//���ж�
		//������յ�����
		rxbuff[rxcount++] = USART_ReceiveData(USART1);
	}
	OSIntExit();
}

