/*
 * multiplexing_leds.c
 *
 *  Created on: Jan 1, 2020
 *      Author: Hamdy
 */

#include "../../2.0 ECUAL/Header Files/multiplexing_leds.h"


	void MultiplexingLeds_Init(LEDMultiPlex_ControlBlock * Block)
	{
		 DIO_pinConfigure(Block->CurrentPort,Block->PinNum1,OUTPUT);
		 DIO_pinConfigure(Block->CurrentPort,Block->PinNum2,OUTPUT);
		 DIO_pinConfigure(Block->CurrentPort,Block->PinNum3,OUTPUT);
	}

	void MultiplexingLeds_Control(LEDMultiPlex_ControlBlock * Block)
	{
				MultiplexingLeds_Init(Block);
				switch	(Block->State)
				{
						case ALLOFF:
						DIO_pinWrite(Block->CurrentPort,Block->PinNum1,LOW);
						DIO_pinWrite(Block->CurrentPort,Block->PinNum2,LOW);
						DIO_pinWrite(Block->CurrentPort,Block->PinNum3,LOW);
						break;
						case LED1_ON:
						DIO_pinWrite(Block->CurrentPort,Block->PinNum1,HIGH);
						DIO_pinWrite(Block->CurrentPort,Block->PinNum2,LOW);
						DIO_pinConfigure(Block->CurrentPort,Block->PinNum3,INPUT_FLOAT);
						break;
						case LED2_ON:
						DIO_pinWrite(Block->CurrentPort,Block->PinNum2,HIGH);
						DIO_pinWrite(Block->CurrentPort,Block->PinNum1,LOW);
						DIO_pinConfigure(Block->CurrentPort,Block->PinNum3,INPUT_FLOAT);
						break;
						case LED3_ON:
						DIO_pinWrite(Block->CurrentPort,Block->PinNum2,HIGH);
						DIO_pinWrite(Block->CurrentPort,Block->PinNum3,LOW);
						DIO_pinConfigure(Block->CurrentPort,Block->PinNum1,INPUT_FLOAT);
						break;
						case LED4_ON:
						DIO_pinWrite(Block->CurrentPort,Block->PinNum3,HIGH);
						DIO_pinWrite(Block->CurrentPort,Block->PinNum2,LOW);
						DIO_pinConfigure(Block->CurrentPort,Block->PinNum1,INPUT_FLOAT);
						break;
						case LED5_ON:
						DIO_pinWrite(Block->CurrentPort,Block->PinNum1,HIGH);
						DIO_pinWrite(Block->CurrentPort,Block->PinNum3,LOW);
						DIO_pinConfigure(Block->CurrentPort,Block->PinNum2,INPUT_FLOAT);
						break;
						case LED6_ON:
						DIO_pinWrite(Block->CurrentPort,Block->PinNum1,LOW);
						DIO_pinWrite(Block->CurrentPort,Block->PinNum3,HIGH);
						DIO_pinConfigure(Block->CurrentPort,Block->PinNum2,INPUT_FLOAT);
						break;
				}
	}
