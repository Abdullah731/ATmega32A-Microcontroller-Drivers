/*
 * ExternalInterruptsAtmega32A.c
 *
 * Created: 12/5/2019 8:53:16 PM
 *  Author: Abdullah M.Abdullah
 */ 

#include "ExternalInterrupts_ATmega32A.h"
#include "uc_Configuration.h"


/*****************************************  Defines FOR External Interrupt Handling ************************************************/


#define INT0VECTOR	_VECTOR(1)
#define INT1VECTOR	_VECTOR(2)
#define INT2VECTOR	_VECTOR(3)


void (*volatile EXTINT0_Functionp)(void)=NULL;
void (*volatile EXTINT1_Functionp)(void)=NULL;
void (*volatile EXTINT2_Functionp)(void)=NULL;

/***************************************** AVR External Interrupt ISRs ************************************************/



ISR(INT0VECTOR)
{
	if (EXTINT0_Functionp != NULL)
	{
		EXTINT0_Functionp();
	}
}





ISR(INT1VECTOR)
{
		if (EXTINT1_Functionp != NULL)
		{
			EXTINT1_Functionp();
		}	
}


ISR(INT2VECTOR)
{
	if (EXTINT2_Functionp != NULL)
	{
		EXTINT2_Functionp();
	}	
}

/***************************************** External Interrupt Functions ************************************************/


	void ExternalInterrupt_Configure(ExtInt_Number IntNumber,ExtInt_Mode Mode)
	{
		switch(IntNumber)
		{
			case EXTINT0:
			// Disable Int0
			ATMEGA32_GICR->bits.b6=0;
			// Configure Int0
			switch (Mode)
			{
				case EXTINT_LOWLVL:
				ATMEGA32A_MCUCR->bits.b0=0;
				ATMEGA32A_MCUCR->bits.b1=0;
				break;
				case EXTINT_BOTHEDGE:
				ATMEGA32A_MCUCR->bits.b0=1;
				ATMEGA32A_MCUCR->bits.b1=0;
				break;
				case EXTINT_FALLING:
				ATMEGA32A_MCUCR->bits.b0=0;
				ATMEGA32A_MCUCR->bits.b1=1;
				break;
				case EXTINT_RISING:
				ATMEGA32A_MCUCR->bits.b0=1;
				ATMEGA32A_MCUCR->bits.b1=1;
				break;
				default:
				break;
			}
			// Enable int0
			ATMEGA32_GICR->bits.b6=1;
			break;
			case EXTINT1:
			ATMEGA32_GICR->bits.b7=0;
			switch (Mode)
			{
				case EXTINT_LOWLVL:
				ATMEGA32A_MCUCR->bits.b2=0;
				ATMEGA32A_MCUCR->bits.b3=0;
				break;
				case EXTINT_BOTHEDGE:
				ATMEGA32A_MCUCR->bits.b2=1;
				ATMEGA32A_MCUCR->bits.b3=0;
				break;
				case EXTINT_FALLING:
				ATMEGA32A_MCUCR->bits.b2=0;
				ATMEGA32A_MCUCR->bits.b3=1;
				break;
				case EXTINT_RISING:
				ATMEGA32A_MCUCR->bits.b2=1;
				ATMEGA32A_MCUCR->bits.b3=1;
				break;
				default:
				break;
			}
			ATMEGA32_GICR->bits.b7=1;
			break;
			case EXTINT2:
			ATMEGA32_GICR->bits.b5=0;
			switch (Mode)
			{
				case EXTINT_FALLING:
				ATMEGA32_MCUCSR->bits.b6=0;
				break;
				case EXTINT_RISING:
				ATMEGA32_MCUCSR->bits.b6=1;
				break;
				case EXTINT_LOWLVL:
				case EXTINT_BOTHEDGE:
				default:
					EXTINT_UserWarningError();
					break;
			}
			ATMEGA32_GICR->bits.b5=1;
			break;
		}
	}
	
	void ExternalInterrupt_Disable(ExtInt_Number IntNumber)
	{
			switch(IntNumber)
			{
				case EXTINT0:
				ATMEGA32_GICR->bits.b6=0;
				break;
				case EXTINT1:
				ATMEGA32_GICR->bits.b7=0;
				break;
				case EXTINT2:
				ATMEGA32_GICR->bits.b5=0;
				break;
			}	
	}
	
	
	void EXTINT_UserWarningError(void)
	{
		
	}
