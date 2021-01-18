/*
 * multiplexing_leds.h
 *
 *  Created on: Jan 1, 2020
 *      Author: Abdullah M.Abdullah
 */

#ifndef _LOWER_APPLICATION_HEADER_FILES_MULTIPLEXING_LEDS_H_
#define _LOWER_APPLICATION_HEADER_FILES_MULTIPLEXING_LEDS_H_

#include "../../1.0 MCAL/Header Files/DIO_ATmega32A.h"

	typedef enum
	{
		ALLOFF,
		LED1_ON,
		LED2_ON,
		LED3_ON,
		LED4_ON,
		LED5_ON,
		LED6_ON,
	}LedMultiplexState;

	typedef struct
	{
		DIO_Struct * CurrentPort;
		pinNumber    PinNum1;
		pinNumber    PinNum2;
		pinNumber    PinNum3;

		LedMultiplexState	State;
	}LEDMultiPlex_ControlBlock;


	void MultiplexingLeds_Init(LEDMultiPlex_ControlBlock * Block);

	void MultiplexingLeds_Control(LEDMultiPlex_ControlBlock * Block);

#endif /* 4_0_LOWER_APPLICATION_HEADER_FILES_MULTIPLEXING_LEDS_H_ */
