/*
 * ADC.c
 *
 *  Created on: Apr 29, 2023
 *      Author: T.S
 */

#include <avr/io.h>
#include "adc.h"
#include "common_macros.h"


#if(polling==1)
void ADC_init(const ADC_ConfigType *Config_Ptr) {


	/*Reference SelectionBit (7:6)
	 *00: External
	 *01: AVCC
	 *11: 2.56 V internal
	 * */

	ADMUX = Config_Ptr->ref_volt;

	/*
	 * channel 0 (Doesn't matter will change it in the read channel according to our choice)
	 * */

	/*
	 * ADC Enable
	 * Choose Prescalar in range 50-200 KHZ
	 */

	ADCSRA = 0;
	ADCSRA |= ((Config_Ptr->prescaler)& 0x07);
	ADCSRA |= (1<<ADEN);

}

uint16 ADC_readChannel(uint8 ch_num) {

	/*INSERT CH NUM*/
	ch_num &= 0x07;
	ADMUX &= 0xE0;
	ADMUX |= (ch_num);

	/*start conversion*/
	SET_BIT(ADCSRA, ADSC);

	/*polling until ADIF=1 "ADC conversion complete" */
	while (BIT_IS_CLEAR(ADCSRA, ADIF));

	/*clear ADIF by setting it  with '1' */
	SET_BIT(ADCSRA, ADIF);

	/*read data from ADC data register*/
	return ADC;

}
#endif

#if(interrupt==1)

#include <avr/interrupt.h>

ISR(ADC_vect)
{
	/* Read ADC Data after conversion complete */
	g_adcResult = ADC;
}


void ADC_init(void)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = 0;

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 1 Enable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = 011 to choose ADC_Clock = F_CPU/8 = 1Mhz/8 = 125Khz --> ADC must operate in range 50-200Khz
	 */
	ADCSRA = (1<<ADEN) | (1<<ADIE) | (1<<ADPS1) | (1<<ADPS0);
}

void ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
}


#endif
