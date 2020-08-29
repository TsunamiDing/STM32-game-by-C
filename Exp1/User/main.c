#include "stm32f10x.h"
#include "EIE3810_TFTLCD.h"
#include "EIE3810_Key.h"
#include "EIE3810_LED.h"
#include "EIE3810_Buzzer.h"
#include "EIE3810_USART.h"

void Delay(u32);
void EIE3810_clock_tree_init(void);
void EIE3810_NVIC_SetPriorityGroup(u8 prigroup);
void EIE3810_TIM2_Init(u16 arr, u16 psc);
void EIE3810_TIM3_Init(u16 arr, u16 psc);
void EIE3810_TIM4_Init(u16 arr, u16 psc);
void EIE3810_TIM5_Init(u16 arr, u16 psc);
void JOYPAD_Init(void);
void JOYPAD_Delay(u16 t);
void Game1(void);
void Game2(void);
void GameBall(void);
void GameOver(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM5_IRQHandler(void);
void show_time_bounces(void);
void EIE3810_USART1_EXTIInit(void);
void USART1_IRQHandler(void);
void pauses(void);

void Step1(void);
void Step2(void);
void Step3(void);
void Step4(void);

int main(void)
{
	EIE3810_clock_tree_init()；
	EIE3810_TFTLCD_Init();
	EIE3810_Key_Init();
	EIE3810_LED_Init();
	EIE3810_Buzzer_Init();	
	EIE3810_USART1_init(72, 39062);
	EIE3810_TFTLCD_DrawBackground(WHITE);
	Delay(1000000);	
	Step1();
	Delay(1000000);	
	Step2();
	Delay(1000000);	
	Step3();
	Delay(1000000);	
	while(1){;}
}

u32 level = 0;
u32 x1 = 240;      u32 x2 = 240;
u32 ballx = 240;   u32 bally = 769;
u32 right = 1;     u32 up = 0;

u32 dir;
u32 i = 0;
u32 bounces = 0;
u32 pause = 0;
u32 Key1;
u32 Changed_Key1;	
u32 Start;
u32 Changed_Start;

void Delay(u32 count)
{
	u32 i;
	for (i=0;i<count;i++);
}

void EIE3810_clock_tree_init(void)
{
	u8 PLL=7;
	u8 temp=0;
	RCC->CR |= 0x00010000;
	while(!((RCC->CR>>17)&0x1));
	RCC->CFGR &= 0xFFFDFFFF;
	RCC->CFGR |= 1<<16;
	RCC->CFGR |= PLL<<18;
	RCC->CR |=0x01000000;
	while(!(RCC->CR>>25));
	RCC->CFGR &=0xFFFFFFFE;
	RCC->CFGR |=0x00000002;
	while(temp !=0x02)
	{
		temp=RCC->CFGR>>2;
		temp &= 0x03;
	}	
	RCC->CFGR &= 0xFFFFFC0F;
	RCC->CFGR |= 0x00000400;	
	RCC->CFGR &= 0xFFFFDFFF;
	FLASH->ACR = 0x32;
	RCC->APB1ENR |= 1<<17;
	RCC->APB2ENR |= 1<<14;
}

void EIE3810_USART1_EXTIInit(void)
{
	NVIC->IP[37] =0x95;
	NVIC->ISER[1] |=1<<5;
}

void USART1_IRQHandler(void)//Define the corresponding relation of the received number and the direction
{
	u32 buffer;
	if(USART1->SR &(1<<5))
	{
		buffer=USART1->DR;
		while(1){
		if(buffer==0)
		{
			dir=0;
			EIE3810_TFTLCD_ShowChar2412(198, 480, 83, RED, WHITE);//S
			EIE3810_TFTLCD_ShowChar2412(210, 480, 85, RED, WHITE);//U
			EIE3810_TFTLCD_ShowChar2412(222, 480, 67, RED, WHITE);//C
			EIE3810_TFTLCD_ShowChar2412(234, 480, 67, RED, WHITE);//C
			EIE3810_TFTLCD_ShowChar2412(246, 480, 69, RED, WHITE);//E
			EIE3810_TFTLCD_ShowChar2412(258, 480, 83, RED, WHITE);//S
			EIE3810_TFTLCD_ShowChar2412(270, 480, 83, RED, WHITE);//S
			break;
		}
		if(buffer==1)
		{ 
			dir=1;
			EIE3810_TFTLCD_ShowChar2412(198, 480, 83, RED, WHITE);//S
			EIE3810_TFTLCD_ShowChar2412(210, 480, 85, RED, WHITE);//U
			EIE3810_TFTLCD_ShowChar2412(222, 480, 67, RED, WHITE);//C
			EIE3810_TFTLCD_ShowChar2412(234, 480, 67, RED, WHITE);//C
			EIE3810_TFTLCD_ShowChar2412(246, 480, 69, RED, WHITE);//E
			EIE3810_TFTLCD_ShowChar2412(258, 480, 83, RED, WHITE);//S
			EIE3810_TFTLCD_ShowChar2412(270, 480, 83, RED, WHITE);//S
			break;
		}
		if(buffer==2)
		{ 
			dir=2;
			EIE3810_TFTLCD_ShowChar2412(198, 480, 83, RED, WHITE);//S
			EIE3810_TFTLCD_ShowChar2412(210, 480, 85, RED, WHITE);//U
			EIE3810_TFTLCD_ShowChar2412(222, 480, 67, RED, WHITE);//C
			EIE3810_TFTLCD_ShowChar2412(234, 480, 67, RED, WHITE);//C
			EIE3810_TFTLCD_ShowChar2412(246, 480, 69, RED, WHITE);//E
			EIE3810_TFTLCD_ShowChar2412(258, 480, 83, RED, WHITE);//S
			EIE3810_TFTLCD_ShowChar2412(270, 480, 83, RED, WHITE);//S
			break;
		}
		if(buffer==3)
		{ 
			dir=3;
			EIE3810_TFTLCD_ShowChar2412(198, 480, 83, RED, WHITE);//S
			EIE3810_TFTLCD_ShowChar2412(210, 480, 85, RED, WHITE);//U
			EIE3810_TFTLCD_ShowChar2412(222, 480, 67, RED, WHITE);//C
			EIE3810_TFTLCD_ShowChar2412(234, 480, 67, RED, WHITE);//C
			EIE3810_TFTLCD_ShowChar2412(246, 480, 69, RED, WHITE);//E
			EIE3810_TFTLCD_ShowChar2412(258, 480, 83, RED, WHITE);//S
			EIE3810_TFTLCD_ShowChar2412(270, 480, 83, RED, WHITE);//S
			break;
		}
		if(buffer==4)
		{ 
			dir=4;
			EIE3810_TFTLCD_ShowChar2412(198, 480, 83, RED, WHITE);//S
			EIE3810_TFTLCD_ShowChar2412(210, 480, 85, RED, WHITE);//U
			EIE3810_TFTLCD_ShowChar2412(222, 480, 67, RED, WHITE);//C
			EIE3810_TFTLCD_ShowChar2412(234, 480, 67, RED, WHITE);//C
			EIE3810_TFTLCD_ShowChar2412(246, 480, 69, RED, WHITE);//E
			EIE3810_TFTLCD_ShowChar2412(258, 480, 83, RED, WHITE);//S
			EIE3810_TFTLCD_ShowChar2412(270, 480, 83, RED, WHITE);//S
			break;
		}
		if(buffer==5)
		{ 
			dir=5;
			EIE3810_TFTLCD_ShowChar2412(198, 480, 83, RED, WHITE);//S
			EIE3810_TFTLCD_ShowChar2412(210, 480, 85, RED, WHITE);//U
			EIE3810_TFTLCD_ShowChar2412(222, 480, 67, RED, WHITE);//C
			EIE3810_TFTLCD_ShowChar2412(234, 480, 67, RED, WHITE);//C
			EIE3810_TFTLCD_ShowChar2412(246, 480, 69, RED, WHITE);//E
			EIE3810_TFTLCD_ShowChar2412(258, 480, 83, RED, WHITE);//S
			EIE3810_TFTLCD_ShowChar2412(270, 480, 83, RED, WHITE);//S
			break;
		}
		if(buffer==6)
		{ 
			dir=6;
			EIE3810_TFTLCD_ShowChar2412(198, 480, 83, RED, WHITE);//S
			EIE3810_TFTLCD_ShowChar2412(210, 480, 85, RED, WHITE);//U
			EIE3810_TFTLCD_ShowChar2412(222, 480, 67, RED, WHITE);//C
			EIE3810_TFTLCD_ShowChar2412(234, 480, 67, RED, WHITE);//C
			EIE3810_TFTLCD_ShowChar2412(246, 480, 69, RED, WHITE);//E
			EIE3810_TFTLCD_ShowChar2412(258, 480, 83, RED, WHITE);//S
			EIE3810_TFTLCD_ShowChar2412(270, 480, 83, RED, WHITE);//S
			break;
		}
		if(buffer==7)
		{ 
			dir=7;
			EIE3810_TFTLCD_ShowChar2412(198, 480, 83, RED, WHITE);//S
			EIE3810_TFTLCD_ShowChar2412(210, 480, 85, RED, WHITE);//U
			EIE3810_TFTLCD_ShowChar2412(222, 480, 67, RED, WHITE);//C
			EIE3810_TFTLCD_ShowChar2412(234, 480, 67, RED, WHITE);//C
			EIE3810_TFTLCD_ShowChar2412(246, 480, 69, RED, WHITE);//E
			EIE3810_TFTLCD_ShowChar2412(258, 480, 83, RED, WHITE);//S
			EIE3810_TFTLCD_ShowChar2412(270, 480, 83, RED, WHITE);//S
			break;
		}}
		Delay(20000000);
		Step4();
	}
}


void JOYPAD_Init(void)
{
	RCC->APB2ENR|=1<<3;
	RCC->APB2ENR|=1<<5;
	GPIOB->CRH&=0xFFFF00FF;
	GPIOB->CRH|=0x00003800;
	GPIOB->ODR|=3<<10;
	GPIOD->CRL&=0xFFFF0FFF;
	GPIOD->CRL|=0x00003000;
	GPIOD->ODR|=1<<3;
}

void JOYPAD_Delay(u16 t)
{
	while(t--);
}

u8 JOYPAD_Read(void)
{
	vu8 temp=0;
	u8 t;
	GPIOB->BSRR |= 1<<11;
	Delay(80);
	GPIOB->BSRR |= 1<<27;
	for(t=0;t<8;t++)
	{
		temp>>=1;
		if((((GPIOB->IDR)>>10)&0x01)==0) temp|=0x80;
		GPIOD->BSRR |= (1<<3);
		Delay(80);
		GPIOD->BSRR |=(1<<19);
		Delay(80);
	}
	return temp;
}

void EIE3810_NVIC_SetPriorityGroup(u8 prigroup)
{
	u32 temp1, temp2;
	temp2 = prigroup&0x00000007;
	temp2 <<=8;
	temp1 = SCB->AIRCR;
	temp1 &= 0x0000F8FF;
	temp1 |= 0x05FA0000;
	temp1 |= temp2;
	SCB->AIRCR = temp1;
}

void EIE3810_TIM2_Init(u16 arr, u16 psc)
{
	//TIM2
	RCC->APB1ENR|= 1<<0;
	TIM2->ARR=arr;
	TIM2->PSC=psc;
	TIM2->DIER|=1<<0;
	TIM2->CR1|=0x01;
	NVIC->IP[28]=0x45;
	NVIC->ISER[0]=(1<<28);
}	

void EIE3810_TIM3_Init(u16 arr, u16 psc)
{
	//TIM3
	RCC->APB1ENR|= 1<<1;
	TIM3->ARR=arr;
	TIM3->PSC=psc;
	TIM3->DIER|=1<<0;
	TIM3->CR1|=0x01;
	NVIC->IP[29]=0x45;
	NVIC->ISER[0]=(1<<29);
}	

void EIE3810_TIM4_Init(u16 arr, u16 psc)
{
	//TIM4
	RCC->APB1ENR|= 1<<2;
	TIM4->ARR=arr;
	TIM4->PSC=psc;
	TIM4->DIER|=1<<0;
	TIM4->CR1|=0x01;
	NVIC->IP[30]=0x45;
	NVIC->ISER[0]=(1<<30);
}	

void EIE3810_TIM5_Init(u16 arr, u16 psc)
{
	//TIM5
	RCC->APB1ENR|= 1<<3;
	TIM5->ARR=arr;
	TIM5->PSC=psc;
	TIM5->DIER|=1<<0;
	TIM5->CR1|=0x01;
	NVIC->IP[18]=0x45;
	NVIC->ISER[1]=(1<<18);
}	

void TIM2_IRQHandler(void)
{
	if (TIM2->SR & 1<<0)
	{
		if (pause == 0)
		{
			show_time_bounces();
		}
	}
	TIM2->SR &= ~(1<<0);
}

void TIM4_IRQHandler(void)
{
	if (TIM4->SR & 1<<0) 
	{
		Game2();
	}
	TIM4->SR &= ~(1<<0);
}

void TIM5_IRQHandler(void)
{
	if (TIM5->SR & 1<<0)
	{
	GameBall();
	Delay(50000);
	pauses();
	}
	TIM5->SR &= ~(1<<0);
}

void Game1(void)
{	
	if (pause == 0)
		{
		if (level == 0)
		{
			EIE3810_TFTLCD_FillRectangle(x1-40,80,785,15,BLACK);	
			
			if (((((GPIOE->IDR)>>2)&1) == 0)&(x1>=40))
			{
				EIE3810_TFTLCD_FillRectangle(x1-40,80,785,15,WHITE);
				x1=x1-2;
				EIE3810_TFTLCD_FillRectangle(x1-40,80,785,15,BLACK);
				Delay(10000);
			}
			if (((((GPIOE->IDR)>>4)&1) == 0)&(x1<=440))
			{
				EIE3810_TFTLCD_FillRectangle(x1-40,80,785,15,WHITE);
				x1=x1+2;
				EIE3810_TFTLCD_FillRectangle(x1-40,80,785,15,BLACK);
				Delay(10000);
			}
		}
			
		if (level == 1)
		{
			EIE3810_TFTLCD_FillRectangle(x1-25,50,785,15,BLACK);	
	
			if (((((GPIOE->IDR)>>2)&1) == 0)&(x1>=25))
			{
				EIE3810_TFTLCD_FillRectangle(x1-25,50,785,15,WHITE);
				x1=x1-2;
				EIE3810_TFTLCD_FillRectangle(x1-25,50,785,15,BLACK);
				Delay(10000);
			}
			if (((((GPIOE->IDR)>>4)&1) == 0)&(x1<=455))
			{
				EIE3810_TFTLCD_FillRectangle(x1-25,50,785,15,WHITE);
				x1=x1+2;
				EIE3810_TFTLCD_FillRectangle(x1-25,50,785,15,BLACK);
				Delay(10000);
			}
		}
	}
}

void Game2(void)
{
	u8 key = JOYPAD_Read();
	if (pause == 0)
	{
		if (level == 0)
		{	
			EIE3810_TFTLCD_FillRectangle(x2-40,80,0,15,BLACK);	
			
			if ((((key>>6)&1) == 1)&(x2>=40))
			{
				EIE3810_TFTLCD_FillRectangle(x2-40,80,0,15,WHITE);
				x2-=8;
				EIE3810_TFTLCD_FillRectangle(x2-40,80,0,15,BLACK);
				Delay(10000);
			}
			if ((((key>>7)&1) == 1)&(x2<=440))
			{
				EIE3810_TFTLCD_FillRectangle(x2-40,80,0,15,WHITE);
				x2+=8;
				EIE3810_TFTLCD_FillRectangle(x2-40,80,0,15,BLACK);
				Delay(10000);
			}
//---------------------------------------------------------			
			EIE3810_TFTLCD_FillRectangle(x1-40,80,785,15,BLACK);	
			
			if (((((GPIOE->IDR)>>2)&1) == 0)&(x1>=40))
			{
				EIE3810_TFTLCD_FillRectangle(x1-40,80,785,15,WHITE);
				x1-=4;
				EIE3810_TFTLCD_FillRectangle(x1-40,80,785,15,BLACK);
				Delay(10000);
			}
			if (((((GPIOE->IDR)>>4)&1) == 0)&(x1<=440))
			{
				EIE3810_TFTLCD_FillRectangle(x1-40,80,785,15,WHITE);
				x1+=4;
				EIE3810_TFTLCD_FillRectangle(x1-40,80,785,15,BLACK);
				Delay(10000);
			}
		}

//Upper are easy level with long pads
//-----------------------------------------------------------------------	
//Following are hard level with short pads

		if (level == 1)
		{	
			EIE3810_TFTLCD_FillRectangle(x2-25,50,0,15,BLACK);	
			
			if ((((key>>6)&1) == 1)&(x2>=25))
			{
				EIE3810_TFTLCD_FillRectangle(x2-25,50,0,15,WHITE);
				x2-=8;
				EIE3810_TFTLCD_FillRectangle(x2-25,50,0,15,BLACK);
				Delay(10000);
			}
			if ((((key>>7)&1) == 1)&(x2<=455))
			{
				EIE3810_TFTLCD_FillRectangle(x2-25,50,0,15,WHITE);
				x2+=8;
				EIE3810_TFTLCD_FillRectangle(x2-25,50,0,15,BLACK);
				Delay(10000);
			}			
//--------------------------------------------------------------------			
			EIE3810_TFTLCD_FillRectangle(x1-25,50,785,15,BLACK);	
	
			if (((((GPIOE->IDR)>>2)&1) == 0)&(x1>=25))
			{
				EIE3810_TFTLCD_FillRectangle(x1-25,50,785,15,WHITE);
				x1-=4;
				EIE3810_TFTLCD_FillRectangle(x1-25,50,785,15,BLACK);
				Delay(10000);
			}
			if (((((GPIOE->IDR)>>4)&1) == 0)&(x1<=455))
			{
				EIE3810_TFTLCD_FillRectangle(x1-25,50,785,15,WHITE);
				x1+=4;
				EIE3810_TFTLCD_FillRectangle(x1-25,50,785,15,BLACK);
				Delay(10000);
			}
		}
	}
}

void GameBall(void)
{
// define how the ball reflect when arrive the edge
	if (ballx <= 15) {right = 1;}
	if (ballx >= 465) {right = 0;}
	if (bally <= 30) {up = 1;}
	if (bally >= 770) {up = 0;}
//-------------------------------------------------------------
//define the directions of the moving of the ball
	if (pause == 0)
	{
	if(dir == 0)
	{
		EIE3810_TFTLCD_DrawCircle(ballx,bally,15,1,WHITE);
		if(right == 1)
			{ballx++;}
		if(right == 0)
			{ballx--;}
		if (up == 1)
			{bally++;}
		if (up == 0)
			{bally--;}
		EIE3810_TFTLCD_DrawCircle(ballx,bally,15,1,RED);
	}
	
	if(dir == 1)
	{
		EIE3810_TFTLCD_DrawCircle(ballx,bally,15,1,WHITE);
		if(right == 1)
			{ballx+=2;}
		if(right == 0)
			{ballx-=2;}
		if (up == 1)
			{bally+=1;}
		if (up == 0)
			{bally-=1;}
		EIE3810_TFTLCD_DrawCircle(ballx,bally,15,1,RED);
	}
	
	if(dir == 2)
	{
		EIE3810_TFTLCD_DrawCircle(ballx,bally,15,1,WHITE);
		if(right == 1)
			{ballx+=3;}
		if(right == 0)
			{ballx-=3;}
		if (up == 1)
			{bally+=1;}
		if (up == 0)
			{bally-=1;}
		EIE3810_TFTLCD_DrawCircle(ballx,bally,15,1,RED);
	}
	
	if(dir == 3)
	{
		EIE3810_TFTLCD_DrawCircle(ballx,bally,15,1,WHITE);
		if(right == 1)
			{ballx+=4;}
		if(right == 0)
			{ballx-=4;}
		if (up == 1)
			{bally+=1;}
		if (up == 0)
			{bally-=1;}
		EIE3810_TFTLCD_DrawCircle(ballx,bally,15,1,RED);
	}
	
	if(dir == 4)
	{
		EIE3810_TFTLCD_DrawCircle(ballx,bally,15,1,WHITE);
		if(right == 1)
			{ballx+=5;}
		if(right == 0)
			{ballx-=5;}
		if (up == 1)
			{bally+=1;}
		if (up == 0)
			{bally-=1;}
		EIE3810_TFTLCD_DrawCircle(ballx,bally,15,1,RED);
	}
	
	if(dir == 5)
	{
		EIE3810_TFTLCD_DrawCircle(ballx,bally,15,1,WHITE);
		if(right == 1)
			{ballx+=6;}
		if(right == 0)
			{ballx-=6;}
		if (up == 1)
			{bally+=1;}
		if (up == 0)
			{bally-=1;}
		EIE3810_TFTLCD_DrawCircle(ballx,bally,15,1,RED);
	}
	
	if(dir == 6)
	{
		EIE3810_TFTLCD_DrawCircle(ballx,bally,15,1,WHITE);
		if(right == 1)
			{ballx+=7;}
		if(right == 0)
			{ballx-=7;}
		if (up == 1)
			{bally+=1;}
		if (up == 0)
			{bally-=1;}
		EIE3810_TFTLCD_DrawCircle(ballx,bally,15,1,RED);
	}
	
	if(dir == 7)
	{
		EIE3810_TFTLCD_DrawCircle(ballx,bally,15,1,WHITE);
		if(right == 1)
			{ballx+=8;}
		if(right == 0)
			{ballx-=8;}
		if (up == 1)
			{bally+=1;}
		if (up == 0)
			{bally-=1;}
		EIE3810_TFTLCD_DrawCircle(ballx,bally,15,1,RED);
	}
}
	
	if(level==0)
	{
		if ((bally <= 30)&((ballx<x2-40)|(ballx>x2+40)))
			{GameOver();bally = 100;}	
		if ((bally >= 770)&((ballx<x1-40)|(ballx>x1+40)))
			{GameOver();bally = 100;}	
	}	
	
	if(level==1)
	{
		if ((bally <= 30)&((ballx<x2-25)|(ballx>x2+25)))
			{GameOver();bally = 100;}	
		if ((bally >= 770)&((ballx<x1-25)|(ballx>x1+25)))
			{GameOver();bally = 100;}	
	}

		if ((ballx <= 15)|(ballx >= 465)|(bally <= 30)|(bally >= 770))
		{
			GPIOB->BSRR = 1<<8;
			Delay(10000);
			GPIOB->BRR = 1<<8;
		}
}

void show_time_bounces(void)
{
	EIE3810_TFTLCD_ShowChar2412(10, 300, 116, RED, WHITE);//t
	EIE3810_TFTLCD_ShowChar2412(22, 300, 105, RED, WHITE);//i
	EIE3810_TFTLCD_ShowChar2412(34, 300, 109, RED, WHITE);//m
	EIE3810_TFTLCD_ShowChar2412(46, 300, 101, RED, WHITE);//e
	EIE3810_TFTLCD_ShowChar2412(58, 300, 58, RED, WHITE);//:
	
	EIE3810_TFTLCD_ShowChar2412(82, 300, 109, RED, WHITE);//m
	EIE3810_TFTLCD_ShowChar2412(118, 300, 115, RED, WHITE);//s	
	
	EIE3810_TFTLCD_ShowChar2412(10, 324, 98, RED, WHITE);//b
	EIE3810_TFTLCD_ShowChar2412(22, 324, 111, RED, WHITE);//o
	EIE3810_TFTLCD_ShowChar2412(34, 324, 117, RED, WHITE);//u
	EIE3810_TFTLCD_ShowChar2412(46, 324, 110, RED, WHITE);//n
	EIE3810_TFTLCD_ShowChar2412(58, 324, 99, RED, WHITE);//c
	EIE3810_TFTLCD_ShowChar2412(70, 324, 101, RED, WHITE);//e
	EIE3810_TFTLCD_ShowChar2412(82, 324, 115, RED, WHITE);//s	
	EIE3810_TFTLCD_ShowChar2412(94, 324, 58, RED, WHITE);//:
	
	EIE3810_TFTLCD_ShowChar2412(70, 300, (i/60)+48, RED, WHITE);//min		
	EIE3810_TFTLCD_ShowChar2412(94, 300, ((i%60)/10)+48, RED, WHITE);//second1
	EIE3810_TFTLCD_ShowChar2412(106, 300, (i%10)+48, RED, WHITE);//second2
	i++;
	
	if ((bally <= 40)|(bally >= 760))
	{
		bounces++;
	}
	EIE3810_TFTLCD_ShowChar2412(106, 324, (bounces/10)+48, RED, WHITE);//bounces1
	EIE3810_TFTLCD_ShowChar2412(118, 324, (bounces%10)+48, RED, WHITE);//bounces2
}

void GameOver(void)
{
	pause = 100;
	RCC->APB1ENR|= 0x00000000;

	Delay(1000000);
	EIE3810_TFTLCD_FillRectangle(0,480,0,800,BLACK);
	EIE3810_TFTLCD_ShowChar2412(186, 300, 71, RED, BLACK );//G
	EIE3810_TFTLCD_ShowChar2412(198, 300, 65, RED, BLACK);//A
	EIE3810_TFTLCD_ShowChar2412(210, 300, 77, RED, BLACK);//M
	EIE3810_TFTLCD_ShowChar2412(222, 300, 69, RED, BLACK);//E
	EIE3810_TFTLCD_ShowChar2412(234, 300, 32, RED, BLACK);// 
	EIE3810_TFTLCD_ShowChar2412(246, 300, 79, RED, BLACK);//O	
	EIE3810_TFTLCD_ShowChar2412(258, 300, 86, RED, BLACK);//V	
	EIE3810_TFTLCD_ShowChar2412(270, 300, 69, RED, BLACK);//E	
	EIE3810_TFTLCD_ShowChar2412(282, 300, 82, RED, BLACK);//R	
	
		EIE3810_TFTLCD_ShowChar2412(150, 400, 80, RED, BLACK );//P
		EIE3810_TFTLCD_ShowChar2412(162, 400, 108, RED, BLACK );//l
		EIE3810_TFTLCD_ShowChar2412(174, 400, 97, RED, BLACK );//a
		EIE3810_TFTLCD_ShowChar2412(186, 400, 121, RED, BLACK );//y
		EIE3810_TFTLCD_ShowChar2412(198, 400, 101, RED, BLACK );//e
		EIE3810_TFTLCD_ShowChar2412(210, 400, 114, RED, BLACK );//r
		EIE3810_TFTLCD_ShowChar2412(222, 400, 32, RED, BLACK );// 
		EIE3810_TFTLCD_ShowChar2412(246, 400, 32, RED, BLACK );// 
		EIE3810_TFTLCD_ShowChar2412(258, 400, 108, RED, BLACK );//l
		EIE3810_TFTLCD_ShowChar2412(270, 400, 111, RED, BLACK );//o
		EIE3810_TFTLCD_ShowChar2412(282, 400, 115, RED, BLACK );//s
		EIE3810_TFTLCD_ShowChar2412(294, 400, 101, RED, BLACK );//e
		EIE3810_TFTLCD_ShowChar2412(306, 400, 115, RED, BLACK );//s
		EIE3810_TFTLCD_ShowChar2412(318, 400, 33, RED, BLACK );//!	
	
	if (bally<=770)
	{
		EIE3810_TFTLCD_ShowChar2412(234, 400, 65, RED, BLACK );//A
	}
	
	if (bally<=30)
	{
		EIE3810_TFTLCD_ShowChar2412(234, 400, 66, RED, BLACK );//B
	}
}

void Step1(void)
{
	EIE3810_TFTLCD_ShowChar2412(100, 100, 87, WHITE, BLUE);//W
	EIE3810_TFTLCD_ShowChar2412(112, 100, 101, WHITE, BLUE);//e
	EIE3810_TFTLCD_ShowChar2412(124, 100, 108, WHITE, BLUE);//l
	EIE3810_TFTLCD_ShowChar2412(136, 100, 99, WHITE, BLUE);//c
	EIE3810_TFTLCD_ShowChar2412(148, 100, 111, WHITE, BLUE);//o
	EIE3810_TFTLCD_ShowChar2412(160, 100, 109, WHITE, BLUE);//m
	EIE3810_TFTLCD_ShowChar2412(172, 100, 101, WHITE, BLUE);//e
	EIE3810_TFTLCD_ShowChar2412(184, 100, 32, WHITE, BLUE);// 
	EIE3810_TFTLCD_ShowChar2412(196, 100, 116, WHITE, BLUE);//t
	EIE3810_TFTLCD_ShowChar2412(208, 100, 111, WHITE, BLUE);//o
	EIE3810_TFTLCD_ShowChar2412(220, 100, 32, WHITE, BLUE);//
	EIE3810_TFTLCD_ShowChar2412(232, 100, 109, WHITE, BLUE);//m
	EIE3810_TFTLCD_ShowChar2412(244, 100, 105, WHITE, BLUE);//i
	EIE3810_TFTLCD_ShowChar2412(256, 100, 110, WHITE, BLUE);//n
	EIE3810_TFTLCD_ShowChar2412(268, 100, 105, WHITE, BLUE);//i
	EIE3810_TFTLCD_ShowChar2412(280, 100, 32, WHITE, BLUE);// 
	EIE3810_TFTLCD_ShowChar2412(292, 100, 80, WHITE, BLUE);//P
	EIE3810_TFTLCD_ShowChar2412(304, 100, 114, WHITE, BLUE);//r
	EIE3810_TFTLCD_ShowChar2412(316, 100, 111, WHITE, BLUE);//o
	EIE3810_TFTLCD_ShowChar2412(328, 100, 106, WHITE, BLUE);//j
	EIE3810_TFTLCD_ShowChar2412(340, 100, 101, WHITE, BLUE);//e
	EIE3810_TFTLCD_ShowChar2412(352, 100, 99, WHITE, BLUE);//c
	EIE3810_TFTLCD_ShowChar2412(364, 100, 116, WHITE, BLUE);//t
	EIE3810_TFTLCD_ShowChar2412(376, 100, 33, WHITE, BLUE);//!
	Delay(10000000);	
	EIE3810_TFTLCD_ShowChar1608(100, 180, 84, WHITE, RED);//T
	EIE3810_TFTLCD_ShowChar1608(108, 180, 104, WHITE, RED);//h
	EIE3810_TFTLCD_ShowChar1608(116, 180, 105, WHITE, RED);//i
	EIE3810_TFTLCD_ShowChar1608(124, 180, 115, WHITE, RED);//s
	EIE3810_TFTLCD_ShowChar1608(132, 180, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar1608(140, 180, 105, WHITE, RED);//i
	EIE3810_TFTLCD_ShowChar1608(148, 180, 115, WHITE, RED);//s
	EIE3810_TFTLCD_ShowChar1608(156, 180, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar1608(164, 180, 116, WHITE, RED);//t
	EIE3810_TFTLCD_ShowChar1608(172, 180, 104, WHITE, RED);//h
	EIE3810_TFTLCD_ShowChar1608(180, 180, 101, WHITE, RED);//e
	EIE3810_TFTLCD_ShowChar1608(188, 180, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar1608(196, 180, 70, WHITE, RED);//F
	EIE3810_TFTLCD_ShowChar1608(204, 180, 105, WHITE, RED);//i
	EIE3810_TFTLCD_ShowChar1608(212, 180, 110, WHITE, RED);//n
	EIE3810_TFTLCD_ShowChar1608(220, 180, 97, WHITE, RED);//a
	EIE3810_TFTLCD_ShowChar1608(228, 180, 108, WHITE, RED);//l
	EIE3810_TFTLCD_ShowChar1608(236, 180, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar1608(244, 180, 76, WHITE, RED);//L
	EIE3810_TFTLCD_ShowChar1608(252, 180, 97, WHITE, RED);//a
	EIE3810_TFTLCD_ShowChar1608(260, 180, 98, WHITE, RED);//b
	EIE3810_TFTLCD_ShowChar1608(268, 180, 46, WHITE, RED);//.
	Delay(10000000);
	EIE3810_TFTLCD_ShowChar1608(100, 240, 65, WHITE, RED);//A
	EIE3810_TFTLCD_ShowChar1608(108, 240, 114, WHITE, RED);//r
	EIE3810_TFTLCD_ShowChar1608(116, 240, 101, WHITE, RED);//e
	EIE3810_TFTLCD_ShowChar1608(124, 240, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar1608(132, 240, 121, WHITE, RED);//y
	EIE3810_TFTLCD_ShowChar1608(140, 240, 111, WHITE, RED);//o
	EIE3810_TFTLCD_ShowChar1608(148, 240, 117, WHITE, RED);//u
	EIE3810_TFTLCD_ShowChar1608(156, 240, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar1608(164, 240, 114, WHITE, RED);//r
	EIE3810_TFTLCD_ShowChar1608(172, 240, 101, WHITE, RED);//e
	EIE3810_TFTLCD_ShowChar1608(180, 240, 97, WHITE, RED);//a
	EIE3810_TFTLCD_ShowChar1608(188, 240, 100, WHITE, RED);//d
	EIE3810_TFTLCD_ShowChar1608(196, 240, 121, WHITE, RED);//y
	EIE3810_TFTLCD_ShowChar1608(204, 240, 63, WHITE, RED);//?
	Delay(10000000);
	EIE3810_TFTLCD_ShowChar1608(100, 300, 79, WHITE, RED);//O
	EIE3810_TFTLCD_ShowChar1608(108, 300, 75, WHITE, RED);//K
	EIE3810_TFTLCD_ShowChar1608(116, 300, 33, WHITE, RED);//!
	EIE3810_TFTLCD_ShowChar1608(124, 300, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar1608(132, 300, 76, WHITE, RED);//L
	EIE3810_TFTLCD_ShowChar1608(140, 300, 101, WHITE, RED);//e
	EIE3810_TFTLCD_ShowChar1608(148, 300, 116, WHITE, RED);//t
	EIE3810_TFTLCD_ShowChar1608(156, 300, 39, WHITE, RED);//'
	EIE3810_TFTLCD_ShowChar1608(164, 300, 115, WHITE, RED);//s
	EIE3810_TFTLCD_ShowChar1608(172, 300, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar1608(180, 300, 115, WHITE, RED);//s
	EIE3810_TFTLCD_ShowChar1608(188, 300, 116, WHITE, RED);//t
	EIE3810_TFTLCD_ShowChar1608(196, 300, 97, WHITE, RED);//a
	EIE3810_TFTLCD_ShowChar1608(204, 300, 114, WHITE, RED);//r
	EIE3810_TFTLCD_ShowChar1608(212, 300, 116, WHITE, RED);//t
	EIE3810_TFTLCD_ShowChar1608(220, 300, 46, WHITE, RED);//.
	Delay(10000000);
	
	EIE3810_TFTLCD_FillRectangle(0,480,0,800,WHITE);
	EIE3810_TFTLCD_ShowChar1608(100, 300, 80, WHITE, RED);//P
	EIE3810_TFTLCD_ShowChar1608(108, 300, 108, WHITE, RED);//l
	EIE3810_TFTLCD_ShowChar1608(116, 300, 101, WHITE, RED);//e
	EIE3810_TFTLCD_ShowChar1608(124, 300, 97, WHITE, RED);//a
	EIE3810_TFTLCD_ShowChar1608(132, 300, 115, WHITE, RED);//s
	EIE3810_TFTLCD_ShowChar1608(140, 300, 101, WHITE, RED);//e
	EIE3810_TFTLCD_ShowChar1608(148, 300, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar1608(156, 300, 115, WHITE, RED);//s
	EIE3810_TFTLCD_ShowChar1608(164, 300, 101, WHITE, RED);//e
	EIE3810_TFTLCD_ShowChar1608(172, 300, 108, WHITE, RED);//l
	EIE3810_TFTLCD_ShowChar1608(180, 300, 101, WHITE, RED);//e
	EIE3810_TFTLCD_ShowChar1608(188, 300, 99, WHITE, RED);//c
	EIE3810_TFTLCD_ShowChar1608(196, 300, 116, WHITE, RED);//t
	EIE3810_TFTLCD_ShowChar1608(204, 300, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar1608(212, 300, 116, WHITE, RED);//t
	EIE3810_TFTLCD_ShowChar1608(220, 300, 104, WHITE, RED);//h
	EIE3810_TFTLCD_ShowChar1608(228, 300, 101, WHITE, RED);//e
	EIE3810_TFTLCD_ShowChar1608(236, 300, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar1608(244, 300, 100, WHITE, RED);//d
	EIE3810_TFTLCD_ShowChar1608(252, 300, 105, WHITE, RED);//i
	EIE3810_TFTLCD_ShowChar1608(260, 300, 102, WHITE, RED);//f
	EIE3810_TFTLCD_ShowChar1608(268, 300, 102, WHITE, RED);//f
	EIE3810_TFTLCD_ShowChar1608(276, 300, 105, WHITE, RED);//i
	EIE3810_TFTLCD_ShowChar1608(284, 300, 99, WHITE, RED);//c
	EIE3810_TFTLCD_ShowChar1608(292, 300, 117, WHITE, RED);//u
	EIE3810_TFTLCD_ShowChar1608(300, 300, 108, WHITE, RED);//l
	EIE3810_TFTLCD_ShowChar1608(308, 300, 116, WHITE, RED);//t
	EIE3810_TFTLCD_ShowChar1608(316, 300, 121, WHITE, RED);//y
	EIE3810_TFTLCD_ShowChar1608(324, 300, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar1608(332, 300, 108, WHITE, RED);//l
	EIE3810_TFTLCD_ShowChar1608(340, 300, 101, WHITE, RED);//e
	EIE3810_TFTLCD_ShowChar1608(348, 300, 118, WHITE, RED);//v
	EIE3810_TFTLCD_ShowChar1608(356, 300, 101, WHITE, RED);//e
	EIE3810_TFTLCD_ShowChar1608(364, 300, 108, WHITE, RED);//l
	EIE3810_TFTLCD_ShowChar1608(372, 300, 58, WHITE, RED);//:

	EIE3810_TFTLCD_ShowChar1608(100, 350, 69, WHITE, BLUE);//E
	EIE3810_TFTLCD_ShowChar1608(108, 350, 97, WHITE, BLUE);//a
	EIE3810_TFTLCD_ShowChar1608(116, 350, 115, WHITE, BLUE);//s
	EIE3810_TFTLCD_ShowChar1608(124, 350, 121, WHITE, BLUE);//y
	
	EIE3810_TFTLCD_ShowChar1608(100, 400, 72, BLUE, WHITE);//H
	EIE3810_TFTLCD_ShowChar1608(108, 400, 97, BLUE, WHITE);//a
	EIE3810_TFTLCD_ShowChar1608(116, 400, 114, BLUE, WHITE);//r
	EIE3810_TFTLCD_ShowChar1608(124, 400, 100, BLUE, WHITE);//d
	
	EIE3810_TFTLCD_ShowChar1608(100, 450, 80, WHITE, RED);//P
	EIE3810_TFTLCD_ShowChar1608(108, 450, 114, WHITE, RED);//r
	EIE3810_TFTLCD_ShowChar1608(116, 450, 101, WHITE, RED);//e
	EIE3810_TFTLCD_ShowChar1608(124, 450, 115, WHITE, RED);//s
	EIE3810_TFTLCD_ShowChar1608(132, 450, 115, WHITE, RED);//s
	EIE3810_TFTLCD_ShowChar1608(140, 450, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar1608(148, 450, 75, WHITE, RED);//K
	EIE3810_TFTLCD_ShowChar1608(156, 450, 69, WHITE, RED);//E
	EIE3810_TFTLCD_ShowChar1608(164, 450, 89, WHITE, RED);//Y
	EIE3810_TFTLCD_ShowChar1608(172, 450, 48, WHITE, RED);//0
	EIE3810_TFTLCD_ShowChar1608(180, 450, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar1608(188, 450, 116, WHITE, RED);//t
	EIE3810_TFTLCD_ShowChar1608(196, 450, 111, WHITE, RED);//o
	EIE3810_TFTLCD_ShowChar1608(204, 450, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar1608(212, 450, 101, WHITE, RED);//e
	EIE3810_TFTLCD_ShowChar1608(220, 450, 110, WHITE, RED);//n
	EIE3810_TFTLCD_ShowChar1608(228, 450, 116, WHITE, RED);//t
	EIE3810_TFTLCD_ShowChar1608(236, 450, 101, WHITE, RED);//e
	EIE3810_TFTLCD_ShowChar1608(244, 450, 114, WHITE, RED);//r
	EIE3810_TFTLCD_ShowChar1608(252, 450, 46, WHITE, RED);//.
}

void Step2(void)
{
	u32 Key0;
	u32 Key1;
	u32 Changed_Key1;
	u32 Key_up;
	u32 Changed_Key_up;

	while(1) //use trigger to choose the hard level of the game in a while(a) loop
	{	
		Key0 = (GPIOE->IDR&GPIO_Pin_4);
		Key1 = (GPIOE->IDR&GPIO_Pin_3);
		Key_up = (GPIOA->IDR&GPIO_Pin_0);
		Delay (500000);

		Changed_Key1 = (GPIOE->IDR&GPIO_Pin_3);
		if (Changed_Key1 == 0)
		{
			if (Changed_Key1 < Key1)
			{ 
					if (level == 0)
					{
						level++;
						EIE3810_TFTLCD_FillRectangle(100,32,350,58,WHITE);
						EIE3810_TFTLCD_ShowChar1608(100, 350, 69, BLUE, WHITE);//E
						EIE3810_TFTLCD_ShowChar1608(108, 350, 97, BLUE, WHITE);//a
						EIE3810_TFTLCD_ShowChar1608(116, 350, 115, BLUE, WHITE);//s
						EIE3810_TFTLCD_ShowChar1608(124, 350, 121, BLUE, WHITE);//y

						EIE3810_TFTLCD_ShowChar1608(100, 400, 72, WHITE, BLUE);//H
						EIE3810_TFTLCD_ShowChar1608(108, 400, 97, WHITE, BLUE);//a
						EIE3810_TFTLCD_ShowChar1608(116, 400, 114, WHITE, BLUE);//r
						EIE3810_TFTLCD_ShowChar1608(124, 400, 100, WHITE, BLUE);//d
					}
			}
		}
		Changed_Key_up = (GPIOA->IDR&GPIO_Pin_0);
		
		if (Changed_Key_up == GPIO_Pin_0)
		{
			if (Key_up < Changed_Key_up)
			{
					if (level == 1)
					{
						level--;
						EIE3810_TFTLCD_FillRectangle(100,32,350,58,WHITE);
						EIE3810_TFTLCD_ShowChar1608(100, 350, 69, WHITE, BLUE);//E
						EIE3810_TFTLCD_ShowChar1608(108, 350, 97, WHITE, BLUE);//a
						EIE3810_TFTLCD_ShowChar1608(116, 350, 115, WHITE, BLUE);//s
						EIE3810_TFTLCD_ShowChar1608(124, 350, 121, WHITE, BLUE);//y

						EIE3810_TFTLCD_ShowChar1608(100, 400, 72, BLUE, WHITE);//H
						EIE3810_TFTLCD_ShowChar1608(108, 400, 97, BLUE, WHITE);//a
						EIE3810_TFTLCD_ShowChar1608(116, 400, 114, BLUE, WHITE);//r
						EIE3810_TFTLCD_ShowChar1608(124, 400, 100, BLUE, WHITE);//d
					}
			}
		}
		
		if (Key0 == 0)
		{
			break;
		}
	}
}

void Step3(void)
{	
	EIE3810_TFTLCD_FillRectangle(0,480,0,800,WHITE);
	EIE3810_TFTLCD_ShowChar2412(42, 300, 85, WHITE, RED);//U
	EIE3810_TFTLCD_ShowChar2412(54, 300, 115, WHITE, RED);//s
	EIE3810_TFTLCD_ShowChar2412(66, 300, 101, WHITE, RED);//e
	EIE3810_TFTLCD_ShowChar2412(78, 300, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar2412(90, 300, 85, WHITE, RED);//U
	EIE3810_TFTLCD_ShowChar2412(102, 300, 83, WHITE, RED);//S
	EIE3810_TFTLCD_ShowChar2412(114, 300, 65, WHITE, RED);//A
	EIE3810_TFTLCD_ShowChar2412(126, 300, 82, WHITE, RED);//R
	EIE3810_TFTLCD_ShowChar2412(138, 300, 84, WHITE, RED);//T
	EIE3810_TFTLCD_ShowChar2412(150, 300, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar2412(162, 300, 102, WHITE, RED);//f
	EIE3810_TFTLCD_ShowChar2412(174, 300, 111, WHITE, RED);//o
	EIE3810_TFTLCD_ShowChar2412(186, 300, 114, WHITE, RED);//r
	EIE3810_TFTLCD_ShowChar2412(198, 300, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar2412(210, 300, 97, WHITE, RED);//a
	EIE3810_TFTLCD_ShowChar2412(222, 300, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar2412(234, 300, 114, WHITE, RED);//r
	EIE3810_TFTLCD_ShowChar2412(246, 300, 97, WHITE, RED);//a
	EIE3810_TFTLCD_ShowChar2412(258, 300, 110, WHITE, RED);//n
	EIE3810_TFTLCD_ShowChar2412(270, 300, 100, WHITE, RED);//d
	EIE3810_TFTLCD_ShowChar2412(282, 300, 111, WHITE, RED);//o
	EIE3810_TFTLCD_ShowChar2412(294, 300, 109, WHITE, RED);//m
	EIE3810_TFTLCD_ShowChar2412(306, 300, 32, WHITE, RED);// 
	EIE3810_TFTLCD_ShowChar2412(318, 300, 100, WHITE, RED);//d
	EIE3810_TFTLCD_ShowChar2412(330, 300, 105, WHITE, RED);//i
	EIE3810_TFTLCD_ShowChar2412(342, 300, 114, WHITE, RED);//r
	EIE3810_TFTLCD_ShowChar2412(354, 300, 101, WHITE, RED);//e
	EIE3810_TFTLCD_ShowChar2412(366, 300, 99, WHITE, RED);//c
	EIE3810_TFTLCD_ShowChar2412(378, 300, 116, WHITE, RED);//t
	EIE3810_TFTLCD_ShowChar2412(390, 300, 105, WHITE, RED);//i
	EIE3810_TFTLCD_ShowChar2412(402, 300, 111, WHITE, RED);//o
	EIE3810_TFTLCD_ShowChar2412(414, 300, 110, WHITE, RED);//n
	EIE3810_TFTLCD_ShowChar2412(426, 300, 46, WHITE, RED);//.
	EIE3810_USART1_EXTIInit();
  USART1_IRQHandler();
}

void Step4(void)
{
	EIE3810_TFTLCD_FillRectangle(0,480,0,800,WHITE);
	
	EIE3810_TFTLCD_FillRectangle(202,75,330,140,WHITE);
	EIE3810_TFTLCD_SevenSegment(202, 330, 3, RED);
	Delay(10000000);	
	
	EIE3810_TFTLCD_FillRectangle(202,75,330,140,WHITE);
	EIE3810_TFTLCD_SevenSegment(202, 330, 2, RED);
	Delay(10000000);
	
	EIE3810_TFTLCD_FillRectangle(202,75,330,140,WHITE);
	EIE3810_TFTLCD_SevenSegment(202, 330, 1, RED);
	Delay(10000000);	
	
	EIE3810_TFTLCD_FillRectangle(202,75,330,140,WHITE);
	EIE3810_TFTLCD_SevenSegment(202, 330, 0, RED);
	Delay(10000000);
	
	EIE3810_TFTLCD_FillRectangle(0,480,0,800,WHITE);
	
//------------------------------------------------------Initial for the timers that will be used in the game soon
	EIE3810_NVIC_SetPriorityGroup(5);
	JOYPAD_Init();
	EIE3810_TIM2_Init(9999,7199);
	EIE3810_TIM4_Init(499,719);
	EIE3810_TIM5_Init(1999,719);
}

void pauses(void) //use trigger to control the pause of the game
{
	Changed_Key1 = (((GPIOE->IDR)>>3)&1);
	if (Changed_Key1 == 0){
		Delay(100);
		if (Changed_Key1 == 0){
			if (Changed_Key1 < Key1){
				if (pause == 0){
					pause = 1;}
				else	
					pause = 0;}}}
	
	Changed_Start = ((JOYPAD_Read()>>3)&1);
	if (Changed_Start == 1){
		Delay(100);
		if (Changed_Start == 1){
			if (Changed_Start > Start){
				if (pause == 0){
					pause = 1;}
				else	
					pause = 0;}}}
	
	Key1 = Changed_Key1;
	Start = Changed_Start;
}
