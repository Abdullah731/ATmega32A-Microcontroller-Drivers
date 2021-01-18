/*
 * ATMEGA32_ADC.h
 *
 * Created: 2/29/2017 11:43:38 AM
 *  Author: Abdullah M.Abdullah
 */ 


#ifndef ATMEGA32_ADC_H_
#define ATMEGA32_ADC_H_

	
	#include "StdTypes.h"
	
	typedef enum
	{
		AREF=0x00,
		AVCC=0x40,
		INTERNAL_2_56v=0xc0,
	}ADC_RefrenceSelect;

	typedef enum
	{
		ADC_10BITS=0x00,
		ADC_8BIT=0x20,
	}ADC_Resloution;
	
	typedef enum
	{
		ADC0,
		ADC1,
		ADC2,
		ADC3,
		ADC4,
		ADC5,
		ADC6,
		ADC7,
		ADC_DIFF_PADC0_NADC0_G10,
		ADC_DIFF_PADC1_NADC0_G10,
		ADC_DIFF_PADC0_NADC0_G200,
		ADC_DIFF_PADC1_NADC0_G200,
		ADC_DIFF_PADC2_NADC2_G10,
		ADC_DIFF_PADC3_NADC2_G10,
		ADC_DIFF_PADC2_NADC2_G200,
		ADC_DIFF_PADC3_NADC2_G200,
		ADC_DIFF_PADC0_NADC1_G1,
		ADC_DIFF_PADC1_NADC1_G1,
		ADC_DIFF_PADC2_NADC1_G1,
		ADC_DIFF_PADC3_NADC1_G1,
		ADC_DIFF_PADC4_NADC1_G1,
		ADC_DIFF_PADC5_NADC1_G1,
		ADC_DIFF_PADC6_NADC1_G1,
		ADC_DIFF_PADC7_NADC1_G1,
		ADC_DIFF_PADC0_NADC2_G1,
		ADC_DIFF_PADC1_NADC2_G1,
		ADC_DIFF_PADC2_NADC2_G1,
		ADC_DIFF_PADC3_NADC2_G1,
		ADC_DIFF_PADC4_NADC2_G1,
		ADC_DIFF_PADC5_NADC2_G1,
		ADC_BANDGAP_1_22V,
		ADC_GND_0V,
	}ADC_Channel;
	
	typedef enum
	{
		ADC_SingleConv=0x0000,
		ADC_AutoTrig_FREERuning=0x0020,
		ADC_AutoTrig_AnalogCompartor=0x2020,
		ADC_AutoTrig_EXTINT0=0x4020,
		ADC_AutoTrig_TIMER0_CompareMatch=0x6020,
		ADC_AutoTrig_TIMER0_OVF=0x8020,
		ADC_AutoTrig_Timer1_CompareMatch_B=0xA020,
		ADC_AutoTrig_Timer1_OVF=0xC020,
		ADC_AutoTrig_Timer1_CaptureEvent=0xE020,
	}ADC_ConvMode;
	
	typedef enum
	{
		ADC_FCPU_BY2 = 0x01,
		ADC_FCPU_BY4,
		ADC_FCPU_BY8,
		ADC_FCPU_BY16,
		ADC_FCPU_BY32,
		ADC_FCPU_BY64,
		ADC_FCPU_BY128,
	}ADC_PreScalerSelect;
	
	typedef enum
	{
		ADC_InterruptDisable=0x00,
		ADC_InterruptEnable=0x08,
	}ADC_Interrupt;
	
	
	
	extern void (*ADC_CallBack) (uint16);
	
	void ADC_Init(
					ADC_RefrenceSelect Refrence,
					ADC_ConvMode       Conv,
					ADC_PreScalerSelect F_ADC,
					ADC_Interrupt   InterruptMode);
					
	uint16 ADC_Read_Polling(
							ADC_Channel Channel,
							ADC_Resloution Resloution);
	
	void ADC_Read_Interrupt(
								ADC_Channel Channel,
								ADC_Resloution Resloution);
	
	void ADC_Disable(void);
	
#endif /* ATMEGA32_ADC_H_ */