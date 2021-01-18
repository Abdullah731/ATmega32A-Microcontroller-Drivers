/* MICROCHIP EEPROM 25AA010A Memory */


#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_


void EEPROM25AA010A_init(void);
void EEPROM25AA010A_Write_Byte(uint8 Data, uint8 Address);
uint8 EEPROM25AA010A_Read_Byte(uint8 Address);



#endif /* EXTERNAL EEPROM_H_ */