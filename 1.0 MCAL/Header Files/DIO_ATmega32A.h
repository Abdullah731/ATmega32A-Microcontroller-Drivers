/**
 * @file  < Digital Input output Related API      >
 * @brief < Contains API to Handle DIO of AVR MCU >
 *
 *		DIO_pinConfigure  
				< Function >   Use This Function To Configure Direction of a DIO pin
 *						  return		 void
 *						  Parameters  
 *										 1- DIO Port			< DIOA , DIOB .. etc>
 *										 2- DIO Pin Number		<0 .. 7>
 *										 3- DIO Pin Mode		< OUTPUT , INPUT_PULLUP , INPUT_FLOAT >
 *
 *		 DIO_pinWrite     
				< Function >   Use This Function To Write Output pins Level 
 *						  return		 void
 *						  Parameters
 *										 1- DIO Port			 < DIOA , DIOB .. etc>
 *										 2- DIO Pin Number	 <0 .. 7>
 *										 3- DIO Pin State	 < LOW , HIGH >
 *
 *
 *		 DIO_pinRead     
				< Function >   Use This Function To Read Input pins Level
 *					     return         Pin Read <Low , HIGH>
 *					     Parameters
 *										1- DIO Port			 < DIOA , DIOB .. etc>
 *										2- DIO Pin Number	 <0 .. 7>
 *									
 *
 *		 DIO_UserWarningError     
				< Function >   This Function Will Be Called When an Invalid Parameter is Passed to Any DIO Function
 *					     return         Void "Never Returns"
 *					     Parameters
 *										1- Error State
 *										
 *
 * @author <	Abdullah M.Abdullah	>
 * @date <1/2017>
 *
 */

#ifndef DIO_ATMEGA32A_H_
#define DIO_ATMEGA32A_H_

	#include "uc_Configuration.h"
	#include "Macros.h"
	#include "StdTypes.h"
	


/******************************************* User Types For AVR Input/Output MCU **************************************/
	
	typedef enum
	{
		INPUT_FLOAT,
		INPUT_PULLUP,
		OUTPUT,
	}pinMode;
	

/******************************************* IO Functions Prototype ***************************************************/

void	DIO_pinConfigure(
						  DIO_Struct * Dio,
						  pinNumber pinNum,
						  pinMode Mode);
	
void	DIO_pinWrite(
						DIO_Struct * Dio,
						pinNumber pinNum,
						digitalState State);
						
digitalState DIO_pinRead(
						  DIO_Struct * Dio,
						  pinNumber pinNum);

void	DIO_portConfigure(
						  DIO_Struct * Dio,
						  vuint8_t ConfigByte);

void	DIO_portWrite(
						DIO_Struct * Dio,
						vuint8_t Data);

vuint8_t DIO_portRead(DIO_Struct * Dio);



#endif /* DIO_ATMEGA32A_H_ */
