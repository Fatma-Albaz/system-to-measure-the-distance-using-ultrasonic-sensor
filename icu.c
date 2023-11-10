/*
 * ICU.c
 *
 *  Created on: Oct 15, 2023
 *      Author: fatma albaz
 */

#include "icu.h"
#include "gpio.h"
#include "icu_private.h"
//#include <avr/io.h>
#include <avr/interrupt.h>
#include "common_macros.h"
/****************************************************************************************
 * 									  	definitions										*
 ****************************************************************************************/
static volatile void(*g_varToCallBackFunction)(void) =NULL;
/****************************************************************************************
 * 								  Function declarations									*
 ****************************************************************************************/
/*
 * this function is to initiate the ICU on the MCU
	 * select mode of the timer :OVF mode
	 * select the edge type
	 * select the required clock
	 * select the timer and ICU register initial values
	 * enable the ICU interrupt
 * this function is configurable for any required initial settings
 */
void ICU_init(const ICU_ConfigType * configuration){
	/*Input signal is at PD6 "input direction" */
	GPIO_setupPinDirection(PORTD_ID,PIN6_ID,PIN_INPUT);
	/*
	 * Timer1 must be in overflow mode to be able to count on a higher range
	 * this mode gives the advantage of counting a larger time period
	 */
	TCCR1A=(1<<FOC1A)|(1<<FOC1B);
	/*
	 * Input Capture Noise Canceler is enabled
	 */
	SET_BIT(TCCR1B,ICNC1);
	/*insert the edge type in the ICES1 bit inside TCCR1B register*/
	TCCR1B = (TCCR1B&0xBF)|((configuration->edge)<<ICES1);
	/*insert the selected clock at bits 0,1,2 in TCCR1B register*/
	TCCR1B = (TCCR1B&0xF8)|((configuration->clk));
	/*put initial values in the registers*/
	TCNT1=0;
	/*initial value for the ICU register*/
	ICR1=0;
	/*interrupt capture unit enable*/
	SET_BIT(TIMSK,TICIE1);
}
/*
 * the edge may be changed by this function
 * this function receives the required edge as a function argument and inserts it inside the TCCR1B register
 */
void ICU_setEdgeDetectionType (const ICU_EdgeType new_edge){
	/*insert the edge type in the ICES1 bit inside TCCR1B register*/
	TCCR1B = (TCCR1B&0xBF)|(new_edge<<ICES1);
}
/*
 * this function returns the value of the ICU unit stored in the ICR1 register
 */
uint16 ICU_getInputCaptureValue (void){
	/*ICR1 is the register that contains the value of the ICU when an interrupt happens*/
	return ICR1;
}
/*
 * this function is used to reset the timer value to zero
 */
void ICU_clearTimerValue(void){
	/*put initial values in the registers*/
	TCNT1=0;
}
/*
 * this function receives the function name that will be executed when the ISR is called
 * as a reaction of rising the flag..
 * the name of the function is stored in a pointer to function
 */
void ICU_setCallBack(void(*local_ptrToCallBack)(void) ){
	g_varToCallBackFunction=local_ptrToCallBack;
}
/*
 * this function is used to deinit the ICU by de-initiating
 * the timer and ICU registers
 */
void ICU_deInit (void){
	/* Clear All Timer1/ICU Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TICIE1);

	/* Reset the global pointer value */
	g_varToCallBackFunction = NULL;
}
ISR(TIMER1_CAPT_vect){
	/*call the callback function using the global pointer to function*/
	if (g_varToCallBackFunction!=NULL){
		g_varToCallBackFunction();
	}
}

