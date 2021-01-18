/*
 * ATMEGA32_ADC.c
 *
 * Created: 2/29/2020 11:43:52 AM
 *  Author: Abdullah M.Abdullah
 */ 


#include "ATMEGA32_ADC.h"
#include "StdTypes.h"
#include "uc_Configuration.h"

void (*ADC_CallBack) (uint16) = NULL;
	
ISR(ADC_VECT)
{
	if (ADC_CallBack != NULL)
	{
		ADC_CallBack(ADC_DATA);
	}
}

void ADC_Init(ADC_RefrenceSelect Refrence,ADC_ConvMode Conv,ADC_PreScalerSelect F_ADC,ADC_Interrupt   InterruptMode)
{
	ADMUX->allRegister = Refrence  ;
	ADCSRA->allRegister= F_ADC | ADC_ENABLE | InterruptMode  | (Conv & 0x00FF) ;
	SFIOR->allRegister&= 0x1F;
	SFIOR->allRegister |= (Conv>>8) & 0xE0;
}
	
uint16 ADC_Read_Polling(ADC_Channel Channel,ADC_Resloution Resloution)
{
	uint16 Result =0;
	switch (Resloution)
	{
		case ADC_10BITS:
		// Right Adjust Result
		ADCSRA->bits.b5=0;
		break;
		case ADC_8BIT:
		// left Adjust result to Read Only 8 bits
		ADCSRA->bits.b5=1;
		break;
		default:
		break;
	}
	// Clear Prev Channel Selection & Select New Channel
	ADMUX->allRegister &= 0xE0;
	ADMUX->allRegister |= Channel;
	// Start Conversion
	ADCSRA->bits.b6 =1;
	// Wait till Conv End
	while(ADCSRA->bits.b4 == 0){}
	// Conv Ended we Must Clear Interrupt Flag
	// ADIF is Cleared By Writing 1 to it.
	ADCSRA->bits.b4=1;
		
	switch (Resloution)
	{
		case ADC_10BITS:
			Result = ADC_DATA;
		break;
		case ADC_8BIT:
			Result = ADCH->allRegister;
		break;
		default:
		break;
	}
	return Result;
}
	
void ADC_Read_Interrupt(ADC_Channel Channel,ADC_Resloution Resloution)
{
	switch (Resloution)
	{
		case ADC_10BITS:
		// Right Adjust Result
		ADCSRA->bits.b5=0;
		break;
		case ADC_8BIT:
		// left Adjust result to Read Only 8 bits
		ADCSRA->bits.b5=1;
		break;
		default:
		break;
	}
	// Clear Prev Channel Selection & Select New Channel
	ADMUX->allRegister &= 0xE0;
	ADMUX->allRegister |= Channel;
	// Start Conversion
	ADCSRA->bits.b6 = 1;
}
	
void ADC_Disable(void)
{
	ADCSRA->bits.b7=0;
}

	