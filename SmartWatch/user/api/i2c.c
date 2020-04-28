#include "i2c.h"
/*
������:IIC_Init
�����Ĺ��ܣ�IIC��ʼ��
��������
*/
void IIC_Init(void)
{
	
	RCC->AHB1ENR |= 1<<0|1<<1;//ʹ��PBʱ��//��GPIOA\Bʱ��
	GPIOA->MODER &=~(0XF<<2);//����
  GPIOA->MODER |= 0X5<<2;//PA1,PA2����ͨ�����ģʽ
	GPIOB->MODER &=~(0XF<<16);//����
  GPIOB->MODER |= 0X5<<16;//PB8,PB9����ͨ�����ģʽ
	
  GPIOA->OTYPER |= 1<<1;//PA1����Ϊ��©ģʽ
	GPIOB->OTYPER |= 1<<9;//PB9����Ϊ��©ģʽ
	GPIOA->OTYPER &=~(1<<2);//PA2����Ϊ����ģʽ
	GPIOB->OTYPER &=~(1<<8);//PB8����Ϊ����ģʽ

	IIC_SCL_H(1);//1-PB,2-PA
	IIC_SCL_H(0);
	IIC_SDA_H(1);//1-PB,2-PA
	IIC_SDA_H(0);
}
/*
������:IIC_start
�����Ĺ��ܣ�ģ��IIC��ʼ�ź�
������cate:1-PB,2-PA
*/
void IIC_Start(u8 cate)
{
  Delay_nus(4);
  IIC_SCL_H(cate);
  IIC_SDA_H(cate);
  Delay_nus(4);
  IIC_SDA_L(cate);
  Delay_nus(4);
  IIC_SCL_L(cate);//ǯסI2C���ߣ�׼�����ͻ��������
}
/*
������:IIC_stop
�����Ĺ��ܣ�ģ��IICֹͣ�ź�
������cate:1-PB,2-PA
*/
void IIC_Stop(u8 cate)
{
  IIC_SDA_L(cate);
  Delay_nus(4);
  IIC_SCL_H(cate);
  Delay_nus(4);
  IIC_SDA_H(cate);//����I2C���߽����ź�
  Delay_nus(4);
}
/*
������:IIC_sendByte
�����Ĺ��ܣ�����һ���ֽ�
������cate:1-PB,2-PA, data Ҫ���͵��ֽ�
*/
u8 IIC_SendByte(u8 cate,u8 data)
{
  u8 ack,i;
  for(i=0;i<8;i++)  //8��ʱ�Ӵ���8λ���ݣ������λ��ʼ����
  {
    if(data &(1<<(7-i)))  
    {
      IIC_SDA_H(cate);
    }
    else
    {
      IIC_SDA_L(cate);
    }
    Delay_nus(10);
    IIC_SCL_H(cate); 
    Delay_nus(10);
    IIC_SCL_L(cate);
  }
  IIC_SDA_H(cate);//�ͷŹܽſ��ƣ��ȴ�Ӧ��
  Delay_nus(10);
  IIC_SCL_H(cate);
  if(Read_SDA(cate))//SDA����ĵ�ƽΪ�ߵ�ƽ��ʾ��Ӧ��
  {
    ack = 1;
  }
  else  //SDA����ĵ�ƽΪ�͵�ƽ��ʾӦ��
  {
    ack = 0;
  }
  Delay_nus(10);
  IIC_SCL_L(cate);
  return ack;
}
/*
������:IIC_readByte
�����Ĺ��ܣ���ȡһ���ֽ�
������cate:1-PB,2-PA  ack=0ʱ������ACK��ack=1������nACK
���ض�ȡ�����ֽ�
*/
u8 IIC_ReadByte(u8 cate,u8 ack)
{
  u8 i;
  u8 data = 0;
  IIC_SDA_H(cate);//SDA����ߵ�ƽ���л�Ϊ����
  for(i=0;i<8;i++)  //����8��ʱ�ӣ���ȡ8λ����
  {
    Delay_nus(10);
    IIC_SCL_H(cate);
    data = data <<1;
    if(Read_SDA(cate))
    {
      data |= 1<<0;
    }
    else   //SDA����ĵ͵�ƽ��ƽ
    {
      data &=~(1<<0);
    }	
    Delay_nus(10);
    IIC_SCL_L(cate);		
  }
  //�����ھŸ�ʱ�ӣ�����Ӧ���źš�
  if(ack == 0)
  {
    IIC_SDA_L(cate);   
  }
  else
  {
    IIC_SDA_H(cate);
  }
  Delay_nus(10);
  IIC_SCL_H(cate);
  Delay_nus(10);
  IIC_SCL_L(cate);
  return data;
}


