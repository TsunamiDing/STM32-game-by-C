#include "stm32f10x.h"
#include "EIE3810_USART.h"

void EIE3810_USART2_init(u32 pclk1, u32 baudrate)
{
	//USART2
	float temp;
	u16 mantissa;
	u16 fraction;
	temp=(float) (pclk1*1000000)/(baudrate*16);
	mantissa=temp;
	fraction=(temp-mantissa)*16;
	mantissa<<=4;
	mantissa+=fraction;
	RCC->APB2ENR |= 1<<2; //Add comments	
	RCC->APB1ENR |= 1<<17; //Add comments	
	GPIOA->CRL &= 0xFFFF00FF; //Add comments
	GPIOA->CRL |= 0x00008B00; //Add comments
	RCC->APB1RSTR |= 1<<17; //Add comments
	RCC->APB1RSTR &= ~(1<<17); //Add comments
	USART2->BRR=mantissa;//Add comments
	USART2->CR1=0x2008; //Add comments
}
void EIE3810_USART1_init(u32 pclk1, u32 baudrate)
{
	//USART1
	float temp;
	u16 mantissa;
	u16 fraction;
	temp=(float) (pclk1*1000000)/(baudrate*16);
	mantissa=temp;
	fraction=(temp-mantissa)*16;
	mantissa<<=4;
	mantissa+=fraction;
	RCC->APB2ENR |= 1<<2; //Add comments	
	RCC->APB2ENR |= 1<<14; //Add comments	
	GPIOA->CRH &= 0xFFFFF00F; //Add comments
	GPIOA->CRH |= 0x000008B0; //Add comments
	RCC->APB2RSTR |= 1<<14; //Add comments
	RCC->APB2RSTR &= ~(1<<14); //Add comments
	USART1->BRR=mantissa;//Add comments
	USART1->CR1=0x202C; //Add comments
}
void USART_print(u8 USARTport, char *st)
{
	u8 i=0;
	while(st[i] != 0x00)
	{
		if (USARTport == 1) USART1 ->DR = st[i];
		while(USART1->SR>>7 == 0){}
		if (USARTport == 2) USART2 ->DR = st[i];
		while(USART2->SR>>7 == 0){}
		if (i==255) break;
		i++;
	}
}
