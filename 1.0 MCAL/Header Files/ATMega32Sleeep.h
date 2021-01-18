/*
 * ATMega32Sleeep.h
 *
 * Created: 2/29/2017 4:52:42 PM
 *  Author: Abdullah M.Abdullah
 */ 


#ifndef ATMEGA32SLEEEP_H_
#define ATMEGA32SLEEEP_H_

#include "uc_Configuration.h"

#define  IDLE_MODE  0x00
#define ADC_NOISE_REDUCTION_MODE 0x10
#define POWER_DOWN_MODE 0x20
#define POWER_SAVE_MODE 0x30
#define STAND_BY_MODE 0x60
#define EXTEND_STAND_BY_MODE 0x70

#define  SET_SLEEP_MODE(SLEEP_MODE)   do{\
	ATMEGA32A_MCUCR->allRegister &= 0x0f;\
	ATMEGA32A_MCUCR->allRegister|=SLEEP_MODE;\
}while(0)


#define SLEEP_ENABLE()        do{\
	ATMEGA32A_MCUCR->allRegister|=(1<<7); \
}while(0)

#define SLEEP_DISABLE()        do{\
	ATMEGA32A_MCUCR->allRegister&=~(1<<7);\
}while(0)


#define SLEEP_NOW()	do{\
	__asm__ __volatile__ ( "sleep" "\n\t" :: );\
}while(0)



#endif /* ATMEGA32SLEEEP_H_ */