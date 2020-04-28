
#include "main.h"

u8 hao[]={
0x10,0x10,0xF0,0x1F,0x10,0xF0,0x00,0x80,0x82,0x82,0xE2,0x92,0x8A,0x86,0x80,0x00,0x40,0x22,0x15,0x08,0x16,0x61,0x00,0x00,
0x40,0x80,0x7F,0x00,0x00,0x00,0x00,0x00,/*"��",0*/
};

#define led_Prio     61   //�������ȼ�
#define ledstk_size  64   //�����ջ��С
OS_STK ledstk[ledstk_size];  //�����ջ�ռ�
void Led_Task(void *pdata); //������


#define motor_Prio     7   
#define motorstk_size  64   
OS_STK motorstk[motorstk_size]; 
void Motor_Task(void *pdata); 


#define key_Prio     9   
#define keystk_size  64   
OS_STK keystk[keystk_size]; 
void Key_Task(void *pdata); 


#define oled_Prio     10   
#define oled_stk_size  64   
OS_STK oled_stk[oled_stk_size]; 
void OLED_Task(void *pdata); 


#define rtc_Prio     12  
#define rtc_stk_size  128   
OS_STK rtc_stk[rtc_stk_size]; 
void RTC_Task(void *pdata); 


#define sht20_Prio     13  
#define sht20_stk_size  128   
OS_STK sht20_stk[sht20_stk_size]; 
void SHT20_Task(void *pdata); 


#define xinlv_Prio     15  
#define xinlv_stk_size  128   
OS_STK xinlv_stk[xinlv_stk_size]; 
void Xinlv_Task(void *pdata); 


#define step_Prio     20  
#define step_stk_size  128   
OS_STK step_stk[step_stk_size]; 
void Step_Task(void *pdata); 


INT8U perr;
OS_EVENT *mysem = NULL;//�ź���ָ��
OS_EVENT *mymbox = NULL; //����ָ��
OS_FLAG_GRP *myflag =NULL;//�ź�����ָ��

short ax,ay,az;
int step =0;

RTC_TimeTypeDef rtctime;
RTC_DateTypeDef rtcdate;
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	Dealy_Config();//��ʱ��ʼ��
  LED_Init(); //LED��ʼ��
	Usart_Init(9600); //USART1��ʼ��
	printf("���ڳ�ʼ���ɹ�\r\n");
	Blue_Init();//������ʼ��
	Motor_Init(); 
	Key_Init();
	KEY_ADC_Init();
	OLED_Init();
	My_RTC_Init();
	IIC_Init();
	HP6_Init();
	MPU_Init();
	CountStepInit();
	
	
	OSInit();  //ucos-ii ����ϵͳ��ʼ��
	
	mysem = OSSemCreate(0);   //�����ź���
	mymbox = OSMboxCreate((void *)0);//������Ϣ����
	myflag = OSFlagCreate(0x00,&perr); //�����ź�����

	OSTaskCreate(Led_Task,(void *)0,&ledstk[ledstk_size-1],led_Prio);
	OSTaskCreate(Motor_Task,(void *)0,&motorstk[motorstk_size-1],motor_Prio);
	OSTaskCreate(Key_Task,(void *)0,&keystk[keystk_size-1],key_Prio);
	OSTaskCreate(OLED_Task,(void *)0,&oled_stk[oled_stk_size-1],oled_Prio);
	OSTaskCreate(RTC_Task,(void *)0,&rtc_stk[rtc_stk_size-1],rtc_Prio);
	OSTaskCreate(SHT20_Task,(void *)0,&sht20_stk[sht20_stk_size-1],sht20_Prio);
	OSTaskCreate(Xinlv_Task,(void *)0,&xinlv_stk[xinlv_stk_size-1],xinlv_Prio);
	OSTaskCreate(Step_Task,(void *)0,&step_stk[step_stk_size-1],step_Prio);
	
	OS_CPU_SysTickInit(100000);  //������ʱ�� -- 1ms
	OSStart();  //���� uC/OS-II �Ķ����񻷾�
  while (1)
  {
		
  }
}


//ָʾ������
void Led_Task(void *pdata)
{
	char *p1=NULL;
	pdata = pdata; //��ֹ������������
	for(;;)
	{
		GPIO_ToggleBits(GPIOA,GPIO_Pin_7);
		OSTimeDly(500);
	}
}
void Motor_Task(void *pdata)
{

	pdata = pdata;
	for(;;)
	{
//		Motor_ON();
//		OSTimeDly(500);
//		Motor_OFF();
		OSTimeDly(500);
	}
}

u8 flag=0;  //��Ű������µı�־
void Key_Task(void *pdata)
{
	u16 key_adc = 0;
	pdata = pdata;
	for(;;)
	{
		key_adc = KEY_Get_ADC();
		if((key_adc > 900 && key_adc<1200)||(rxbuff[0]=='1'))//����
		{
			printf("��ʾʱ��\r\n");
			OLED_clear(0);
			flag = 1;
		}
		if(key_adc > 1250 && key_adc<1500)//����
		{
			printf("��������\r\n");
			flag = 2;
			OLED_clear(0);
		}
		if(key_adc > 1900 && key_adc<2100)//����
		{
			printf("�Ʋ�\r\n");
			flag = 3;
			OLED_clear(0);
		}
		if(key_adc > 3800 && key_adc<4100)//����
		{
			printf("����\r\n");
			OLED_clear(0);
		}
		if(KEY)
		{
			printf("����\r\n");
			OLED_clear(0);
		}
		OSTimeDly(500);
	}
}

void OLED_Task(void *pdata)
{
	pdata = pdata;
	for(;;)
	{

//		Show_XXx(0,0,64,64,(char *)gImage_tu);
//		OLED_Chin_Eng(0,70,16,16,"����hi");
		OSTimeDly(500);
	}
}

void RTC_Task(void *pdata)
{
	char Str[64];
	pdata = pdata;
	for(;;)
	{
		if(flag==1)
		{
			HP6_Close_Rate();
			HP6_Close_BP();
			RTC_GetTime(RTC_Format_BIN,&rtctime);
			RTC_GetDate(RTC_Format_BIN,&rtcdate);
			sprintf(Str,"%2d :%2d :%2d",rtctime.RTC_Hours,rtctime.RTC_Minutes,rtctime.RTC_Seconds);
			OLED_Chin_Eng(0,0,16,16,Str);
			sprintf(Str,"20%2d-%2d-%2d",rtcdate.RTC_Year,rtcdate.RTC_Month,rtcdate.RTC_Date);
			OLED_Chin_Eng(2,0,16,16,Str);
			RTC_Set_AlarmA(6,11,43,10);//��������	
		}
		OSTimeDly(500);
	}
}


void SHT20_Task(void *pdata)
{
	char buff[64];
	float tem=0,hum=0;
	pdata=pdata;
	for(;;)
	{
		if(flag==0)
		{
			tem=SHT20_readTemOrHum(0xF3);//�����¶�
			hum=SHT20_readTemOrHum(0xF5);//�����¶�
			sprintf(buff,"%0.1f",tem);
			OLED_Chin_Eng(4,0,16,16,buff);
			sprintf(buff,"%0.1f",hum);
			OLED_Chin_Eng(6,0,16,16,buff);
		}
		OSTimeDly(500);
	}
}
uint8_t  xinlv[24]={0};
uint8_t  bp[24]={0};
void Xinlv_Task(void *pdata)
{
	pdata =pdata;
	for(;;)
	{
		if(flag==2)
		{
			HP6_Open_Rate();
			OSTimeDly(10000);
			HP6_Get_RateDate();  //��ȡ���ʲ������
			HP6_Get_ResultDate(xinlv);
			printf("xinlv==%d\r\n",xinlv[7]);
			//��ʾ����ʾ��
			OSTimeDly(5000);
			HP6_Close_Rate();
		}
		OSTimeDly(100);
//		HP6_Open_BP();
//		OSTimeDly(70000);
//		HP6_Get_BPDate();
//		HP6_Get_ResultDate(bp);
////		printf("��ѹ��%d  ��ѹ��%d\r\n",bp[10],bp[11]);
//		OSTimeDly(2000);
//		HP6_Close_BP();
//		OSTimeDly(500);
	}
}

void Step_Task(void *pdata)
{
	pdata =pdata;
	for(;;)
	{
		if(flag==3)
		{
			MPU_Get_Accelerometer(&ax,&ay,&az);//��ȡ���ٶȵĳ�ʼֵ
			step =CountStep(ax,ay,az);
			printf("%d\r\n",step);
		}
		OSTimeDly(10);	
	}
}	



