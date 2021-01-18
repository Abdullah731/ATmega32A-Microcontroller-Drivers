/*
 * DIO_ATmega32A.c
 *
 * Created: 11/7/2019 6:02:37 PM
 *  Author: Abdullah M.Abdullah
 */

	#include "DIO_ATmega32A.h"

	typedef enum
	{
		DIOERROR_InvalidPinNumber,
		DIOERROR_InvalidPortPassed,
		DIOERROR_InvalidPinLevel,
		DIOERROR_InvalidPinMode,
	}DIO_ErrorState;


static void DIO_UserWarningError(DIO_ErrorState ErrorState);


static void DIO_UserWarningError(DIO_ErrorState ErrorState)
{
	switch(ErrorState)
	{
		case DIOERROR_InvalidPinNumber:
		ERRORMSG("InvalidPinNumber Passed to A DIO Module Function \n");
		break;
		case DIOERROR_InvalidPortPassed:
		ERRORMSG("InvalidPortPassed Passed to A DIO Module Function \n");
		break;
		case DIOERROR_InvalidPinLevel:
		ERRORMSG("Invalid Pin Level Passed to A DIO Module Function \n");
		break;
		case DIOERROR_InvalidPinMode:
		ERRORMSG("Invalid Pin Mode Passed to A DIO Module Function \n");
		break;
	}

	while(1)
	{
		/* Code Will Be Stuck Here Or you Should Call a Handling API */
	}
}

void	DIO_pinConfigure(
							DIO_Struct * Dio,
							pinNumber pinNum,
							pinMode Mode)
	{

		if (pinNum > 7)
		{
			DIO_UserWarningError(DIOERROR_InvalidPinNumber);
		}

		switch(Mode)
		{

				 case INPUT_FLOAT:
					 CLEARBIT(Dio->ddr.allRegister,pinNum);
					 CLEARBIT(Dio->port.allRegister,pinNum);
				 break;
				 case INPUT_PULLUP:
					 CLEARBIT(Dio->ddr.allRegister,pinNum);
					 SETBIT(Dio->port.allRegister,pinNum);
				 break;
				 case OUTPUT:
					 SETBIT(Dio->ddr.allRegister,pinNum);
					 CLEARBIT(Dio->port.allRegister,pinNum);
				 break;
				 default:
					DIO_UserWarningError(DIOERROR_InvalidPinMode);
				 break;
		}
}

void	DIO_pinWrite(
						DIO_Struct * Dio,
						pinNumber pinNum,
						digitalState State)
{
	if (pinNum > 7)
	{
		DIO_UserWarningError(DIOERROR_InvalidPinNumber);
	}
	else
	{

		switch(State)
		{
			case HIGH:
			SETBIT(Dio->port.allRegister,pinNum);
			break;
			case LOW:
			CLEARBIT(Dio->port.allRegister,pinNum);
			break;
			default:
			DIO_UserWarningError(DIOERROR_InvalidPinLevel);
			break;
		}
	}
}


digitalState DIO_pinRead(
							DIO_Struct * Dio,
							pinNumber pinNum)
{
	digitalState returnvar = 0;
	if (pinNum > 7)
	{
		DIO_UserWarningError(DIOERROR_InvalidPinNumber);
	}
	else
	{
		switch(READBIT(Dio->pin.allRegister,pinNum))
		{
			case LOW:
			returnvar = LOW;
			break;
			case HIGH:
			returnvar = HIGH;
			break;
			default:
			break;
		}
	}
	return returnvar;
}


void	DIO_portConfigure(DIO_Struct * Dio,vuint8_t ConfigByte)
{
		Dio->ddr.allRegister=ConfigByte;
}

void	DIO_portWrite(
						DIO_Struct * Dio,
						vuint8_t Data)
{
	Dio->port.allRegister=Data;
}

vuint8_t DIO_portRead(DIO_Struct * Dio)
{
		return  Dio->pin.allRegister;
}



