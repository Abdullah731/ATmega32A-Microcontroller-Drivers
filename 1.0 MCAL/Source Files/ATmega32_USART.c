/*
 * ATmega32_USART.c
 *
 * Created: 6/20/2020 1:44:57 AM
 *  Author: Abdullah M.Abdullah
 */ 
#include "DIO_ATmega32A.h"
#include "uc_Configuration.h"
#include "ATmega32_USART.h"
#include "StdTypes.h"
#include "Macros.h"

USART_ConfigurationStruct			USART0 ={0,
																.RXC_InterruptCall = NULL,
																.TXC_InterruptCall = NULL,
																.UDRE_InterruptCall = NULL	};

ISR(_VECTOR(13))
{
	if(USART0.RXC_InterruptCall != NULL)
	{
		USART0.RXC_InterruptCall();
	}
	else
	{
		// Handle the error using Handling error function.
	}
}

ISR(_VECTOR(15))
{
	if(USART0.TXC_InterruptCall != NULL)
	{
		USART0.TXC_InterruptCall();
	}
	else
	{
		// Handle the error using Handling error function.
	}
}

ISR(_VECTOR(14))
{
	if(USART0.UDRE_InterruptCall != NULL)
	{
		USART0.UDRE_InterruptCall();
	}
	else
	{
		// Handle the error using Handling error function.
	}
}

void USART_init(void)
{
	uint8_t UCSRA_Temp = 0;
	uint8_t UCSRB_Temp = 0;
	uint8_t UCSRC_Temp = 0;
	float UBRR_Temp = 0;
	
	switch (USART0.EnableMode)
	{
		case USART_Disable:
		break;
		
		case USART_Rx_Only:
				UCSRB_Temp |= (1 << RXEN);
		break;
		
		case USART_Tx_Only:
				UCSRB_Temp |= (1 << TXEN);
		break;
		case USART_Tx_Rx:
				UCSRB_Temp |= (1 << RXEN) | (1 << TXEN);
		break;	
		default:
		break;										  
	}
	
	switch(USART0.CommunicationMode)
	{
			case USART_Async_NormalSpeed:
					UBRR_Temp = ((float)(F_CPU) / (16.0 *USART0.BaudRate) - 1) + 0.5;
					break;
			
			case USART_Async_DoubleSpeed:
					UCSRA_Temp |= (1 << U2X);
					UBRR_Temp = ((float)(F_CPU) / (8.0 *USART0.BaudRate) - 1) + 0.5;
					break;
			
			case USART_Sync:
					UCSRC_Temp |= (1 << UMSEL);
					UBRR_Temp = ((float)(F_CPU) / (2.0 *USART0.BaudRate) - 1) + 0.5;
					switch(USART0.ClockPolarity)
					{
						case USART_Sample_Falling_Edge:
						break;
						case USART_Sample_Rising_Edge:
							UCSRC_Temp |= (1 << UCPOL);							
						break;
					}
					break;

			default:
					break;
	}

	switch(USART0.CommunicationTerminal)
	{
		case USART_SingleProcessor:
				break;
		case USART_MultiProcessor:
				UCSRA_Temp |= (1 << MPCM);
				break;
		default:
				break;
	}	
	
	switch(USART0.InterruptSettings)
	{
		case USART_InterruptsDisable:
				break;
		case USART_RxComp_Enable:
				UCSRB_Temp |= (1 << RXCIE);
				break;
		case USART_TxComp_Enable:
				UCSRB_Temp |= (1 << TXCIE);
				break;
		case USART_UDREmpty_Enable:
				UCSRB_Temp |= (1 << UDRE);
				break;
		case USART_RxComp_TxComp_Enable:
				UCSRB_Temp |= (1 << TXCIE) | (1 << RXCIE);
				break;
		case USART_RxComp_UDREmpty_Enable:
				UCSRB_Temp |= (1 << RXCIE) | (1 << UDRE);
				break;
		case USART_TxComp_UDREmpty_Enable:
				UCSRB_Temp |= (1 << TXCIE) | (1 << UDRE);
				break;
		case USART_RxComp_TxComp_UDREmpty_Enable:
				UCSRB_Temp |= (1 << TXCIE) | (1 << RXCIE) | (1 << UDRE);
				break;
		default:
				break;
	}
	
	switch(USART0.DataFrame)
	{
		case USART_5_bitData:
		break;
		case USART_6_bitData:
			UCSRC_Temp |= (1 << UCSZ0);
		break;
		case USART_7_bitData:
			UCSRC_Temp |= (1 << UCSZ1);
		break;
		case USART_8_bitData:
			UCSRC_Temp |= (1 << UCSZ1) | (1 << UCSZ0);
		break;
		case USART_9_bitData:
			UCSRC_Temp |= (1 << UCSZ1) | (1 << UCSZ0);
			UCSRB_Temp |= (1 << UCSZ2);
		break;
		default:
			break;
	}
	
	switch(USART0.ControlFrame)
	{
		case USART_ParityDisable_1Stop:
		break;
		case USART_ParityDisable_2Stop:
			UCSRC_Temp |= (1 << USBS);
		break;
		case USART_ParityEven_1Stop:
			UCSRC_Temp |= (1 << UPM1);
		break;
		case USART_ParityEven_2Stop:
			UCSRC_Temp |= (1 << USBS) | (1 << UPM1);
		break;
		case USART_ParityOdd_1Stop:
			UCSRC_Temp |= (1 << UPM1) | (1 << UPM0);
		break;
		case USART_ParityOdd_2Stop:
		UCSRC_Temp |= (1 << USBS) | (1 << UPM1) | (1 << UPM0);
		break;
		default:
		break;
		
	}
	
	UBRRH->allRegister = (((uint16_t)UBRR_Temp)>>8);
	UBRRL->allRegister	= ((uint8_t)UBRR_Temp);
	UCSRA->allRegister	= UCSRA_Temp;
	UCSRC->allRegister	= UCSRC_Temp;
	UCSRB->allRegister	= UCSRB_Temp;

}

void USART_SendByte_polling(uint16 Data)
{
	while(!((UCSRA->allRegister) & (1 << UDRE)));
	if(USART0.DataFrame == USART_9_bitData)
	{
		/*
			1	1001	0010		&
			1	0000	0000
			1	0000	0000		>> 8
				0000	0001
		*/
		
		UCSRB->allRegister |= ((UCSRB->allRegister) & 0xFE) | ((Data & (1 << 8))>>8);		// 0xFE to clear the last bit ()
		
	}
	UDR->allRegister = (uint8) Data;
}

void USART_SendByte_Nonpolling(uint16 Data)
{
	if(((UCSRA->allRegister) & (1 << UDRE)))	// TO CHECK IF THE UDR IS READY TO STORE DATA (INTERRUPT METHOD)
	{
		if(USART0.DataFrame == USART_9_bitData)
		{
			/*
				1	1001	0010		&
				1	0000	0000
				1	0000	0000		>> 8
					0000	0001
			*/
		
			UCSRB->allRegister |= ((UCSRB->allRegister) & 0xFE) | ((Data & (1 << 8))>>8);		// 0xFE to clear the last bit ()
			UDR->allRegister = (uint8) Data;	
		}
}
}
uint16_t USART_ReceiveByte_polling()
{
	uint16_t receivedData = 0;
	while(!((UCSRA->allRegister) & (1 << RXC)));
	/* CHCEKING THE ERRORS*/
	if((UCSRA->allRegister) & ((1 << FE) | (1 << DOR) | (1 << UPE))) // UPE is PE bit.
	{
		if((UCSRA->allRegister) & (1 << FE))
		{
			USART0.ReadMsg_Error =	USART_FrameError;
		}
		else if ((UCSRA->allRegister) & (1 << DOR))
		{
			USART0.ReadMsg_Error =	USART_OverRunError;
		}
		else
		{
			USART0.ReadMsg_Error = USART_ParityError;
		}
	}
	
	if(USART0.DataFrame == USART_9_bitData)
	{
		receivedData = ((UCSRB->allRegister) & (1 << RXB8)) << 7;
	}
	receivedData |= UDR->allRegister;
	
	return	receivedData;
}

uint16 USART_ReceiveByte_NonPolling(void)
{
	uint16 receivedData = 0;
	if(((UCSRA->allRegister) & (1 << RXC)) != 0)
	{
		/* CHCEKING THE ERRORS*/
		if((UCSRA->allRegister) & ((1 << FE) | (1 << DOR) | (1 << UPE))) // UPE is PE bit.
		{
			if((UCSRA->allRegister) & (1 << FE))
			{
				USART0.ReadMsg_Error =	USART_FrameError;
			}
			else if ((UCSRA->allRegister) & (1 << DOR))
			{
				USART0.ReadMsg_Error =	USART_OverRunError;
			}
			else
			{
				USART0.ReadMsg_Error = USART_ParityError;
			}
		}
		if(USART0.DataFrame == USART_9_bitData)
		{
			receivedData = (((UCSRB->allRegister) & (1 << RXB8)) << 7);
		}
		receivedData |= (UDR->allRegister);
	}
	return (UDR->allRegister);
}