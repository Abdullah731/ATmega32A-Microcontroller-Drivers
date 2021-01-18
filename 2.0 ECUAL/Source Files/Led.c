/*
 * Led.c
 *
 * Created: 11/21/2019 7:14:51 PM
 *  Author: Hamdy
 */ 

	#include "../../2.0 ECUAL/Header Files/LED.h"
	
	void LEDSetup(ledDatatype led)
	{
		DIO_pinConfigure(led.LED_Dio,led.LED_pin,OUTPUT);
	}
	
	void LEDControl(ledDatatype led, LEDstate state)
	{
		switch(state)
		{
			// LED_OFF is the same as LED_ON_REVERSED
			case LED_OFF:
			DIO_pinWrite(led.LED_Dio,led.LED_pin,LOW);
			break;
			case LED_ON:
			DIO_pinWrite(led.LED_Dio,led.LED_pin,HIGH);
			break;
			case LED_TOGGLE:
			DIO_pinWrite(led.LED_Dio,led.LED_pin,!DIO_pinRead(led.LED_Dio,led.LED_pin));
			break;
			default:
			LED_UserWarningError();
			break;
		}	
	}



void LED_UserWarningError(void)
{
				
}	
