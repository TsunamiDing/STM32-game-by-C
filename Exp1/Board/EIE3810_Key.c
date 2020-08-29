#include "stm32f10x.h"
#include "EIE3810_KEY.h"

// put your procedure and code here
void EIE3810_Key_Init(void)
{
	RCC->APB2ENR |= 1<<2;
	RCC->APB2ENR |= 1<<6;

	GPIOA->CRL &= 0xFFFFFFF0;
	GPIOA->CRL |= 0x00000008;
	
	GPIOE->CRL &= 0xFFF000FF;
	GPIOE->CRL |= 0x00000800;
	GPIOE->CRL |= 0x00008000;
	GPIOE->CRL |= 0x00080000;

	GPIOA->ODR |= 0<<0;
	GPIOE->ODR |= 1<<2;
	GPIOE->ODR |= 1<<3;
	GPIOE->ODR |= 1<<4;
}
