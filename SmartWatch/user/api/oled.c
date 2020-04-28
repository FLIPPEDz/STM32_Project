#include "oled.h"

//OLED���ӿڳ�ʼ��
void OLED_GPIO_Init(void)
{
	RCC->AHB1ENR |=(1<<0)|(1<<1);//����1ʱ��ʹ��
	RCC->APB2ENR |=(1<<12);
	//����PB7,PB13,PA15����ģʽ-ͨ�ù���ģʽ
	GPIOB->MODER &=~(3<<14);
	GPIOB->MODER |=(1<<14);
	GPIOB->MODER &=~(3<<26);
	GPIOB->MODER |=(1<<26);
	GPIOA->MODER &=~(3<<30);
	GPIOA->MODER |=(1<<30);
	//����PB3,PB5����ģʽ-���ù���ģʽ
	GPIOB->MODER &=~(3<<6);
	GPIOB->MODER |=(2<<6);
	GPIOB->MODER &=~(3<<10);
	GPIOB->MODER |=(2<<10);
	//���ø��ù���ģʽ-SPI1
	GPIOB->AFR[0] &=~(0XF<<12);//--F�����ο��ֲ�P192
	GPIOB->AFR[0] |=(0X5<<12);
	GPIOB->AFR[0] &=~(0XF<<20);//--F�����ο��ֲ�P192
	GPIOB->AFR[0] |=(0X5<<20);
	//���ģʽ����-�������
	GPIOA->OTYPER &=~(1<<15);
	GPIOB->OTYPER &=~(1<<3);
	GPIOB->OTYPER &=~(1<<5);
	GPIOB->OTYPER &=~(1<<7);
	GPIOB->OTYPER &=~(1<<13);
	//�����������-50MHZ
	GPIOA->OSPEEDR &=~(3<<30);
	GPIOA->OSPEEDR |=(2<<30);
	GPIOB->OSPEEDR &=~(3<<6);
	GPIOB->OSPEEDR |=(2<<6);
	GPIOB->OSPEEDR &=~(3<<10);
	GPIOB->OSPEEDR |=(2<<10);
	GPIOB->OSPEEDR &=~(3<<14);
	GPIOB->OSPEEDR |=(2<<14);
	GPIOB->OSPEEDR &=~(3<<26);
	GPIOB->OSPEEDR |=(2<<26);
	//��������ģʽ����-����ģʽ
	GPIOA->PUPDR &=~(3<<30);
	GPIOA->PUPDR |=(0<<30);
	GPIOB->PUPDR &=~(3<<6);
	GPIOB->PUPDR |=(0<<6);
	GPIOB->PUPDR &=~(3<<10);
	GPIOB->PUPDR |=(0<<10);
	GPIOB->PUPDR &=~(3<<14);
	GPIOB->PUPDR |=(0<<14);
	GPIOB->PUPDR &=~(3<<26);
	GPIOB->PUPDR |=(0<<26);

	SPI1->CR1 |= (1<<9)|(1<<8);//������豸����
	SPI1->CR1 &=~ (7<<3);
	SPI1->CR1 |= (4<<3);//fclk/32
	SPI1->CR1 |= (1<<2);//���豸
	SPI1->CR1 |= (1<<6);//ʹ��SPI
}
//SPI��дһ���ֽ�����
uint8_t SPI1_ReadWriteByte (uint8_t Data)
{
	while (!(SPI1->SR & (1<<1)));
	SPI1->DR = Data;
	while (!(SPI1->SR & (1<<0)));
	return SPI1->DR;
}
//OLED����λ
void OLED_REST(void)
{
	  OLED_RES=1; 
		Delay_nms(200); 
		OLED_RES=0; 
		Delay_nms(200); 
		OLED_RES=1; 
		Delay_nms(200);
}
//OLED��д����/����
void OLED_ReadWriteByte(u8 data,u8 com_data) 
{ 
  com_data ?(OLED_DC=1):(OLED_DC=0);
  OLED_CS=0;
  SPI1_ReadWriteByte (data); 
  OLED_CS=1;
}
//��������ʼ��
void OLED_Config(void)
{
	OLED_ReadWriteByte(0xAE,OLED_COM); /*display off*/
	OLED_ReadWriteByte(0x00,OLED_COM); /*set lower column address*/
	OLED_ReadWriteByte(0x10,OLED_COM); /*set higher column address*/
	
	OLED_ReadWriteByte(0x40,OLED_COM); /*set display start line*/
	
	OLED_ReadWriteByte(0xB0,OLED_COM); /*set page address*/
	OLED_ReadWriteByte(0x81,OLED_COM); /*contract control*/
	OLED_ReadWriteByte(0x66,OLED_COM); /*128*/
	OLED_ReadWriteByte(0xA1,OLED_COM); /*set segment remap*/
	OLED_ReadWriteByte(0xA6,OLED_COM); /*normal / reverse--����ɫ*/
	OLED_ReadWriteByte(0xA8,OLED_COM); /*multiplex ratio*/
	OLED_ReadWriteByte(0x3F,OLED_COM); /*duty = 1/64*/
	OLED_ReadWriteByte(0xC8,OLED_COM); /*Com scan direction*/
	
	OLED_ReadWriteByte(0xD3,OLED_COM); /*set display offset-����ƫ����*/
	OLED_ReadWriteByte(0x00,OLED_COM);
	
	OLED_ReadWriteByte(0xD5,OLED_COM); /*set osc division*/
	OLED_ReadWriteByte(0x80,OLED_COM);
	OLED_ReadWriteByte(0xD9,OLED_COM); /*set pre-charge period*/
	OLED_ReadWriteByte(0x1f,OLED_COM);
	OLED_ReadWriteByte(0xDA,OLED_COM); /*set COM pins*/
	OLED_ReadWriteByte(0x12,OLED_COM);
	OLED_ReadWriteByte(0xdb,OLED_COM); /*set vcomh*/
	OLED_ReadWriteByte(0x30,OLED_COM);
	OLED_ReadWriteByte(0x8d,OLED_COM); /*set charge pump enable*/
	OLED_ReadWriteByte(0x14,OLED_COM);
	OLED_ReadWriteByte(0xAF,OLED_COM); /*display ON*/
	OLED_clear(0);
 } 
//OLED����ʼ��
void OLED_Init(void)
{
	OLED_GPIO_Init();
	OLED_CS=1;
	OLED_REST();
	OLED_Config();
}
//����
void OLED_clear(u8 data)
{
   uint16_t i=0,j=0;
   for(i=0;i<8;i++)
  {
	  OLED_ReadWriteByte(0XB0+i,OLED_COM); //����ҳ��ַ
	  OLED_ReadWriteByte(0X00+0,OLED_COM); //�����е�ַ����λ
	  OLED_ReadWriteByte(0X10+0,OLED_COM); //�����е�ַ����λ
    for(j=0;j<132;j++)
	  {
		 OLED_ReadWriteByte(data,OLED_Data);
    }
   } 
 }
//���ù��
u8 OLED_Set_Pos(u8 page, u8 column)
{
	 if(page>=8|column>=132)
	 return 0;
	 OLED_ReadWriteByte(0XB0+page,OLED_COM); //����ҳ��ַ
	 OLED_ReadWriteByte((0X00+(column & 0xf)),OLED_COM); //�����е�ַ����λ
	 OLED_ReadWriteByte((0X10+((column>>4)&0xf)),OLED_COM);
	 return 1;
 }

//page--ҳ,column--��,size_x--�ֿ���,size_y--�ֿ���,p--ģ
void Show_XXx(u8 page,u8 column,u32 size_x,u32 size_y,char *p)
{
	u16 i,j=0;
	for(i=0;i<(size_y/8);i++)
	{
		  if(OLED_Set_Pos(page+i,column))
		  for(j=0;j<size_x;j++)
	   {
			 OLED_ReadWriteByte(p[(i*size_x)+j],OLED_Data);
		 }
	 }
}

//��ʾ����һ������
void Show_Hanz(u8 page,u8 column,u32 size_x,u32 size_y,char *p)
{
		u16 i,j=0,k=0;
	  u32 offset=0;
	  u32 lenth=strlen(HanZ_list);
	  k=size_x*size_y/8;
	  for(i=0;i<lenth;i+=2)//ע��lenth�˴���Ҫ����2
	  {
			if((p[0]==HanZ_list[i])&&(p[1]==HanZ_list[i+1]))
			{
				i=i/2;
				break;
			}
		}
		offset=i*k;//����ƫ����
	  for(i=0;i<(size_y/8);i++)
	 {
		  if(OLED_Set_Pos(page+i,column))
		  for(j=0;j<size_x;j++)
	   {
			 OLED_ReadWriteByte(HanZ_16X16[offset+(i*size_x)+j],OLED_Data);//16*16--����
		 }
	 }
}
//��ʾ����һ��8*16 / 12*24  ��С��ASCII�ַ�
void Show_Char(u8 page,u8 column,u32 size_x,u32 size_y,char *p)
{
		u16 i,j=0,k=0;
	  k=((*p)-32)*(size_x*size_y/8);//����ƫ����
	  for(i=0;i<(size_y/8);i++)
	 {
		  if(OLED_Set_Pos(page+i,column))
		  for(j=0;j<size_x;j++)
	   {
			 if(size_y==16)
			 OLED_ReadWriteByte(ASII_8X16[k+(i*size_x)+j],OLED_Data);//8*16--ASCIIֵ���ش���󣬶����һ��Ԫ�أ������˵�0��Ԫ��
			 else if(size_y==24)
			 OLED_ReadWriteByte(ASII_12X24[k+(i*size_x)+j],OLED_Data);//12*24--ASCIIֵ
		 }
	 }
 }
//��ʾ����һ��ASCII�ַ�
void Show_Chars(u8 page,u8 column,u32 size_x,u32 size_y,char *q)
{
	int i;
  int len=strlen((char *)q);
	for(i=0;i<len;i++)
	{
     Show_Char(page,column+(i*size_x),size_x,size_y,&q[i]);
	}
}
//��Ӣ�Ļ����ʾ
void OLED_Chin_Eng(u8 page,u8 column,u32 size_x,u32 size_y,char *q)
{
	 while(*q!=NULL)
	 {  
		 if(*q>(char)0xa0)//�˴�ע�⣬����ĳЩ���ĵı����ź�һ��������պõ���0xa1
	    {
			  Show_Hanz(page,column,size_x,size_y,q);
				column+=size_x;
				q+=2;
		  }
		  else 
		  {
		
		    Show_Char(page,column,size_x/2,size_y,q);
				column+=(size_x/2);
        q+=1;
		  }
			if((132-column)<0)
			{
				column=0;
			}
	  }
}
