/*
 * Mini_Project3.c
 *
 *  Created on: May 6, 2023
 *      Author: T.S
 */

#include "gpio.h"
#include "pwm.h"
#include "DCmotor.h"
#include "lcd.h"
#include "adc.h"
#include "lm35_sensor.h"

int main(void) {

	/*Main initialization*/

	ADC_ConfigType Config_Ptr1 = { 0XC0, 0X03 };



	ADC_init(&Config_Ptr1);

	/* debug configure pin PB0, PB1 and PB3 as input pins */
	/*DDRB |= 0x0B;*/
	/*PORTC = 0xFE;*/
	/*--------*/

	DcMotor_Init();
	/*DcMotor_Rotate(0, 0);*/

	LCD_init();
	LCD_displayString("Fan is ");
	LCD_moveCursor(1, 0);
	LCD_displayString("Temp =      C");

	uint8 temp = LM35_getTemperature();

	while (1) {

		/*Application*/

		if (temp < 30) {
			/*Turn off the fan*/
			DcMotor_Rotate(0, 0);

			/*Update the LCD*/
			LCD_moveCursor(0, 7);
			LCD_displayString("OFF");
			LCD_moveCursor(1, 8);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');

		} else if (temp >= 30 && temp < 60) {
			/*Turn ON the fan with 25% of its maximum speed*/
			DcMotor_Rotate(1, 25);

			/*debug*/
//			GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_HIGH);
			/*Update the LCD*/
			LCD_moveCursor(0, 7);
			LCD_displayString("ON");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1, 8);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		} else if (temp >= 60 && temp < 90) {
			/*Turn ON the fan with 50% of its maximum speed*/
			DcMotor_Rotate(1, 50);

			/*Update the LCD*/
			LCD_moveCursor(0, 7);
			LCD_displayString("ON");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1, 8);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');

		} else if (temp >= 90 && temp < 120) {
			/*Turn ON the fan with 75% of its maximum speed*/
			DcMotor_Rotate(1, 75);

			/*Update the LCD*/
			LCD_moveCursor(0, 7);
			LCD_displayString("ON");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1, 8);
			LCD_intgerToString(temp);
			LCD_displayCharacter('  ');

		} else if (temp >= 120) {
			/*Turn ON the fan with 100% of its maximum speed*/
			DcMotor_Rotate(1, 100);

			/*Update the LCD*/
			LCD_moveCursor(0, 7);
			LCD_displayString("ON");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1, 8);
			LCD_intgerToString(temp);
			LCD_displayCharacter('  ');

		}

		temp = LM35_getTemperature();

	}
	return 0;
}
