#include "key.h"

//按键初始化
void Key_Init(void)
{
	GPIO_InitTypeDef keygpio;
	//使能PA端口时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	keygpio.GPIO_Pin = GPIO_Pin_0;
	keygpio.GPIO_Mode = GPIO_Mode_IN; //输入
	keygpio.GPIO_PuPd = GPIO_PuPd_NOPULL; //无上下拉
	GPIO_Init(GPIOA,&keygpio);
}

void KEY_ADC_Init(void)
{
	RCC->AHB1ENR |= 1<<0;  
	RCC->APB2ENR|=1<<8;//ADC1时钟使能
	GPIOA->MODER &=~(3<<6);//清零
  GPIOA->MODER |= 0X3<<6;//PA3配置模拟输入模式
	RCC->APB2RSTR|=1<<8;//ADCs复位
	RCC->APB2RSTR &=~(1<<8);//复位结束
	ADC->CCR=3<<16;//ADCCLK=PCLK/8=100/8=12MHZ,最好不要超过36MHZ
	ADC1->CR1=0;//CR1设置清零
	ADC1->CR2=0;//CR2设置清零
	ADC1->CR1|=0<<24;//12位模式
	ADC1->CR1|=0<<8;//非扫描模式
	
	ADC1->CR2 &=~(1<<1);//单次转换模式
	ADC1->CR2 &=~(1<<11);//右对齐
	ADC1->CR2 |=0<<28;//软件触发
	ADC1->SQR1 &=~(0XF<<20);
	ADC1->SQR1 |=0<<20;//1个转换在规则通道中，也就是只转换规则序列1
	//设置通道3的采样时间
	ADC1->SMPR2 &=~(7<<9);//通道3采样时间清空
	ADC1->SMPR2 |=(7<<9);//通道3，480个周期，提高转换精度
  ADC1->CR2 |=1<<0;//开启AD转换器
}
u16 KEY_Get_ADC(void)
{
	//设置转换序列
	ADC1->SQR3 &=~(0X1F<<0);//设置ADC1通道1，将ADCIN3放到第一个转换序列中
	ADC1->SQR3 |=(3<<0);//必须是第一个通道
	ADC1->CR2 |=1<<30;//启动转换通道
	while(!(ADC1->SR&(1<<1)));//等待转换结束
	return ADC1->DR;//返回ADC值
}
