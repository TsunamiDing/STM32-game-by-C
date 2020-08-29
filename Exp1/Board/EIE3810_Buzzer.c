#include "stm32f10x.h"
#include "EIE3810_Buzzer.h"

// put procedure header here
void EIE3810_Buzzer_Init(void)
{
	RCC->APB2ENR |= 1<<3;
	GPIOB->CRH &= 0xFFFFFFF0;
	GPIOB->CRH |= 0x00000003;
}
