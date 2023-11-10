/*
 * main_file.c
 *
 *  Created on: Oct 16, 2023
 *      Author: fatma albaz
 */

#include "lcd.h"
#include "ultrasonic.h"
#include <avr/interrupt.h>
#include <avr/io.h>/*to enable global interrupts*/
/*
 * this function is used to display the required distance on the LCD
 * the included if conditions assures that there is no overwriting on
 * displayed results
 * the distance is passed as a function argument and valued by cm unit
 */
void display_On_LCD (uint16 distance_measured);
/*
 * Implement the following system to measure the distance using ultrasonic sensor
 * HC-SR04 with the specifications listed below:
 * 		1. Use ATmega32 Microcontroller with frequency 8Mhz.
 * 		2. Measure the distance using the Ultrasonic sensor HC-SR04.
 * 		3. The LCD should display the distance value.
 */
int main (void){
	uint16 distance_measured=0;
	LCD_init();/*initiate the lcd*/
	Ultrasonic_init();/*initiate the ultrasonic sensor*/
	LCD_displayString("Distance= ");
	SREG |= (1<<7);/*enable global interrupts*/
	while (1){
		distance_measured=Ultrasonic_readDistance();
		display_On_LCD(distance_measured);
	}
	return 0;
}
/*
 * this function is used to display the required distance on the LCD
 * the included if conditions assures that there is no overwriting on
 * displayed results
 * the distance is passed as a function argument and valued by cm unit
 */
void display_On_LCD (uint16 distance_measured){
	LCD_moveCursor(0,10);
			if (distance_measured>100){
				LCD_intToStringDisplay(distance_measured);
				LCD_displayString("cm");
			}
			else if  (distance_measured>10){
				LCD_intToStringDisplay(distance_measured);
				LCD_displayString(" cm");
			}
			else{
				LCD_intToStringDisplay(distance_measured);
				LCD_displayString("  cm");
			}
}
