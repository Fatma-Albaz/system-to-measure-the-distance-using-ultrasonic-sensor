/*
 * ultrasonic.c
 *
 *  Created on: Oct 16, 2023
 *      Author: fatma albaz
 */

#include "ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include <util/delay.h>
/*global variables declarations*/
static volatile uint16 g_valueOfTime=0;
static volatile uint8 g_counter=0;
/************************************************************************************************
 * 										FUNCTION DECLARATIONS								    *
 ************************************************************************************************/
/*
 * function description:
 * this function is used to initiate the ultrasonic driver
 * Initialize the ICU driver as required.
 * Setup the ICU call back function.
 * Setup the direction for the trigger pin as output pin through the GPIO driver.
 */
void Ultrasonic_init(void){
	/*
	 * initialization of the ICU driver
	 */
	ICU_ConfigType configuration;
	configuration.clk=F_CPU_8;
	configuration.edge=RISING;
	ICU_init(&configuration);
	/*
	 * setup the ICU callback function
	 */
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,PIN_OUTPUT);
	/*this step is done at the ICU driver
	 * GPIO_setupPinDirection(ULTRASONIC_ECHO_PORT_ID,ULTRASONIC_ECHO_PIN_ID,PIN_INPUT);
	 */
}
/*
 * Function description:
 * this function is used to send the trigger pulse for the trigger pin
 * the trigger pulse is high at least for 10 micro seconds
 * this is done by producing a high value on the pin then delay for 15 micro
 * seconds and then return the pin value to low
 */
void Ultrasonic_Trigger(void){
	/*
	 * Sending the trigger pulse for the trigger pin
	 */
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_HIGH);
	_delay_us(15);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_LOW);
}
/*
 * the distance range of the ultrasonic is from 2cm :400cm
 * so the distance data type will be uint16
 * the distance is equal to the speed* time
 * time is measured from the function Ultrasonic_edgeProcessing
 * speed is the speed of sound 340 m/s
➢ Send the trigger pulse by using Ultrasonic_Trigger function.
➢ Start the measurements by the ICU from this moment.
 */
uint16 Ultrasonic_readDistance(void){
	Ultrasonic_Trigger();
	uint16 distance=0;
	while (g_counter!=2);
	g_counter=0;
	distance= (uint16)((float32)g_valueOfTime / 57.8);
	return distance;
}
/*
 * this function is called when an interrupt request is initiated (the required edge is detected)
➢ This is the call back function called by the ICU driver.
➢ This is used to calculate the high time (pulse time) generated by
the ultrasonic sensor.
 */
void Ultrasonic_edgeProcessing(void){
	g_counter++;
	if (g_counter==1){
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);
	}
	else if (g_counter==2){
		g_valueOfTime=ICU_getInputCaptureValue();
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(RISING);
	}
}