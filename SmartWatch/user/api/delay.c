#include "delay.h"

uint32_t runtime=0;//记录系统运行的时间

/*
	函数名称：Dealy_Config
	函数功能：延时初始化
	函数参数：time
	返回值：无
*/
void Dealy_Config(void)
{
	if(SysTick_Config(100000)==1)   //1ms
	{
		while(1);
	}
}
//中断多长时间进入1次：1ms
//void SysTick_Handler(void)
//{
//	runtime++;
//}

/*
	函数名称：Delay_ms
	函数功能：延时n毫秒
	函数参数：time
	返回值：无
*/
void Delay_ms(uint32_t time)
{
	uint32_t time1=runtime;//保存当前系统的运行时间
	while(runtime-time1<time);
}


/*
	函数名称：Delay_nus
	函数功能：汇编延时n微妙
	函数参数：time
	返回值：无
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
	函数名称：Delay_nms
	函数功能：汇编延时n毫秒
	函数参数：time
	返回值：无
*/
void Delay_nms(uint32_t time)
{
	while(time--)
		Delay_nus(1000);
}




