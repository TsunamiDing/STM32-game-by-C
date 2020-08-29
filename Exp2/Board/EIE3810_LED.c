#include "stm32f10x.h"
#include "EIE3810_LED.h"

// put your code here
void EIE3810_LED_Init(void)
{
	RCC->APB2ENR |= 1<<3;
	RCC->APB2ENR |= 1<<6;

	GPIOB->CRL &= 0xFF0FFFFF;
	GPIOB->CRL |= 0x00300000;
	
	GPIOE->CRL &= 0xFF0FFFFF;
	GPIOE->CRL |= 0x00300000;
}
