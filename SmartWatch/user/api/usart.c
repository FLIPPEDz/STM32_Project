#include "usart.h"
#include "stdio.h"
//USART1c初始化
// brr  -- 波特率
void Usart_Init(uint32_t brr)
{
	GPIO_InitTypeDef usartgpio;
	USART_InitTypeDef usartstru;
	NVIC_InitTypeDef usartnvic;
	//打开时钟 PA USART1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//将USART1 映射到PA9  PA10
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	//PA9  PA10 复用功能
	usartgpio.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	usartgpio.GPIO_Mode = GPIO_Mode_AF; //复用
	usartgpio.GPIO_OType = GPIO_OType_PP; //推挽
	usartgpio.GPIO_Speed = GPIO_Fast_Speed; //快速
	usartgpio.GPIO_PuPd = GPIO_PuPd_NOPULL; //无上下拉
	GPIO_Init(GPIOA,&usartgpio);
	//USART1    1+8+0+1
	usartstru.USART_BaudRate = brr; //波特率
	usartstru.USART_WordLength = USART_WordLength_8b;//字长8位
	usartstru.USART_StopBits = USART_StopBits_1;//停止位1位
	usartstru.USART_Parity = USART_Parity_No;//禁止校验
	usartstru.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;//收发模式
	usartstru.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件控制流
	USART_Init(USART1,&usartstru);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//使能接收中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//优先级分组
	
	usartnvic.NVIC_IRQChannel = USART1_IRQn; //中断通道
	usartnvic.NVIC_IRQChannelPreemptionPriority  =  0; //占先优先级0
	usartnvic.NVIC_IRQChannelSubPriority = 0; //次级优先级0
	usartnvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&usartnvic);

	USART_Cmd(USART1,ENABLE);//使能串口1
}

//重定义fputc 
//改变数据输出的方向，往串口输出
//换行  \r\n
int fputc(int c, FILE * stream)
{
	//等待上次的数据发送完成
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	//发送数据
	USART_SendData(USART1,c);
	return c;
}

uint8_t rxbuff[64]={0};//保存接收到的数据
uint16_t rxcount = 0;//保存接收到的数据的个数

#include "ucos_ii.h"
//中断服务函数
void USART1_IRQHandler(void)
{
	OSIntEnter();
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
		USART_ClearFlag(USART1,USART_FLAG_RXNE);//清中断
		//保存接收的数据
		rxbuff[rxcount++] = USART_ReceiveData(USART1);
	}
	OSIntExit();
}

