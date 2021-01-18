/*
 * ATmega32_SPI.c
 *
 * Created: 6/22/2020 4:22:04 AM
 *  Author: Abdullah M.Abdullah
 */ 

#include "uc_Configuration.h"
#include "ATmega32_SPI.h"
#include "DIO_ATmega32A.h"

ISR(_VECTOR(12))
{
	if(SPI0.SPI_TransferInterruptCall != NULL)
	{
		SPI0.SPI_TransferInterruptCall();
	}
}

SPI_ConfigStruct SPI0 = {0,.SPI_TransferInterruptCall=NULL};

void SPI_init(void)
{
	SPCR->allRegister = 0;
	SPSR->allRegister = 0;
	switch(SPI0.EnableControl)
	{
		case SPI_Disable:
		break;
		case SPI_Enable:
			switch(SPI0.SelectMode)
			{
				case SPI_Master:
					SPCR->bits.b4 = TRUE;
					DIO_pinConfigure(DIOB,PIN4,OUTPUT);
					DIO_pinConfigure(DIOB,PIN5,OUTPUT);
					DIO_pinConfigure(DIOB,PIN7,OUTPUT);
					
				break;
				case SPI_Slave:
					DIO_pinConfigure(DIOB,PIN6,OUTPUT);				
				break;
				default:
				break;
			}
			switch(SPI0.DataOrder)
			{
				case SPI_LSB:
				SPCR->bits.b5 = TRUE;
				break;
				case SPI_MSB:
				break;
				default:
				break;
			}
			switch(SPI0.InterruptState)
			{
				case SPI_InterruptDisable:
				break;
				case SPI_InterruptEnable:
					SPCR->bits.b7 = TRUE;
				break;
				default:
				break;
			}
			switch(SPI0.ClockMode)
			{
				case SPI_ClockMode0:
				break;
				case SPI_ClockMode1:
					SPCR->bits.b2 = TRUE;
				break;
				case SPI_ClockMode2:
					SPCR->bits.b3 = TRUE;
					/*
					* Note: if you used SPI Mode 3 or Mode 2 (CLK IDLE State = HIGH)
					* The AVR and some MicroControllers, we must explicitly State that the default clk pin state is high 
					* By Setting the pin to output with a HIGH value
					*/
					DIO_pinWrite(DIOB,PIN7,OUTPUT);
				break;
				case SPI_ClockMode3:
					SPCR->bits.b2 = TRUE;	
					SPCR->bits.b3 = TRUE;
					/*
					* Note: if you used SPI Mode 3 or Mode 2 (CLK IDLE State = HIGH)
					* The AVR and some MicroControllers, we must explicitly State that the default clk pin state is high 
					* By Setting the pin to output with a HIGH value
					*/
					DIO_pinWrite(DIOB,PIN7,OUTPUT);
				break;
				default:
				break;
			}
			switch(SPI0.Frequency)
			{
				case SPI_Freq_By_2:
					SPSR->bits.b0 = TRUE;
				break;
				case SPI_Freq_By_4:
				break;
				case SPI_Freq_By_8:
					SPSR->bits.b0 = TRUE;
					SPCR->bits.b0 = TRUE;					
				break;
				case SPI_Freq_By_16:
					SPCR->bits.b0 = TRUE;					
				break;
				case SPI_Freq_By_32:
					SPCR->bits.b1 = TRUE;
					SPSR->bits.b0 = TRUE;
				break;
				case SPI_Freq_By_64:
					SPCR->bits.b1 = TRUE;				
				break;
				case SPI_Freq_By_128:
					SPCR->bits.b0 = TRUE;
					SPCR->bits.b1 = TRUE;
				break;
			}
			/* ENABLE SPI COMMUNICATION */
			SPCR->bits.b6 = TRUE;
		break;
		default:
		break;	
	}
}

uint8 SPI_ReadWrite_Blocking(uint8 Data)
{
	SPDR->allRegister = Data;
	if (SPSR->bits.b6 == TRUE)
	{
		SPI0.Error = SPI_ErrorCollision;
	}
	while (!(SPSR->bits.b7));	
	return SPDR->allRegister;
	
}
uint8 SPI_ReadWrite_NonBlocking(uint8 Data)
{
	SPDR->allRegister = Data;
	if (SPSR->bits.b6 == TRUE)
	{
		SPI0.Error = SPI_ErrorCollision;
	}
	return SPDR->allRegister;
}