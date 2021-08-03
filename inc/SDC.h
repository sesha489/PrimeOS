#ifndef SDC_H_
#define SDC_H_

#include"TFT.h"

#define SPI1_SS_Set   (GPIOD->ODR |=  (1U << 14)) //SPI1_SS Set
#define SPI1_SS_Clear (GPIOD->ODR &= ~(1U << 14)) //SPI1_SS Clear

#ifdef __cplusplus
 extern "C" {
#endif

uint8_t SDC_Transfer(uint8_t data);
void SDC_SendCMD(uint8_t cmd, uint32_t arg, uint8_t crc);
uint8_t WaitForR1(void);
void SDC_SPI_Init(void);
void SDC_INIT(void);
void Read_SDC(uint8_t *RData, uint32_t Address, uint16_t ReadSize);

#ifdef __cplusplus
}
#endif

#endif /* SDC_H_ */
