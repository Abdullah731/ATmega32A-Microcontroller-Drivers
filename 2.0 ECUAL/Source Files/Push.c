/*
 * Push.c
 *
 * Created: 11/28/2019 6:34:37 PM
 *  Author: Hamdy
 */ 

#include "Push.h"

#define BUTTON_BOUNCE_PERIOD_mS	(60)

void ButtonSw_Setup(ButtonSw_datatype * Button)
{
	switch(Button->InputMode)
	{
		case INPUT_FLOAT:
		DIO_pinConfigure(Button->Button_Dio,Button->Button_Pin,INPUT_FLOAT);
		break;
		case INPUT_PULLUP:
		DIO_pinConfigure(Button->Button_Dio,Button->Button_Pin,INPUT_PULLUP);
		break;
		default:
		Button_UserWarningError();
		break;
	}
	Button->PrevButton_State = DIO_pinRead(Button->Button_Dio,Button->Button_Pin);
}

ButtonSw_state ButtonSw_Read(ButtonSw_datatype * Button)
{
	ButtonSw_state returnvar = SW_NOTPRESSED;
	 
	if (DIO_pinRead(Button->Button_Dio,Button->Button_Pin) != Button->PrevButton_State)
	{
		_delay_ms(BUTTON_BOUNCE_PERIOD_mS);
		if (DIO_pinRead(Button->Button_Dio,Button->Button_Pin) != Button->PrevButton_State)
		{
			Button->PrevButton_State = DIO_pinRead(Button->Button_Dio,Button->Button_Pin);
			switch (Button->PrevButton_State)
			{
				case LOW:
						returnvar = SW_PRESSEDLOW;
				break;
				case HIGH:
						returnvar = SW_PRESSEDHIGH;
				break;
				default:
				break;
			}
		}
	}
	return returnvar;
}


void Button_UserWarningError(void)
{
	
}
