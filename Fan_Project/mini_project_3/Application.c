/*
 * Application.c
 *
 *  Created on: Feb 22, 2024
 *      Author: Marwan Medhat
 */
#include "lcd.h"
#include "lm35_sensor.h"
#include "dcmotor.h"


int main()
{
	/* configure the ADC with internal voltage of 2.56 V and the prescaler F_CPU/8 */
	ADC_ConfigType ADC_configuration = { VINTERNAL , ADC_PRESCALER_8 };

	/* temp value to store the temperature value */
	uint8 temp;
	/* Start the DC Motor */
	DcMotor_init();
	/* Start the LCD */
	LCD_init();
	/* initialize the ADC */
	ADC_init(&ADC_configuration);

	/* Those 2 functions are outside the while(1) loop because they wont be changed during the runtime */
	LCD_displayStringRowColumn(1,0,"  Temp =      C.");
	LCD_displayStringRowColumn(0,0,"  FAN is ");

	while(1)

	{
		/* temperature variable will contain the sensor readings */
		temp = LM35_getTemperature();

		/* This if condition is to display the temperature value on the LCD and the else condition is to display the temperature value
		 * and delete the extra character when the temperature changes from 3 digits to either 2 or 1 digit.
		 */
		if ( temp > 100 )
		{
			LCD_moveCursor(1,9);
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_moveCursor(1,9);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}

		/* This if condition will either display OFF or ON on the LCD based on the temperature */
		if ( temp < 30 )
		{
			DcMotor_Rotate(STOP, 0);
			LCD_moveCursor(0,9);
			LCD_displayString("OFF.");
		}
		else
		{
			LCD_moveCursor(0,9);
			LCD_displayString("ON .");
		}

		/* This if condition will change the motor speed according to the temperature */
		if ( temp >= 30 && temp < 60 )
		{
			DcMotor_Rotate(CW, 25);
		}
		else if ( temp >= 60 && temp < 90 )
		{
			DcMotor_Rotate(CW, 50);
		}
		else if ( temp >= 90 && temp < 120 )
		{
			DcMotor_Rotate(CW, 75);
		}
		else if ( temp >= 120 )
		{
			DcMotor_Rotate(CW, 100);
		}

	}

}

