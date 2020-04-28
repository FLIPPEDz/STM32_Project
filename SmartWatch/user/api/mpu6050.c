#include "mpu6050.h"
/*
������:MPU_IIC_Write_Byte
�����Ĺ��ܣ�MPU_IICдһ���ֽں���
������reg��Ҫд��ļĴ�����ַ data��Ҫд��Ĵ���������
*/
void MPU_IIC_Write_Byte(u8 reg,u8 data)
{
	IIC_Start(1);//0-PA,1-PB
	IIC_SendByte(1,(MPU_ADDR<<1)|0);//����������ַ+д����
	IIC_SendByte(1,reg);//���ͼĴ�����ַ
	IIC_SendByte(1,data);//��������
	IIC_Stop(1);//0-PA,1-PB
}
/*
������:MPU_IIC_Read_Byte
�����Ĺ��ܣ�MPU_IIC��һ���ֽں���
������reg��Ҫд��ļĴ�����ַ 
���ض�ȡ��������
*/
u8 MPU_IIC_Read_Byte(u8 reg)	
{
	u8 data;
	IIC_Start(1);//0-PA,1-PB
	IIC_SendByte(1,(MPU_ADDR<<1)|0);//����������ַ+д����
	IIC_SendByte(1,reg);//���ͼĴ�����ַ
	IIC_Start(1);
	IIC_SendByte(1,(MPU_ADDR<<1)|1);//����������ַ+������
	data=IIC_ReadByte(1,1);//��ȡ����,����nACK
	IIC_Stop(1);//0-PA,1-PB
	return data;
}
/*
������:MPU_Write_Len
�����Ĺ��ܣ�MPU_IIC����д��lenth���ֽں���
������reg��Ҫд��ļĴ�����ַ buff��Ҫд������ݵ�ַ lenth�����ݳ���
*/
void MPU_Write_Len(u8 reg,u8 *buff,u8 lenth)
{
	u8 i=0;
	IIC_Start(1);
	IIC_SendByte(1,(MPU_ADDR<<1)|0);//����������ַ+д����
	IIC_SendByte(1,reg);//���ͼĴ�����ַ
  for(i=0;i<lenth;i++)
  IIC_SendByte(1,buff[i]);//����д��lenth������
	IIC_Stop(1);
}
/*
������:MPU_Read_Len
�����Ĺ��ܣ�MPU_IIC������ȡ���ݺ���
������reg��Ҫд��ļĴ�����ַ buff����ȡ�������ݴ洢�� lenth��Ҫ��ȡ�����ݳ���
���ض�ȡ��������
*/
u8 MPU_Read_Len(u8 reg,u8 *buff,u8 lenth)	
{
	u8 i;
	IIC_Start(1);
	IIC_SendByte(1,(MPU_ADDR<<1)|0);//����������ַ+д����
	IIC_SendByte(1,reg);//���ͼĴ�����ַ
	IIC_Start(1);
	IIC_SendByte(1,(MPU_ADDR<<1)|1);//����������ַ+������
	for(i=lenth;i>0;i--)
	{
		if(i==1)
		{
			buff[lenth-i]=IIC_ReadByte(1,1);//��ȡ�����һλ����,����nACK
			break;
		}
		else
		buff[lenth-i]=IIC_ReadByte(1,0);//��ʼ��ȡ����,����ACK
	}
	IIC_Stop(1);
	return 0;
}	
/*
������:MPU_Set_Gyro_Fsr
�����Ĺ��ܣ�����MPU6050�����Ǵ����������̷�Χ
������fsr��0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
*/
void MPU_Set_Gyro_Fsr(u8 fsr)
{
  MPU_IIC_Write_Byte(MPU_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ  
}
/*
������:MPU_Set_Accel_Fsr
�����Ĺ��ܣ�����MPU6050���ٶȴ����������̷�Χ
������fsr��0,��2g;1,��4g;2,��8g;3,��16g
*/
void MPU_Set_Accel_Fsr(u8 fsr)
{
  MPU_IIC_Write_Byte(MPU_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ  
}
/*
������:MPU_Set_LPF
�����Ĺ��ܣ�����MPU6050�����ֵ�ͨ�˲���
������lpf�����ֵ�ͨ�˲�Ƶ��(Hz)
*/
void MPU_Set_LPF(u16 lpf)
{
  u8 data=0;
  if(lpf>=188)data=1;
  else if(lpf>=98)data=2;
  else if(lpf>=42)data=3;
  else if(lpf>=20)data=4;
  else if(lpf>=10)data=5;
  else data=6; 
  MPU_IIC_Write_Byte(MPU_CFG_REG,data);//�������ֵ�ͨ�˲���  
}
/*
������:MPU_Set_Rate
�����Ĺ��ܣ�����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
������rate:4~1000(Hz)
*/
void MPU_Set_Rate(u16 rate)
{
  u8 data;
  if(rate>1000)rate=1000;
  if(rate<4)rate=4;
  data=1000/rate-1;
  MPU_IIC_Write_Byte(MPU_SAMPLE_RATE_REG,data);	//�������ֵ�ͨ�˲���
  MPU_Set_LPF(rate/2);	//�Զ�����LPFΪ�����ʵ�һ��
}
/*
������:MPU_Get_Gyroscope
�����Ĺ��ܣ��õ�������ֵ(ԭʼֵ)
������gx,gy,gz:������x,y,z���ԭʼ����(������)
����0 �ɹ�  �������� ʧ��
*/
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
  u8 buff[6],res;  
  res=MPU_Read_Len(MPU_GYRO_XOUTH_REG,buff,6);
  if(res==0)
  {
    *gx=((u16)buff[0]<<8)|buff[1];  
    *gy=((u16)buff[2]<<8)|buff[3];  
    *gz=((u16)buff[4]<<8)|buff[5];
  } 	
  return res;;
}
/*
������:MPU_Get_Accelerometer
�����Ĺ��ܣ��õ����ٶ�ֵ(ԭʼֵ)
������ax,ay,az:���ٶ�x,y,z���ԭʼ����(������)
����0 �ɹ�  �������� ʧ��
*/
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
  u8 buff[6],res;  
  res=MPU_Read_Len(MPU_ACCEL_XOUTH_REG,buff,6);
  if(res==0)
  {
    *ax=((u16)buff[0]<<8)|buff[1];  
    *ay=((u16)buff[2]<<8)|buff[3];  
    *az=((u16)buff[4]<<8)|buff[5];
  } 	
  return res;;
}
/*
������:MPU_Init
�����Ĺ��ܣ���ʼ��MPU6050
��������
����0 �ɹ�  �������� ʧ��
*/
u8 MPU_Init(void)
{
	u8 res;
  MPU_IIC_Write_Byte(MPU_PWR_MGMT1_REG,0X80);	//��λMPU6050-��λ��1
  Delay_nms(100); 
  MPU_IIC_Write_Byte(MPU_PWR_MGMT1_REG,0X00);	//����MPU6050 
  MPU_Set_Gyro_Fsr(3);					//�����Ǵ�����,��2000dps-���������̧����
  MPU_Set_Accel_Fsr(0);					//���ٶȴ�����,��2g
  MPU_Set_Rate(50);						//���ò�����50Hz
  MPU_IIC_Write_Byte(MPU_INT_EN_REG,0X00);	//�ر������ж�
  MPU_IIC_Write_Byte(MPU_USER_CTRL_REG,0X00);	//I2C��ģʽ�ر�
  MPU_IIC_Write_Byte(MPU_FIFO_EN_REG,0X00);	//�ر�FIFO
  MPU_IIC_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//INT���ŵ͵�ƽ��Ч
  res=MPU_IIC_Read_Byte(MPU_DEVICE_ID_REG);
  if(res==MPU_ADDR)//����ID��ȷ
  {
    MPU_IIC_Write_Byte(MPU_PWR_MGMT1_REG,0X01);	//����ϵͳʱ��Դ,PLL X��Ϊ�ο�
    MPU_IIC_Write_Byte(MPU_PWR_MGMT2_REG,0x00);	//���ٶȡ������ǹ���
    MPU_Set_Rate(50);						            //���ò�����Ϊ50Hz
		MPU_Set_LPF(20);                        //���ô���Ϊ25HZ
    return 0;
  }
	else return 1;
}	

	

