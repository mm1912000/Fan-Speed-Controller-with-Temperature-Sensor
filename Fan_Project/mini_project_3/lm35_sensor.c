 /******************************************************************************
 *
 * Module: Temperature Sensor
 *
 * File Name: lm35_sensor.h
 *
 * Description: source file for the LM35 Temperature Sensor driver
 *
 * Author: Marwan Medhat
 *
 *******************************************************************************/
#if (INTERRUPT_ENABLE == LOGIC_HIGH )
#include <util/delay.h>
#endif
#include "lm35_sensor.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature(void)
{
	uint8 temp_value = 0;

#if (INTERRUPT_ENABLE == LOGIC_HIGH )
	/* read ADC channel where the temperature sensor is connected */
	ADC_readChannel(SENSOR_CHANNEL_ID);
	/* delay until the g_adcresult value is updated from the ISR */
	_delay_ms(5);
	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8)(((uint32)g_adcresult*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));
#else
	uint16 adc_value = 0;
	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);
	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8)(((uint32)adc_value*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));
#endif

	return temp_value;
}

