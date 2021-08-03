/*
 * TFT.c
 *
 *  Created on: 20 Dec 2018
 *      Author: Administrator
 */

#include"TFT.h"

void Assign_PinData(uint16_t Data){

	GPIOD->BSRR = 0x80000000;
	GPIOE->BSRR = 0x2A000000;
	GPIOF->BSRR = 0xF0000000;

	GPIOF->BSRR = ((Data & (1U<<0))<<12) | ((Data & (1U<<2))<<13) | ((Data & (1U<<4))<<10) | ((Data & (1U<<7))<<6);
	GPIOD->BSRR = ((Data & (1U<<1))<<14);
	GPIOE->BSRR = ((Data & (1U<<3))<<10) | ((Data & (1U<<5))<<6) | ((Data & (1U<<6))<<3);

}

void Send_CMD(uint16_t Data){
	//CS_Clear;
	RS_Clear;

	WR_Clear;
	Assign_PinData((Data & 0x0000));
	WR_Set;

	WR_Clear;
	Assign_PinData((Data & 0x00FF));
	WR_Set;

	//CS_Set;

}

void Send_Data(uint16_t Data){
	//CS_Clear;
	RS_Set;

	WR_Clear;
	Assign_PinData((Data & 0xFF00)>>8);
	WR_Set;

	WR_Clear;
	Assign_PinData((Data & 0x00FF));
	WR_Set;

	//CS_Set;

}

/*void Send_Colour24(unsigned int Data){        //Can be used only when R03H configured to 0x0000D030
	//unsigned int compac;
	//compac = 0;
	//CS_Clear;
	RS_Set;

	WR_Clear;
	//compac = ((Data & 0x0003F000)>>12);
	//Assign_PinData(compac<<2);
	Assign_PinData((Data & 0x0003F000)>>10);
	WR_Set;

	WR_Clear;
	//compac = ((Data & 0x00000FC0)>>6);
	//Assign_PinData(compac<<2);
	Assign_PinData((Data & 0x00000FC0)>>4);
	WR_Set;

	WR_Clear;
	//compac = ((Data & 0x0000003F));
	//Assign_PinData(compac<<2);
	Assign_PinData(Data & 0x0000003F);
	WR_Set;

	//CS_Set;

}*/

void Init_Pins(void){

	//Enable clock for ports going to be used
	RCC->AHB1ENR |= (1U << 0);	//Enabling Port-A clock
	RCC->AHB1ENR |= (1U << 2);	//Enabling Port-C clock
	RCC->AHB1ENR |= (1U << 3);	//Enabling Port-D clock
	RCC->AHB1ENR |= (1U << 4);	//Enabling Port-E clock
	RCC->AHB1ENR |= (1U << 5);	//Enabling Port-F clock

	//Configure required pins as outputs. LCD control pins
	GPIOA->MODER |= (0b01 << 3*2);	//Port-A Pin-3 to Output (LCD_RD)
	GPIOC->MODER |= (0b01 << 0*2);	//Port-C Pin-0 to Output (LCD_WR)
	GPIOC->MODER |= (0b01 << 3*2);	//Port-C Pin-3 to Output (LCD_RS)
	GPIOF->MODER |= (0b01 << 3*2);	//Port-F Pin-3 to Output (LCD_CS)
	GPIOF->MODER |= (0b01 << 5*2);	//Port-F Pin-5 to Output (LCD_RST)

	//LCD Data pins
	GPIOF->MODER |= (0b01 << 12*2);	//Port-F Pin-12 to Output (D0)
	GPIOD->MODER |= (0b01 << 15*2);	//Port-D Pin-15 to Output (D1)
	GPIOF->MODER |= (0b01 << 15*2);	//Port-F Pin-15 to Output (D2)
	GPIOE->MODER |= (0b01 << 13*2);	//Port-E Pin-13 to Output (D3)
	GPIOF->MODER |= (0b01 << 14*2);	//Port-F Pin-14 to Output (D4)
	GPIOE->MODER |= (0b01 << 11*2);	//Port-E Pin-11 to Output (D5)
	GPIOE->MODER |= (0b01 << 9*2 );	//Port-E Pin-9  to Output (D6)
	GPIOF->MODER |= (0b01 << 13*2);	//Port-F Pin-13 to Output (D7)

	//Set Speed
	GPIOA->OSPEEDR = 0xFFFFFFFF;	//Port-A
	GPIOC->OSPEEDR = 0xFFFFFFFF;	//Port-C
	GPIOF->OSPEEDR = 0xFFFFFFFF;	//Port-F
	GPIOD->OSPEEDR = 0xFFFFFFFF;	//Port-D
	GPIOE->OSPEEDR = 0xFFFFFFFF;	//Port-E

	//Set control pins and data pins to default
	D0_Clear;
	D1_Clear;
	D2_Clear;
	D3_Clear;
	D4_Clear;
	D5_Clear;
	D6_Clear;
	D7_Clear;

	WR_Set;    //Write performed when WR=0
	RS_Set;    //RS=0 (Index), RS=1 (Control)
	RD_Set;    //Read performed when RD=0
	CS_Set;    //Display accessible on CS=0
	RST_Set;   //Reset is active low so set high

	CS_Clear;

}

void Exit_Standby(void){
	Send_CMD(0x0010);
	Send_Data(0x14E0);
	Send_CMD(0x0007);
	Send_Data(0x0133);
}

void Paint_Colour(uint16_t Colour){

	unsigned int i;
	i = 76800;
	Send_CMD(0x0020);
	Send_Data(0x0000);
	Send_CMD(0x0021);
	Send_Data(0x0000);
	Send_CMD(0x0022);
	/*for(i=76800; i>0; i--){
		Send_Data(Colour);
	}*/
	while(i!=0){
		Send_Data(Colour);
		Send_Data(Colour);
		Send_Data(Colour);
		Send_Data(Colour);
		Send_Data(Colour);
		Send_Data(Colour);
		Send_Data(Colour);
		Send_Data(Colour);
		Send_Data(Colour);
		Send_Data(Colour);
		Send_Data(Colour);
		Send_Data(Colour);
		Send_Data(Colour);
		Send_Data(Colour);
		Send_Data(Colour);
		Send_Data(Colour);
		i = i-16;
	}
}

void Init_Display(void){

	Send_CMD(0x0001);
	Send_Data(0x0100);
	_msDelay(20);
	Send_CMD(0x0002);
	Send_Data(0x0700);
	_msDelay(20);
	Send_CMD(0x0003);
	Send_Data(0x1030);//0xD030
	_msDelay(20);
	Send_CMD(0x0004);
	Send_Data(0x0000);
	_msDelay(20);
	Send_CMD(0x0008);
	Send_Data(0x0302);
	_msDelay(20);
	Send_CMD(0x000A);
	Send_Data(0x0000);
	_msDelay(20);
	Send_CMD(0x000C);
	Send_Data(0x0000);
	_msDelay(20);
	Send_CMD(0x000D);
	Send_Data(0x0000);
	_msDelay(20);
	Send_CMD(0x000F);
	Send_Data(0x0000);
	_msDelay(20);
	Send_CMD(0x0030);
	Send_Data(0x0000);
	_msDelay(20);
	Send_CMD(0x0031);
	Send_Data(0x0405);
	_msDelay(20);
	Send_CMD(0x0032);
	Send_Data(0x0203);
	_msDelay(20);
	Send_CMD(0x0035);
	Send_Data(0x0004);
	_msDelay(20);
	Send_CMD(0x0036);
	Send_Data(0x0B07);
	_msDelay(20);
	Send_CMD(0x0037);
	Send_Data(0x0000);
	_msDelay(20);
	Send_CMD(0x0038);
	Send_Data(0x0405);
	_msDelay(20);
	Send_CMD(0x0039);
	Send_Data(0x0203);
	_msDelay(20);
	Send_CMD(0x003C);
	Send_Data(0x0004);
	_msDelay(20);
	Send_CMD(0x003D);
	Send_Data(0x0B07);
	_msDelay(20);
	Send_CMD(0x0020);
	Send_Data(0x0000);
	_msDelay(20);
	Send_CMD(0x0021);
	Send_Data(0x0000);
	_msDelay(20);
	Send_CMD(0x0050);
	Send_Data(0x0000);
	_msDelay(20);
	Send_CMD(0x0051);
	Send_Data(0x00EF);
	_msDelay(20);
	Send_CMD(0x0052);
	Send_Data(0x0000);
	_msDelay(20);
	Send_CMD(0x0053);
	Send_Data(0x013F);
	_msDelay(20);
	Send_CMD(0x0060);
	Send_Data(0xA700);
	_msDelay(20);
	Send_CMD(0x0061);
	Send_Data(0x0001);
	_msDelay(20);
	Send_CMD(0x0090);
	Send_Data(0x003A);
	_msDelay(20);
	Send_CMD(0x0095);
	Send_Data(0x021E);
	_msDelay(20);
	Send_CMD(0x0080);
	Send_Data(0x0000);
	_msDelay(20);
	Send_CMD(0x0081);
	Send_Data(0x0000);
	_msDelay(20);
	Send_CMD(0x0082);
	Send_Data(0x0000);
	_msDelay(20);
	Send_CMD(0x0083);
	Send_Data(0x0000);
	_msDelay(20);
	Send_CMD(0x0084);
	Send_Data(0x0000);
	_msDelay(20);
	Send_CMD(0x0085);
	Send_Data(0x0000);
	_msDelay(20);
	Send_CMD(0x00FF);
	Send_Data(0x0001);
	_msDelay(20);
	Send_CMD(0x00B0);
	Send_Data(0x140D);
	_msDelay(20);
	Send_CMD(0x00FF);
	Send_Data(0x0000);
	_msDelay(20);
	Send_CMD(0x0007);
	Send_Data(0x0133);
	_msDelay(20);
	Exit_Standby();
	_msDelay(20);
	Send_CMD(0x0022);
	_msDelay(20);
	Paint_Colour(Black);
	_msDelay(20);
}

void Init_TFT(void){
	Init_Pins();
	_msDelay(20);
	Init_Display();
}

void DrawPoint(uint16_t x, uint16_t y, uint16_t colour)
{
	Send_CMD(0x0020);
	Send_Data(y);
	Send_CMD(0x0021);
	Send_Data(x);
	Send_CMD(0x0022);
	Send_Data(colour);
}

unsigned char SelectBit(unsigned int num)
{
    switch(num)
    {
    case 0:
      return(0x01);
    case 1:
      return(0x02);
    case 2:
      return(0x04);
    case 3:
      return(0x08);
    case 4:
      return(0x10);
    case 5:
      return(0x20);
    case 6:
      return(0x40);
    case 7:
      return(0x80);
    }
	return(0x00);
}

void WriteText5x8(uint16_t x, uint16_t y, const char *textptr, uint16_t colour)
{
	y = 239-y;
	unsigned char pixdata[5], s;
	for(unsigned int i=0; textptr[i]!='\0'; i++)
	{
		if(textptr[i]<='~')
			memcpy(pixdata,TEXT5x8[textptr[i]-' '],5);
		else
			memcpy(pixdata,TEXT5x8[0],5);
		for(unsigned int j=0; j<5; j++, x++)
		{
			for(unsigned int k=0; k<8; k++)
			{
				s = SelectBit(k);
				if(s&pixdata[j])
				{
					DrawPoint(x, (y-k), colour);
				}else{
					DrawPoint(x, (y-k), White);
				}
			}
		}
		x += 1;
	}
}
