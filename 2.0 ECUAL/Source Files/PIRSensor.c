/*
 * PIRSensor.c
 *
 * Created: 7/12/2020 11:56:04 AM
 *  Author: Abdullah
 */ 

#include "PIRSensor.h"
#include "Macros.h"

void PIRSensor_init(PIRSensorDatatype PIR)
{
	CLEARBIT(PIR.PIRSensor_Dio->ddr.allRegister,PIR.PIRSensor_pin);
}
