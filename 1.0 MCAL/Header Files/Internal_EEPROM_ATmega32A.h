/*
 * Internal_EEPROM_ATmega32A.h
 *
 * Created: 6/30/2020 10:19:36 AM
 *  Author: Abdullah
 */ 


#ifndef INTERNAL_EEPROM_ATMEGA32A_H_
#define INTERNAL_EEPROM_ATMEGA32A_H_

#include "DIO_ATmega32A.h"
#include "uc_Configuration.h"

uint8 EEPROM_Read(uint16 address);
void EEPROM_Write(uint8 Data,uint16 address);



#endif /* INTERNAL_EEPROM_ATMEGA32A_H_ */