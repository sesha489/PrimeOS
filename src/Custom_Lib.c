#include"Custom_Lib.h"

#pragma GCC optimize ("O0")

void _msDelay(uint16_t delaymSec){
	delayCounts = delaymSec;

	while(delayCounts>0){

	}
}

void ClockConfigEx(void){

	mSec = 0;
	sec = 0;
	min = 0;
	hour = 0;
	//MHz = 0;

	FLASH->ACR |= 0x00000004;
	RCC->PLLCFGR = 0x29006C10;//p=2, n=432, m=16 24006C10
	RCC->CFGR = 0x0000940A;//94=APB2(108MHz), B4=APB2(54MHz)
	//Set APB1 = 4; APB2 = 2(108MHz)/4(54MHz) in RCC->CFGR as desired
	RCC->CR |= 0x3F000003;//PLLON and HSION
	for(uint16_t i=0;i<10000;i++)

	SystemCoreClockUpdate();
	//_msDelay(200);
	//MHz = SystemCoreClock;
	SysTick_Config(SystemCoreClock/1000);
}

void SysTick_Handler(void){
 	if(mSec<1000){
 		mSec++;
 		if(delayCounts>0){
 			delayCounts--;
 		}
 	}else{
 		sec++;
 		mSec = 0;
 	}
 	if(sec>=60){
 		min++;
 		sec = 0;
 	}
 	if(min>=60){
 		hour++;
 		min = 0;
 	}
 	//Set ^= 1U;
}
