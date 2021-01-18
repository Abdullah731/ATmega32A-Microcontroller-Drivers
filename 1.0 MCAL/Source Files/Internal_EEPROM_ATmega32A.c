/*
 * Internal_EEPROM_ATmega32A.c
 *
 * Created: 6/30/2020 10:20:04 AM
 *  Author: Abdullah M.Abdullah
 */ 

#include "Internal_EEPROM_ATmega32A.h"
#include "uc_Configuration.h"
#include "Macros.h"

uint8 EEPROM_Read(uint16 address)
{
	uint8 Data = 0;
	/* Checking if the EEPROM is ready for operation */
	while((READBIT(EECR->allRegister,EECR->bits.b1)) != LOW);
	EEARL->allRegister = (address);
	EEARH->allRegister = (address>>8);
	EECR->bits.b1 = LOW;
	EECR->bits.b0 = HIGH;
	return (Data);
}

void EEPROM_Write(uint8 Data,uint16 address)
{
	/* Checking if the EEPROM is ready for operation */
	while((READBIT(EECR->allRegister,EECR->bits.b1)) != LOW);
	EEDR->allRegister = Data;
	EEARL->allRegister = (address);
	EEARH->allRegister = (address>>8);
	EECR->bits.b2 = HIGH;
	EECR->bits.b1 = HIGH;
	
}