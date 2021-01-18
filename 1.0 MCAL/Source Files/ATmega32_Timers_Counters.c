#include "uc_Configuration.h"
#include "ATmega32_Timers_Counters.h"
#include "StdTypes.h"
#include "Macros.h"


void (* Timer0_OVF_CallBack) (void) = NULL;
void (* Timer0_COMP_CallBack) (void) = NULL;

ISR(TIMER0_OVF_VECT)
{
	if(Timer0_OVF_CallBack != NULL)
	{
		Timer0_OVF_CallBack();
	}
}

ISR(TIMER0_COMP_VECT)
{
	if(Timer0_COMP_CallBack != NULL)
	{
		Timer0_COMP_CallBack();
	}
}


void Timer0_Init(Timer0_Frequency Tfrequency, Timer0_Modes Tmode, Timer0_OC0ControlMode TOc0Mode, Timer0_Interrupt Tinterrupt)
{
	TCNT0->allRegister = 0x00;
	TCCR0->allRegister = Tfrequency | Tmode | TOc0Mode;
	TIMSK->allRegister &=0xFC;
	TIMSK->allRegister |= Tinterrupt;
}

void Timer0_SetCompareValue(uint8 Compare_value)
{
	OCR0->allRegister = Compare_value;
}


void Timer0_CTC_SquareGenerate(float32 SignalFreq, float32 Timer0_Freq)
{
	OCR0->allRegister =	(uint8)	((Timer0_Freq/(2.0*SignalFreq)) - 0.5);
}


void Timer0_PWMSetDutyCycle(float DutyCycle,Timer0_OC0ControlMode InvertionState)
{
	switch (InvertionState)
	{
		case Timer0_PWM_NonInvert:
		OCR0->allRegister = ((DutyCycle/100.0) * 255)+0.5;
		break;
		case Timer0_PWM_Invert:
		OCR0->allRegister = (((100-DutyCycle)/100.0) * 255)+0.5;
		break;
		default:
		break;
	}
}
