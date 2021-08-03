//PrimOS
//24 Nov 2020
//S.Seshadri

#include"FAT16.h"
#include"EventHandlers.h"

int main (void){
	ClockConfigEx();
	Init_TFT();
	Paint_Colour(White);

	SDC_SPI_Init();
	_msDelay(3000);
	FAT16_INIT();
	_msDelay(3000);
	Paint_Colour(White);

	InitEvtHandler();

	char a[20];
	while(1){
		sprintf(a,"%d seconds", sec);
		WriteText5x8(20, 20, a, Black);
		sprintf(a,"%d minutes", min);
		WriteText5x8(20, 40, a, Black);
		sprintf(a,"%d hours", hour);
		WriteText5x8(20, 60, a, Black);

		//If user push button pressed ON green LED
		/*if (ClickEvent){
			WriteText5x8(20, 100, "Clicked", Black);*/
			/*GPIOB->ODR |= (1U << 0);
			GPIOB->ODR |= (1U << 7);
			GPIOB->ODR |= (1U << 14);*/
		/*}else{
			WriteText5x8(20, 100, "Noclick", Black);*/
			/*GPIOB->ODR &= ~(1U << 0);
			GPIOB->ODR &= ~(1U << 7);
			GPIOB->ODR &= ~(1U << 14);*/
		//}
		sprintf(a,"%d", RaiseCount);
		WriteText5x8(20, 100, a, Black);
	}
}
