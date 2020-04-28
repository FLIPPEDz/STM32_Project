#include "SHT20.h"
/*
������:SHT20_readTemOrHum
�����Ĺ��ܣ���ȡSHT20���¶Ȼ�ʪ�Ȳ���ֵ
������commod 0XF3 �����¶�,0XF5 ����ʪ��
���ز������¶Ȼ�ʪ��ֵ,1-��ȡʧ��
*/
float SHT20_readTemOrHum(u8 commod)
{
  float temp,hum;//��ʪ�ȵ�ת�����
  u8 ACK=0,NACK=1;//ACK-����Ӧ��,NACK-������Ӧ��
	u8 ack,tem1,tem2;//tem1�������ݵĸ�λ,tem2�����λ
	u16 ST;
	IIC_Start(1);//���Ϳ�ʼ�ź�
	//���÷ֱ���   11bit RH% ����ʱ�䣺12ms(typ.) & 11bit T�� ����ʱ�䣺9ms(typ.) 
	if(IIC_SendByte(1,SHT20_addr&0xfe)==ACK)             //I2C address + write + ACK
  {
   if(IIC_SendByte(1,0xe6)==ACK)                               //д�û��Ĵ���
    {  
     if(IIC_SendByte(1,0x83)==ACK)  
		 IIC_Stop(1);
    }
  } 
  IIC_Start(1);    
	ack=IIC_SendByte(1,SHT20_addr&0Xfe);//д�������������ַ
	if(ack==ACK)
	{
		if(IIC_SendByte(1,commod)==ACK)
		{
      do
      {
        Delay_nms(6);                                     
				IIC_Start(1);                                    //���Ϳ�ʼ�ź�
			}while(IIC_SendByte(1,SHT20_addr|0x01)==NACK);      //��Ӧ�������Σ����ڲ����У������Ӧ���������ǰѭ��
	    tem1=IIC_ReadByte(1,ACK);//������,��Ӧ��
			tem2=IIC_ReadByte(1,ACK);//������,��Ӧ��
			IIC_ReadByte(1,NACK);//������,����Ӧ��
			IIC_Stop(1);
			ST=(tem1<<8)|(tem2<<0);
			ST&=~0X0003;//Data�ĺ���λ�ڽ����������ǰǰ���á�0��
			if(commod==Read_Temp_COMD)//����Ϊ��ȡ�¶ȵ�����
			{
				temp=(float)(ST*0.00268127-46.85);//��ʽ:T= -46.85 + 175.72 * ST/2^16
				return temp;
			}
			else if(commod==Read_Hum_COMD)//����Ϊ��ȡʪ�ȵ�����  
			{
				hum=(float)(ST*0.00190735-6);//��ʽ: RH%= -6 + 125 * SRH/2^16
				return hum;
			}
    }
	}
	return 1;
}


