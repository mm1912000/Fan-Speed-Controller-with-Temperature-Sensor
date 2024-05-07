 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega16 ADC driver
 *
 * Author: Marwan Medhat
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define INTERRUPT_ENABLE     LOGIC_LOW       /* Set this definition to HIGH if you want to enable interrupt and LOW to disable it */
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

/*******************************************************************************
 *                         External Variables                                  *
 *******************************************************************************/
#if ( INTERRUPT_ENABLE == LOGIC_HIGH )
extern volatile uint16 g_adcresult;
#endif
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	AREF,AVCC,VINTERNAL = 3
}ADC_ReferenceVoltage;

typedef enum
{
	ADC_PRESCALER_2 = 1, ADC_PRESCALER_4, ADC_PRESCALER_8, ADC_PRESCALER_16, ADC_PRESCALER_32, ADC_PRESCALER_64, ADC_PRESCALER_128
}ADC_Prescaler;

typedef struct
{
	ADC_ReferenceVoltage ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */

#if (INTERRUPT_ENABLE == LOGIC_HIGH)
void ADC_readChannel(uint8 channel_num);
#else
uint16 ADC_readChannel(uint8 channel_num);
#endif

#endif /* ADC_H_ */
