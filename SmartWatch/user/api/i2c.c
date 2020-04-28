#include "i2c.h"
/*
函数名:IIC_Init
函数的功能：IIC初始化
参数：无
*/
void IIC_Init(void)
{
	
	RCC->AHB1ENR |= 1<<0|1<<1;//使能PB时钟//打开GPIOA\B时钟
	GPIOA->MODER &=~(0XF<<2);//清零
  GPIOA->MODER |= 0X5<<2;//PA1,PA2配置通用输出模式
	GPIOB->MODER &=~(0XF<<16);//清零
  GPIOB->MODER |= 0X5<<16;//PB8,PB9配置通用输出模式
	
  GPIOA->OTYPER |= 1<<1;//PA1配置为开漏模式
	GPIOB->OTYPER |= 1<<9;//PB9配置为开漏模式
	GPIOA->OTYPER &=~(1<<2);//PA2配置为推挽模式
	GPIOB->OTYPER &=~(1<<8);//PB8配置为推挽模式

	IIC_SCL_H(1);//1-PB,2-PA
	IIC_SCL_H(0);
	IIC_SDA_H(1);//1-PB,2-PA
	IIC_SDA_H(0);
}
/*
函数名:IIC_start
函数的功能：模拟IIC开始信号
参数：cate:1-PB,2-PA
*/
void IIC_Start(u8 cate)
{
  Delay_nus(4);
  IIC_SCL_H(cate);
  IIC_SDA_H(cate);
  Delay_nus(4);
  IIC_SDA_L(cate);
  Delay_nus(4);
  IIC_SCL_L(cate);//钳住I2C总线，准备发送或接收数据
}
/*
函数名:IIC_stop
函数的功能：模拟IIC停止信号
参数：cate:1-PB,2-PA
*/
void IIC_Stop(u8 cate)
{
  IIC_SDA_L(cate);
  Delay_nus(4);
  IIC_SCL_H(cate);
  Delay_nus(4);
  IIC_SDA_H(cate);//发送I2C总线结束信号
  Delay_nus(4);
}
/*
函数名:IIC_sendByte
函数的功能：发送一个字节
参数：cate:1-PB,2-PA, data 要发送的字节
*/
u8 IIC_SendByte(u8 cate,u8 data)
{
  u8 ack,i;
  for(i=0;i<8;i++)  //8个时钟传输8位数据，从最高位开始传输
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
  IIC_SDA_H(cate);//释放管脚控制，等待应答
  Delay_nus(10);
  IIC_SCL_H(cate);
  if(Read_SDA(cate))//SDA输入的电平为高电平表示非应答
  {
    ack = 1;
  }
  else  //SDA输入的电平为低电平表示应答
  {
    ack = 0;
  }
  Delay_nus(10);
  IIC_SCL_L(cate);
  return ack;
}
/*
函数名:IIC_readByte
函数的功能：读取一个字节
参数：cate:1-PB,2-PA  ack=0时，发送ACK，ack=1，发送nACK
返回读取到的字节
*/
u8 IIC_ReadByte(u8 cate,u8 ack)
{
  u8 i;
  u8 data = 0;
  IIC_SDA_H(cate);//SDA输出高电平，切换为输入
  for(i=0;i<8;i++)  //产生8个时钟，读取8位数据
  {
    Delay_nus(10);
    IIC_SCL_H(cate);
    data = data <<1;
    if(Read_SDA(cate))
    {
      data |= 1<<0;
    }
    else   //SDA输入的低电平电平
    {
      data &=~(1<<0);
    }	
    Delay_nus(10);
    IIC_SCL_L(cate);		
  }
  //产生第九个时钟，发送应答信号。
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


