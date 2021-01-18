/*
 * Push.h
 *
 * Created: 11/28/2019 6:34:30 PM
 *  Author: Abdullah M.Abdullah
 */ 


#ifndef PUSH_H_
#define PUSH_H_

#include "../../1.0 MCAL/Header Files/DIO_ATmega32A.h"
#include <util/delay.h>

typedef enum
{
	SW_NOTPRESSED,
	SW_PRESSEDHIGH,
	SW_PRESSEDLOW
}ButtonSw_state;

typedef struct 
{
   DIO_Struct *	 Button_Dio;
   pinNumber Button_Pin;
   pinMode	 InputMode;
   digitalState PrevButton_State;
}ButtonSw_datatype;


void ButtonSw_Setup(ButtonSw_datatype * Button);
ButtonSw_state ButtonSw_Read(ButtonSw_datatype * Button);
void Button_UserWarningError(void);
#endif /* PUSH_H_ */
