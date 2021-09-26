#include"EventHandlers.h"

void InitEvtHandler(){
	RCC->APB2ENR |= (1U << 14);	//Enabling SYSCFG clock
	GPIOC->MODER |= (0b00 << 13*2);	//Port-C Pin-13 User Push Button

	SYSCFG->EXTICR[3] = 0x00000020;
	EXTI->IMR = 0x00002000;
	EXTI->RTSR = 0x00002000;
	EXTI->FTSR = 0x00000000;

	NVIC_SetPriority(EXTI15_10_IRQn, 0);
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	ClickEvent = 0;
	RaiseCount = 0;
	FallCount = 0;

	ClickTimeStamp.tpmsec = 0;
	ClickTimeStamp.tpsec = 0;
	ClickTimeStamp.tpmin = 0;
	ClickTimeStamp.tphr = 0;
}

void RecordTimeStamp(void){
	ClickTimeStamp.tpmsec = mSec;
	ClickTimeStamp.tpsec = sec;
	ClickTimeStamp.tpmin = min;
	ClickTimeStamp.tphr = hour;
}

void SingleClick(void){
	ClickEvent = 1;
}

void DoubleClick(void){
	ClickEvent = 2;
}

void EXTI15_10_IRQHandler(void){
	if(EXTI->PR & 0x00002000){
		EXTI->PR |= 0x00002000;
		if((min-ClickTimeStamp.tpmin) == 0){
			if((sec-ClickTimeStamp.tpsec) > 0){
				RaiseCount++;
				RecordTimeStamp();
				SingleClick();
			}else{
				if((mSec-ClickTimeStamp.tpmsec) >= 250){
					RaiseCount++;
					RecordTimeStamp();
					DoubleClick();
				}
			}
		}else{
			RaiseCount++;
			RecordTimeStamp();
			SingleClick();
		}
	}
}
