/*
 * TFT.h
 *
 *  Created on: 20 Dec 2018
 *      Author: Administrator
 */

#ifndef TFT_H_
#define TFT_H_

#include"Font.h"

#define Black   0x0000    //      0,   0,   0
#define White   0xFFFF    //    255, 255, 255
#define Red     0xF800    //    255,   0,   0
#define Blue    0x001F    //      0,   0, 255
#define Green   0x07E0    //      0, 255,   0
#define Cyan    0x07FF    //      0, 255, 255
#define Yellow  0xFFE0    //    255, 255,   0
#define Magenta 0xF81F    //    255,   0, 255
#define Grey    0x7BEF    //    128, 128, 128

#define RD_Set   (GPIOA->ODR |=  (1U << 3))
#define RD_Clear (GPIOA->ODR &= ~(1U << 3))

#define WR_Set   (GPIOC->ODR |=  (1U << 0))
#define WR_Clear (GPIOC->ODR &= ~(1U << 0))

#define RS_Set   (GPIOC->ODR |=  (1U << 3))
#define RS_Clear (GPIOC->ODR &= ~(1U << 3))

#define CS_Set   (GPIOF->ODR |=  (1U << 3))
#define CS_Clear (GPIOF->ODR &= ~(1U << 3))

#define RST_Set   (GPIOF->ODR |=  (1U << 5))
#define RST_Clear (GPIOF->ODR &= ~(1U << 5))

#define D0_Set   (GPIOF->ODR |=  (1U << 12))
#define D0_Clear (GPIOF->ODR &= ~(1U << 12))
#define D1_Set   (GPIOD->ODR |=  (1U << 15))
#define D1_Clear (GPIOD->ODR &= ~(1U << 15))
#define D2_Set   (GPIOF->ODR |=  (1U << 15))
#define D2_Clear (GPIOF->ODR &= ~(1U << 15))
#define D3_Set   (GPIOE->ODR |=  (1U << 13))
#define D3_Clear (GPIOE->ODR &= ~(1U << 13))
#define D4_Set   (GPIOF->ODR |=  (1U << 14))
#define D4_Clear (GPIOF->ODR &= ~(1U << 14))
#define D5_Set   (GPIOE->ODR |=  (1U << 11))
#define D5_Clear (GPIOE->ODR &= ~(1U << 11))
#define D6_Set   (GPIOE->ODR |=  (1U << 9))
#define D6_Clear (GPIOE->ODR &= ~(1U << 9))
#define D7_Set   (GPIOF->ODR |=  (1U << 13))
#define D7_Clear (GPIOF->ODR &= ~(1U << 13))

#ifdef __cplusplus
 extern "C" {
#endif

void Init_Pins(void);
void Init_Display(void);
void Assign_PinData(uint16_t Data);
void Send_CMD(uint16_t Data);
void Send_Data(uint16_t Data);
//void Send_Colour24(unsigned int Data);    //Can be used only when R03H configured to 0x0000D030
void Exit_Standby(void);
void Paint_Colour(uint16_t Colour);
void DrawPoint(uint16_t x, uint16_t y, uint16_t colour);
void WriteText5x8(uint16_t x, uint16_t y, const char *textptr, uint16_t colour);
unsigned char SelectBit(unsigned int num);
void Init_TFT(void);

#ifdef __cplusplus
}
#endif

#endif /* TFT_H_ */
