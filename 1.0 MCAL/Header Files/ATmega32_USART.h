/*
 * ATmega32_USART.h
 *
 * Created: 6/20/2020 1:44:47 AM
 *  Author: Abdullah
 */ 


#ifndef ATMEGA32_USART_H_
#define ATMEGA32_USART_H_



typedef enum 
{
	USART_SingleProcessor,
	USART_MultiProcessor,
}USART_CommunicationTerminal;

typedef enum
{
	USART_Async_NormalSpeed,
	USART_Async_DoubleSpeed,
	USART_Sync,
}USART_CommunicationMode;


typedef enum
{
	USART_Disable,
	USART_Tx_Only,
	USART_Rx_Only,
	USART_Tx_Rx,
}USART_EnableMode;


typedef enum
{
	USART_InterruptsDisable,
	USART_RxComp_Enable,
	USART_TxComp_Enable,
	USART_UDREmpty_Enable,
	USART_RxComp_TxComp_Enable,
	USART_RxComp_UDREmpty_Enable,
	USART_TxComp_UDREmpty_Enable,
	USART_RxComp_TxComp_UDREmpty_Enable,
}USART_Interrupt_Settings;


typedef enum
{
	USART_5_bitData,
	USART_6_bitData,
	USART_7_bitData,
	USART_8_bitData,
	USART_9_bitData,		
}USART_DataFrame;


typedef enum
{
	USART_ParityDisable_1Stop,
	USART_ParityDisable_2Stop,
	USART_ParityEven_1Stop,
	USART_ParityEven_2Stop,
	USART_ParityOdd_1Stop,
	USART_ParityOdd_2Stop,
}USART_ControlFrame;


typedef enum
{
	USART_Sample_Falling_Edge,
	USART_Sample_Rising_Edge,
}USART_ClockPolarity;

typedef enum
{
	USART_NoError,
	USART_ParityError,
	USART_OverRunError,
	USART_FrameError,
}USART_ErrorType;

typedef struct  
{
	/* Please refer to upper enum for more details */
	USART_EnableMode												EnableMode;
	USART_CommunicationMode									CommunicationMode;
	USART_CommunicationTerminal								CommunicationTerminal;
	USART_Interrupt_Settings										InterruptSettings;
	USART_DataFrame													DataFrame;
	USART_ControlFrame												ControlFrame;
	/* Assign this only work on sync mode*/
	USART_ClockPolarity												ClockPolarity;
	uint16																	BaudRate; /* variable has 10 bits */
	/* Read This flag before using data received from the Read Function, and clear this flag urself */
	USART_ErrorType													ReadMsg_Error;
	/* Call Back Members */
	void																		(*RXC_InterruptCall)(void); // Pointer to function, it point to a function you wish to be called by RXC interrupt
	void																		(*TXC_InterruptCall)(void); // Pointer to function, it point to a function you wish to be called by TXC interrupt
	void																		(*UDRE_InterruptCall)(void); // Pointer to function, it point to a function you wish to be called by UDRE interrupt
	
	
}USART_ConfigurationStruct;

extern USART_ConfigurationStruct			USART0;

void USART_init(void);
void USART_SendByte_polling(uint16 Data);
void USART_SendByte_Nonolling(uint8 Data);
uint16 USART_ReceiveByte_polling();
uint16 USART_ReceiveByte_NonPolling(void);

#endif /* ATMEGA32_USART_H_ */