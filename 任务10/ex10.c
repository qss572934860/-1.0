//����10		�������������ʾ�����(����ܶ�̬ɨ����ʾ)
#include	<reg51.h>				//1 �����⹦�ܼĴ��������ļ�reg51.h��������
#define	DCOUNT	8					//2 �궨�壺DCOUNT������2(����ܵĸ���)
#define	portled_S		P0			//3 �궨�壺portled_S����P1(����ܵĶ�ѡ��)
#define	portled_B		P2			//4 �궨�壺portled_B����P2(����ܵ�λѡ��)
#define	uchar	unsigned	char	//5 �궨�壺uchar����unsigned char
uchar	data	wcnt,timcnt,second,minute,hour;	//6 ��data������ȫ�ֱ���wcnt��timcnt��second
uchar	code	led[]={0x3f,0x06,0x5b,	//7 ��code����������ܵı������led
0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};	//8 ���������(C51�������Էֶ�����д)
uchar	code	ledctrl[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};//9 ��code����������ܵ���ʾ�������
void	display(uchar,uchar,uchar);				//10 display����˵��
void	main(void)					//11 main����
{	second=0;						//12 �����ʼ���������������ֵ0
	timcnt=0;						//13 10ms�жϴ�������������ֵ0
	wcnt=0;							//14 �������ʾλ�ü���������ֵ0
	TMOD=0x10;						//15 ����T1������ģʽ(��ʱ)��������ʽ(��ʽ1)
	TL1=(65536-9216)%256;			//16 T1�ļ���������ֵ��10ms
	TH1=(65536-9216)/256;			//17
	ET1=1;							//18 ��T1�ж�
	EA=1;							//19 ��ȫ���ж�
	TR1=1;							//20 ����T1
	while(1)						//21 ��ѭ�������22Ϊѭ����
	{
  display(second,minute,hour);				//33 ����display������ʾ�����ֵ		
	
	}			//22 ˯��CPU
}									//23 main��������
//--------��ʱ�ж�T1�������---------
void	tim1()	interrupt	3	using	2	//24 T1�жϷ��������жϺ�Ϊ3
{	TL1=(65536-9216)%256;			//25 ���ü�����ֵ:10ms
	TH1=(65536-9216)/256;			//26
	timcnt++;						//27 10ms�жϴ�������ֵ��1
	if(timcnt>=100)					//28 ����1����
	{	timcnt=0;					//29 ��1�룬10ms�жϴ�������ֵ��0
		second++;					//30 �������1
		if(second>=60)	
		{
			second=0;	//31 ������1�֣����������0
			minute++;
			if(minute>=60)
			{
				minute=0;
				hour++;
				if(hour>=24)
					hour=0;
			}
		}
	}								//32 ����1�봦�����
	
}									//34 �жϷ���������
//-------------��ʾ�ӳ���------------
void	display(uchar	second,uchar minute,uchar hour)		//35 display����
{	portled_S=0;					//36��ѡ���������
	portled_B=ledctrl[wcnt];		//37���������ǰ����ܵĿ�����
	switch(wcnt)					//38��ѯ��ǰ��������ܵı��
	{case	0:						//39��0�Ź�
		portled_S=led[second%10];		//40��ѡ�������ĸ�λ������(��ʾ���λ)
		break;						//41����switch���
	case	1:						//42��1�Ź�
		portled_S=led[second/10];		//43��ѡ��������ʮλ������(��ʾ��ʮλ)
	  break;
	case  2:
		portled_S=0x40;
	  break;
	case 3:
		portled_S=led[minute%10];		
	  break;
	case 4:
		portled_S=led[minute/10];	
    break;	
	case  5:
		portled_S=0x40;
	  break;
	case  6:
		portled_S=led[hour%10];	
	  break;
	case  7:
		portled_S=led[hour/10];	
	  break;
	  
	}								//44 switch������
	wcnt++;							//45 λ�ü���ֵ��1
	wcnt=wcnt%DCOUNT;				//46 ���紦��
}									//47 �жϷ���������
//--------------------------------------------------------
//��ʾ����������������,�����ж�����ʱ��


////�������ﵽģֵʱ����ֵ��0  ��־λ��1 �����жϱ�־λ��0  ��������ֵ��������