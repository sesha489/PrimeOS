/*
 * Custom_Lib.h
 *
 *  Created on: 24 Nov 2020
 *      Author: Seshadri
 */

#ifndef CUSTOM_LIB_H_
#define CUSTOM_LIB_H_

#include"stm32f767xx.h"
#include<string.h>
#include<stdio.h>
//#include<iostream>

#ifdef __cplusplus
 extern "C" {
#endif

//volatile uint32_t MHz;
volatile uint16_t mSec;
volatile uint16_t sec;
volatile uint16_t min;
volatile uint16_t hour;
volatile uint16_t delayCounts;

void _msDelay(uint16_t delaymSec);
void SysTick_Handler(void);
void ClockConfigEx(void);

#ifdef __cplusplus
}
#endif

#endif /* CUSTOM_LIB_H_ */
