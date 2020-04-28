#include "delay.h"

uint32_t runtime=0;//��¼ϵͳ���е�ʱ��

/*
	�������ƣ�Dealy_Config
	�������ܣ���ʱ��ʼ��
	����������time
	����ֵ����
*/
void Dealy_Config(void)
{
	if(SysTick_Config(100000)==1)   //1ms
	{
		while(1);
	}
}
//�ж϶೤ʱ�����1�Σ�1ms
//void SysTick_Handler(void)
//{
//	runtime++;
//}

/*
	�������ƣ�Delay_ms
	�������ܣ���ʱn����
	����������time
	����ֵ����
*/
void Delay_ms(uint32_t time)
{
	uint32_t time1=runtime;//���浱ǰϵͳ������ʱ��
	while(runtime-time1<time);
}


/*
	�������ƣ�Delay_nus
	�������ܣ������ʱn΢��
	����������time
	����ֵ����
*/
void Delay_nus(uint32_t time)
{
	while(time--)
	{
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	}
}
	
/*
	�������ƣ�Delay_nms
	�������ܣ������ʱn����
	����������time
	����ֵ����
*/
void Delay_nms(uint32_t time)
{
	while(time--)
		Delay_nus(1000);
}




