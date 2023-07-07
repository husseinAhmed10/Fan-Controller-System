/*
 * ADC.h
 *
 *  Created on: Apr 29, 2023
 *      Author: T.S
 */



#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"



/*DataTypes of ADC*/
#define ADC_ReferenceVolatge uint8
#define ADC_Prescaler uint8
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

typedef struct {
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
} ADC_ConfigType;

#define polling 1

#define interrupt 0

/*Function prototype*/
#if(polling == 1)
void ADC_init(const ADC_ConfigType *Config_Ptr);

uint16 ADC_readChannel(uint8 ch_num);
#endif

#if(interrupt == 1)
void ADC_init(void);
void ADC_readChannel(uint8 channel_num);
#endif

#endif /* ADC_H_ */

