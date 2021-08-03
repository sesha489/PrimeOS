#include"EventHandlers.h"

void InitEvtHandler(){
	RCC->APB2ENR |= (1U << 14);	//Enabling SYSCFG clock
	GPIOC->MODER |= (0x00 << 13*2);	//Port-C Pin-13 User Push Button

	SYSCFG->EXTICR[3] = 0x00000020;
	EXTI->IMR = 0x00002000;
	EXTI->RTSR = 0x00002000;
	EXTI->FTSR = 0x00000000;

	NVIC_SetPriority(EXTI15_10_IRQn, 0);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI15_10_IRQHandler(void){
	if(EXTI->PR & 0x00002000){
		EXTI->PR |= 0x00002000;
		RaiseCount++;
	}
}
