#include "SHT20.h"
/*
函数名:SHT20_readTemOrHum
函数的功能：读取SHT20的温度或湿度测量值
参数：commod 0XF3 测量温度,0XF5 测量湿度
返回测量的温度或湿度值,1-读取失败
*/
float SHT20_readTemOrHum(u8 commod)
{
  float temp,hum;//温湿度的转换结果
  u8 ACK=0,NACK=1;//ACK-给出应答,NACK-给出非应答
	u8 ack,tem1,tem2;//tem1代表数据的高位,tem2代表低位
	u16 ST;
	IIC_Start(1);//发送开始信号
	//设置分辨率   11bit RH% 测量时间：12ms(typ.) & 11bit T℃ 测量时间：9ms(typ.) 
	if(IIC_SendByte(1,SHT20_addr&0xfe)==ACK)             //I2C address + write + ACK
  {
   if(IIC_SendByte(1,0xe6)==ACK)                               //写用户寄存器
    {  
     if(IIC_SendByte(1,0x83)==ACK)  
		 IIC_Stop(1);
    }
  } 
  IIC_Start(1);    
	ack=IIC_SendByte(1,SHT20_addr&0Xfe);//写命令包含器件地址
	if(ack==ACK)
	{
		if(IIC_SendByte(1,commod)==ACK)
		{
      do
      {
        Delay_nms(6);                                     
				IIC_Start(1);                                    //发送开始信号
			}while(IIC_SendByte(1,SHT20_addr|0x01)==NACK);      //无应答则整形，还在测量中，如果有应答，则结束当前循环
	    tem1=IIC_ReadByte(1,ACK);//读命令,给应答
			tem2=IIC_ReadByte(1,ACK);//读命令,给应答
			IIC_ReadByte(1,NACK);//读命令,不给应答
			IIC_Stop(1);
			ST=(tem1<<8)|(tem2<<0);
			ST&=~0X0003;//Data的后两位在进行物理计算前前须置‘0’
			if(commod==Read_Temp_COMD)//命令为读取温度的命令
			{
				temp=(float)(ST*0.00268127-46.85);//公式:T= -46.85 + 175.72 * ST/2^16
				return temp;
			}
			else if(commod==Read_Hum_COMD)//命令为读取湿度的命令  
			{
				hum=(float)(ST*0.00190735-6);//公式: RH%= -6 + 125 * SRH/2^16
				return hum;
			}
    }
	}
	return 1;
}


