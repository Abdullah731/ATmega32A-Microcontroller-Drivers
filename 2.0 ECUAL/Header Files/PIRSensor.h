/*
 * PIRSensor.h
 *
 * Created: 7/12/2020 11:55:54 AM
 *  Author: Abdullah M.Abdullah
 */ 


#ifndef PIRSENSOR_H_
#define PIRSENSOR_H_
#include "DIO_ATmega32A.h"

	typedef struct
	{
		DIO_Struct * PIRSensor_Dio;
		pinNumber PIRSensor_pin;
	}PIRSensorDatatype;
	

void PIRSensor_init(PIRSensorDatatype PIR);

#endif /* PIRSENSOR_H_ */