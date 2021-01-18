/**
 * @file <microController Configuration .h>
 * @brief <Define Here All MCU Prepheral and Cpu Register Adresses>
 *
 * <This File Contains ALL ATmega32A Register Address and Memory Map Information>
 *
 * @author <	Abdullah Mustafa Abdullah  - abdallah.moustafa333@gmail.com	>
 * @date <2017>
 *
 */

#ifndef UC_CONFIGURATION_H_S
#define UC_CONFIGURATION_H_S

#define _AVR_ATMEGA32A_H_INCLUDED

	#include "Macros.h"
	#include "StdTypes.h"
/******************************* CPU Debugger Defines  *****************************************************/

#define  DEBUG_USER		0

#if DEBUG_USER

#define ERRORMSG(Msg)			{printf(Msg);}
#else
#define ERRORMSG(Msg)			{}
#endif
							  
/******************************* CPU Related Defines *******************************************************/
#define F_CPU		(16000000U)

/******************************* CPU Internal Registers <SFRs & GPRs> **************************************/
#define IO_OFFSET	(0x20)
#define SRAM_OFFSET	(0x60)
#define CPU_REG		((vuint8_t *)0x00)
#define NULL	((void *) 0x0FFF)

#define ATMEGA32_SREG		((reg8*)(0x3F+IO_OFFSET))
#define ATMEGA32A_MCUCR		((reg8*)(0x35+IO_OFFSET))
#define ATMEGA32_MCUCSR		((reg8*)(0x34+IO_OFFSET))
#define ATMEGA32_GICR		((reg8*)(0x3B+IO_OFFSET))
#define GIFR				((reg8*)(0x3A+IO_OFFSET))
#define SFIOR				((reg8*)(0x30+IO_OFFSET))

/******************************************* Defines for Port  **************************************/

#define	DIOA		((DIO_Struct *)(0x19+IO_OFFSET))
#define DIOB		((DIO_Struct *)(0x16+IO_OFFSET))
#define DIOC		((DIO_Struct *)(0x13+IO_OFFSET))
#define DIOD		((DIO_Struct *)(0x10+IO_OFFSET))

/******************************* EEPROM INTERNAL REGISTERS **************************************/

#define EEARH		((reg8*)(0x1F + IO_OFFSET))
#define EEARL		((reg8*)(0x1E + IO_OFFSET))
#define EEDR		((reg8*)(0x1D + IO_OFFSET))
#define EECR		((reg8*)(0x1C + IO_OFFSET))


/*****************************************  Attribute Defines FOR AVR Interrupt Handling ************************************************/
#define ISR_NONBLOCK 	__attribute__((interrupt))
#define ISR_BLOCK
#define ISR_NAKED      	__attribute__((naked))
#define ISR_ALIASOF(v) 	__attribute__((alias(__STRINGIFY(v))))
#define _VECTOR(N) 		__vector_ ## N

#define ISR(V,...)	void V (void) __attribute__ ((signal)) __VA_ARGS__;\
				    void V (void)

/******************************* Timer_Counter_0 REGISTERS **************************************/
#define TIMER0_OVF_VECT		_VECTOR(11)
#define TIMER0_COMP_VECT	_VECTOR(10)
#define  TCCR0		(( reg8 *) (0x33 + IO_OFFSET))
#define  TCNT0		(( reg8 *) (0x32 + IO_OFFSET))
#define  OCR0		(( reg8 *) (0x3C + IO_OFFSET))
#define TIMSK		((reg8*)(0x39+IO_OFFSET))


/******************************* USART INTERNAL REGISTERS **************************************/
#define UDR		((reg8*)(0x0C+IO_OFFSET))
#define UCSRA	((reg8*)(0x0B+IO_OFFSET))
#define UCSRB	((reg8*)(0x0A+IO_OFFSET))
#define UBRRL	((reg8*)(0x09+IO_OFFSET))
#define UBRRH 	((reg8*)(0x20+IO_OFFSET))
#define UCSRC 	((reg8*)(0x20+IO_OFFSET))

#define UCPOL   0
#define UCSZ0   1
#define UCSZ1   2
#define USBS    3
#define UPM0    4
#define UPM1    5
#define UMSEL   6
#define URSEL   7
#define TXB8    0
#define RXB8    1
#define UCSZ2   2
#define TXEN    3
#define RXEN    4
#define UDRIE   5
#define TXCIE   6
#define RXCIE   7
#define MPCM    0
#define U2X     1
#define UPE     2
#define DOR     3
#define FE      4
#define UDRE    5
#define TXC     6
#define RXC     7

/******************************* SPI INTERNAL REGISTERS **************************************/

#define SPCR		((reg8*)(0x0D+IO_OFFSET))
#define SPSR		((reg8*)(0x0E + IO_OFFSET))
#define SPDR		((reg8*)(0x0F+IO_OFFSET))


#define SPR0		b0
#define SPR1		b1
#define CPHA	b2
#define CPOL		b3
#define MSTR	b4
#define DORD	b5
#define	SPE		b6
#define SPIE		b7
#define	SPI2X	b0
#define WCOL	b6
#define	SPIF		b7
 
/******************************************* ATmega32A ADC Register ***********************************************/
#define  ADCSRA			((reg8 *) (0x06 + IO_OFFSET))
#define  ADMUX			((reg8 *) (0x07 + IO_OFFSET))
#define  ADCL			((reg8 *) (0x04 + IO_OFFSET))
#define  ADCH			((reg8 *) (0x05 + IO_OFFSET))
#define  ADC_DATA		(*(vuint16 *) (0x04 + IO_OFFSET))
#define  ADC_VECT		_VECTOR(16)
#define  ADC_ENABLE		(1<<7)

/******************************************* Global Interrupt Related Macros **************************************/
	#define GLOBAL_INTERRUPT_ENABLE()	{ATMEGA32_SREG->bits.b7=1;}
	#define GLOBAL_INTERRUPT_DISABLE()	{ATMEGA32_SREG->bits.b7=0;}
	
/******************************************* User Types For AVR MCU **************************************/

	typedef union
	{
		vuint8_t allRegister;
		struct
		{
			vuint8_t b0:1;
			vuint8_t b1:1;
			vuint8_t b2:1;
			vuint8_t b3:1;
			vuint8_t b4:1;
			vuint8_t b5:1;
			vuint8_t b6:1;
			vuint8_t b7:1;
		}bits;
	}reg8;

	typedef struct
	{
		reg8 pin;
		reg8 ddr;
		reg8 port;
	}DIO_Struct;


#endif /* UC_CONFIGURATION_H_ */
