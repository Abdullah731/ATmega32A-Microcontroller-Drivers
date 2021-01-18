/*
 * ATmega32_SPI.h
 *
 * Created: 6/22/2017 4:22:22 AM
 *  Author: Abdullah M.Abdullah
 */ 


#ifndef ATMEGA32_SPI_H_
#define ATMEGA32_SPI_H_

#include "uc_Configuration.h"
#include "DIO_ATmega32A.h"

typedef enum
{
	SPI_Enable,
	SPI_Disable,
		
}SPI_Control;

typedef enum
{
	SPI_InterruptDisable,
	SPI_InterruptEnable,
}SPI_InterruptState;

typedef enum
{
	SPI_LSB,
	SPI_MSB,
}SPI_DataOrder;

typedef enum
{
	SPI_Slave,
	SPI_Master,
}SPI_Mode;

typedef enum
{
	SPI_ClockMode0,
	SPI_ClockMode1,
	SPI_ClockMode2,
	SPI_ClockMode3,
}SPI_ClockMode;

typedef enum
{
	SPI_Freq_By_2,
	SPI_Freq_By_4,
	SPI_Freq_By_8,
	SPI_Freq_By_16,
	SPI_Freq_By_32,
	SPI_Freq_By_64,
	SPI_Freq_By_128,
}SPI_Frequency;

typedef enum
{
	SPI_NoError,
	SPI_ErrorCollision,
}SPI_Error;


typedef struct
{
	SPI_Control			EnableControl;
	SPI_Mode				SelectMode;
	SPI_ClockMode		ClockMode;
	SPI_DataOrder		DataOrder;
	SPI_InterruptState	InterruptState;
	SPI_Frequency		Frequency;
	SPI_Error				Error;	
	void						(*SPI_TransferInterruptCall)(void);
}SPI_ConfigStruct;

extern SPI_ConfigStruct SPI0;

void SPI_init(void);
uint8 SPI_ReadWrite_Blocking(uint8 Data);
uint8 SPI_ReadWrite_NonBlocking(uint8 Data);


#endif /* ATMEGA32_SPI_H_ */