#include"SDC.h"

#pragma GCC optimize ("O0")

uint8_t SPI_Transfer(uint8_t data){
	*(volatile uint8_t *)&SPI1->DR = data;
	while(SPI1->SR & 0x00000080);
	return *(volatile uint8_t *)&SPI1->DR;
}

void SPI_SendCMD(uint8_t cmd, uint32_t arg, uint8_t crc){
	uint8_t arg1, arg2, arg3, arg4;

	arg1 = ((arg & 0xFF000000)>>24);
	arg2 = ((arg & 0x00FF0000)>>16);
	arg3 = ((arg & 0x0000FF00)>>8);
	arg4 = (arg & 0x000000FF);

	SPI_Transfer(0xFF);
	SPI_Transfer(cmd);
	SPI_Transfer(arg1);
	SPI_Transfer(arg2);
	SPI_Transfer(arg3);
	SPI_Transfer(arg4);
	SPI_Transfer(crc);
}

uint8_t WaitForR1(void){
	uint8_t R;
	R=0xFF;
	while(R==0xFF)
		R = SPI_Transfer(0xFF);
	return R;
}

void SDC_INIT(void){
	uint8_t R1, R71, R72, R73, R74, dummy;
	//char a[20];

	SPI1->CR1 |= 0x0040;
	SPI1_SS_Set;
	for(int i=0; i<10; i++){
		SPI1->DR = 0xFF;
		while(SPI1->SR & 0x00000080);
	}
	for(int i=0;i<0xFF;i++);

	R1 = R71 = R72 = R73 = R74 = dummy = 0xFF;

	SPI1_SS_Clear;
	SPI_SendCMD(0x40, 0x00000000, 0x95);    //CMD0 set SD Card to idle mode
	R1 = WaitForR1();
	int j=0;
	while((R1!=0x01)&&(j<0xFF)){
		SPI_SendCMD(0x40, 0x00000000, 0x95);    //CMD0 set SD Card to idle mode
		R1 = WaitForR1();
		j++;
	}
	j=0;

	if(R1==0x01){
		WriteText5x8(10, 10, "Card is in Idle mode", Black);
		while(R1!=0xFF)
			R1 = SPI_Transfer(0xFF);

		R1 = R71 = R72 = R73 = R74 = dummy = 0xFF;
		SPI_SendCMD(0x48, 0x000001AA, 0x87);    //CMD8 to check supply compatibility
		R1 = WaitForR1();
		R71 = SPI_Transfer(0xFF);
		R72 = SPI_Transfer(0xFF);
		R73 = SPI_Transfer(0xFF);
		R74 = SPI_Transfer(0xFF);
		dummy = SPI_Transfer(0xFF);

		if(R73==0x01 && R74==0xAA){
			WriteText5x8(10, 20, "Card is supply compatible", Black);
			R1 = 0xFF; dummy = 0x00;
			while(dummy!=0xFF)
				dummy = SPI_Transfer(0xFF);

			dummy = 0xFF;
			SPI_SendCMD(0x77, 0x00000000, 0xFF);    //CMD55 prefix command for ACMD. ACMD41=CMD55+CMD41
			dummy = WaitForR1();
			SPI_SendCMD(0x69, 0x40000000, 0xFF);    //CMD41 Command to initialize Version-2 cards
			R1 = WaitForR1();
			while((R1!=0x00)&&(j<0xFF)){
				SPI_SendCMD(0x77, 0x00000000, 0xFF);
				dummy = WaitForR1();
				SPI_SendCMD(0x69, 0x40000000, 0xFF);
				R1 = WaitForR1();
			}

			if(R1==0x00){
				WriteText5x8(10, 30, "SD Card initialized", Black);
			}else{
				WriteText5x8(10, 30, "Unknown source to initialize", Black);
			}
		}else{
			WriteText5x8(10, 20, "Card is not supply compatible", Black);
		}
	}else{
		WriteText5x8(10, 10, "No SD Card in slot", Black);
	}
	SPI1_SS_Set;
	SPI1->CR1 &= 0xFFBF;
}

void SDC_SPI_Init(void){
	//Clock Settings for SPI
	RCC->CFGR = 0x0000D40A;//94=APB2(108MHz), B4=APB2(54MHz), D4=APB2(27MHz)
	RCC->AHB1ENR |= (1U << 0);	//Enabling Port-A clock
	RCC->AHB1ENR |= (1U << 3);	//Enabling Port-D clock
	RCC->APB2ENR |= (1U << 12);	//Enabling SPI-1 clock
	//Allocate the alternate function
	GPIOA->AFR[0] = 0x55500000;

	//RCC enable and Port speed for Port-A&D are initiated in TFT.h
	GPIOA->MODER |= (0b10 <<  5*2);	//Port-A Pin- 5 SPI_SCK
	GPIOA->MODER |= (0b10 <<  6*2);	//Port-A Pin- 6 SPI_MISO
	GPIOA->MODER |= (0b10 <<  7*2);	//Port-A Pin- 7 SPI_MOSI
	GPIOD->MODER |= (0b01 << 14*2);	//Port-D Pin-14 SPI_SS

	SPI1->CR2 = 0x170C;//Interrupt required = 17E4 not required = 1704
	SPI1->CR1 = 0x033C;

	SDC_INIT();
	//Increase clock speed after initialization
	SPI1->CR1 = 0x0304;//0x407C(/256); & 0x4044(/2)
}

void Read_SDC(uint8_t *RData, uint32_t Address, uint16_t ReadSize){
	SPI1->CR1 |= 0x0040;
	SPI1_SS_Clear;

	uint8_t R1;
	R1 = 0x00;
	while(R1!=0xFF)
		R1 = SPI_Transfer(0xFF);
	R1 = 0xFF;
	SPI_SendCMD(0x51, Address, 0xFF);    //CMD0 set SD Card to idle mode
	R1 = WaitForR1();

	if(R1 == 0x00){
		R1 = 0xFF;
		R1 = WaitForR1();
		if(R1 == 0xFE){
			for(int i=0; i<ReadSize; i++){
				RData[i] = SPI_Transfer(0xFF);
				WriteText5x8(10, 20, "Reading.....", Black);
			}
			WriteText5x8(10, 20, "Reading completed", Black);
		}else{
			WriteText5x8(10, 20, "Reading failed after response", Black);
		}
	}else{
		WriteText5x8(10, 20, "Reading failed", Black);
	}

	SPI1_SS_Set;
	SPI1->CR1 &= 0xFFBF;
}
