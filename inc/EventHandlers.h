/*
 * EventHandlers.h
 *
 *  Created on: 24 Nov 2020
 *      Author: S.Seshadri
 */

#ifndef EVENTHANDLERS_H_
#define EVENTHANDLERS_H_

#include"Custom_Lib.h"

#ifdef __cplusplus
 extern "C" {
#endif

uint8_t ClickEvent;
uint16_t RaiseCount;
uint16_t FallCount;

struct{
	uint16_t tpmsec;
	uint16_t tpsec;
	uint16_t tpmin;
	uint16_t tphr;
}ClickTimeStamp;

void InitEvtHandler();
void EXTI15_10_IRQHandler(void);
void RecordTimeStamp(void);
void SingleClick(void);
void DoubleClick(void);

#ifdef __cplusplus
}
#endif

#endif /* EVENTHANDLERS_H_ */
