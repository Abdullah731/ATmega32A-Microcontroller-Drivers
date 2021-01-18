/*
 * ATmega32_Timers_Counters.h
 *
 * Created: 7/2/2020 5:32:56 AM
 *  Author: Abdullah
 */ 


#ifndef ATMEGA32_TIMERS_COUNTERS_H_
#define ATMEGA32_TIMERS_COUNTERS_H_

#include "uc_Configuration.h"
#include "StdTypes.h"

typedef enum
{
	Timer0_NormalMode = 0x00,
	Timer0_CTCMode = 0x08,
	Timer0_PWMPhaseCorrect = 0x40,
	Timer0_FastPWN = 0x48,
}Timer0_Modes;


typedef enum
{
	Timer0_OC0Disconnect=0x00,
	Timer0_NonPWM_ToggleOC0=0x10,
	Timer0_NonPWM_ClearOC0=0x20,
	Timer0_NonPWM_SetOC0=0x30,
	Timer0_PWM_NonInvert=0x20,
	Timer0_PWM_Invert=0x30,
}Timer0_OC0ControlMode;

typedef enum
{
	Timer0_Disabled,	
	Timer0_CPUfreq,
	Timer0_CPUfreqBy8,
	Timer0_CPUfreqBy64,
	Timer0_CPUfreqBy256,
	Timer0_CPUfreqBy1024,
	Counter0_FallingEdge,
	Counter0_RisingEdge,
}Timer0_Frequency;

typedef enum
{
	Timer0_InterruptDisable,
	Timer0_OVF_InterruptEnable,
	Timer0_COMP_InterruptEnable,
	Timer0_OVF_COMP_InterruptEnable,
}Timer0_Interrupt;

extern void (* Timer0_OVF_CallBack) (void);
extern void (* Timer0_COMP_CallBack) (void);

void Timer0_Init(
				Timer0_Frequency		Tfrequency,
				Timer0_Modes			Tmode,
				Timer0_OC0ControlMode	TOc0Mode,
				Timer0_Interrupt		Tinterrupt
				);
				
void Timer0_SetCompareValue(uint8 Compare_value);

void Timer0_CTC_SquareGenerate(float32 SignalFreq, float32 Timer0_Freq);

void Timer0_PWMSetDutyCycle(float DutyCycle,Timer0_OC0ControlMode InvertionState);

#endif /* ATMEGA32_TIMERS_COUNTERS_H_ */