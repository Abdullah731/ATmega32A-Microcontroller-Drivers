/* MICROCHIP EEPROM 25AA010A Memory */

#include "ATmega32_SPI.h"
#include "uc_Configuration.h"
#include <util/delay.h>
#include "DIO_ATmega32A.h"
#include "External_EEPROM.h"


#define DUMMY_DATA					(0x00)
#define CHIP_SELECT_PORT				(DIOB)
#define CHIP_SELECT_PIN				(PIN0)
#define SPI_USED							(SPI0)
#define READ_INSTRUCTION			(0x03)
#define WREN_INSTRUCTION			(0x06)
#define WRITE_INSTRUCTION			(0x02)

void EEPROM25AA010A_init(void)
{
	/*
	* Note: if you used SPI Mode 3 or Mode 2 (CLK IDLE State = HIGH)
	* The AVR and some MicroControllers, we must explicitly State that the default clk pin state is high 
	* By Setting the pin to output with a HIGH value
	*/
	SPI_USED.ClockMode = SPI_ClockMode3;
	SPI_USED.DataOrder = SPI_MSB;
	SPI_USED.SelectMode = SPI_Master;
	SPI_USED.Frequency = SPI_Freq_By_4;
	SPI_USED.InterruptState = SPI_InterruptDisable;
	SPI_USED.EnableControl = SPI_Enable;
	SPI_init();
	/* CONFIGURE CHIP_SELECT_PIN TO BE THE CS PIN (OUTPUT) */
	DIO_pinConfigure(CHIP_SELECT_PORT,CHIP_SELECT_PIN,OUTPUT);
	
}

void EEPROM25AA010A_Write_Byte(uint8 Data, uint8 Address)
{
	/* SELECT EEPROM BY APPLYING LOW TO CS */
	DIO_pinWrite(CHIP_SELECT_PORT,CHIP_SELECT_PIN,LOW);
	/* WRITE LATCH ENABLE */
	SPI_ReadWrite_Blocking(WREN_INSTRUCTION);
	/* APPLY HIGH TO CS PIN TO MAKE WRITE LATCH ENABLE INSTRU. EXECUTED*/
	DIO_pinWrite(CHIP_SELECT_PORT,CHIP_SELECT_PIN,HIGH);
	_delay_ms(5); // To Execute the write enable latch instru.
	DIO_pinWrite(CHIP_SELECT_PORT,CHIP_SELECT_PIN,LOW);
	SPI_ReadWrite_Blocking(WRITE_INSTRUCTION);
	SPI_ReadWrite_Blocking(Address);
	SPI_ReadWrite_Blocking(Data);
	DIO_pinWrite(CHIP_SELECT_PORT,CHIP_SELECT_PIN,HIGH);
	_delay_ms(5); // To Write the data.
}

uint8 EEPROM25AA010A_Read_Byte(uint8 Address)
{
	uint8 Read_Data = 0;
	DIO_pinWrite(CHIP_SELECT_PORT,CHIP_SELECT_PIN,LOW);
	SPI_ReadWrite_Blocking(READ_INSTRUCTION);
	SPI_ReadWrite_Blocking(Address);
	Read_Data = SPI_ReadWrite_Blocking(DUMMY_DATA); // Sending Dummy Byte to receive the required data.
	DIO_pinWrite(CHIP_SELECT_PORT,CHIP_SELECT_PIN,HIGH);
	return (Read_Data);
}