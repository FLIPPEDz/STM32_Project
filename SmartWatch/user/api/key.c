#include "key.h"

//������ʼ��
void Key_Init(void)
{
	GPIO_InitTypeDef keygpio;
	//ʹ��PA�˿�ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	keygpio.GPIO_Pin = GPIO_Pin_0;
	keygpio.GPIO_Mode = GPIO_Mode_IN; //����
	keygpio.GPIO_PuPd = GPIO_PuPd_NOPULL; //��������
	GPIO_Init(GPIOA,&keygpio);
}

void KEY_ADC_Init(void)
{
	RCC->AHB1ENR |= 1<<0;  
	RCC->APB2ENR|=1<<8;//ADC1ʱ��ʹ��
	GPIOA->MODER &=~(3<<6);//����
  GPIOA->MODER |= 0X3<<6;//PA3����ģ������ģʽ
	RCC->APB2RSTR|=1<<8;//ADCs��λ
	RCC->APB2RSTR &=~(1<<8);//��λ����
	ADC->CCR=3<<16;//ADCCLK=PCLK/8=100/8=12MHZ,��ò�Ҫ����36MHZ
	ADC1->CR1=0;//CR1��������
	ADC1->CR2=0;//CR2��������
	ADC1->CR1|=0<<24;//12λģʽ
	ADC1->CR1|=0<<8;//��ɨ��ģʽ
	
	ADC1->CR2 &=~(1<<1);//����ת��ģʽ
	ADC1->CR2 &=~(1<<11);//�Ҷ���
	ADC1->CR2 |=0<<28;//�������
	ADC1->SQR1 &=~(0XF<<20);
	ADC1->SQR1 |=0<<20;//1��ת���ڹ���ͨ���У�Ҳ����ֻת����������1
	//����ͨ��3�Ĳ���ʱ��
	ADC1->SMPR2 &=~(7<<9);//ͨ��3����ʱ�����
	ADC1->SMPR2 |=(7<<9);//ͨ��3��480�����ڣ����ת������
  ADC1->CR2 |=1<<0;//����ADת����
}
u16 KEY_Get_ADC(void)
{
	//����ת������
	ADC1->SQR3 &=~(0X1F<<0);//����ADC1ͨ��1����ADCIN3�ŵ���һ��ת��������
	ADC1->SQR3 |=(3<<0);//�����ǵ�һ��ͨ��
	ADC1->CR2 |=1<<30;//����ת��ͨ��
	while(!(ADC1->SR&(1<<1)));//�ȴ�ת������
	return ADC1->DR;//����ADCֵ
}
