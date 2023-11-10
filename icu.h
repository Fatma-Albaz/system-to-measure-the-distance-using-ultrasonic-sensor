/*
 * icu.h
 *
 *  Created on: Oct 15, 2023
 *      Author: fatma albaz
 */

#ifndef ICU_H_
#define ICU_H_
#include "std_types.h"
typedef enum{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}ICU_EdgeType;

typedef enum{
	FALLING,RISING
}ICU_ClockType;

typedef struct{
	ICU_ClockType clk;
	ICU_EdgeType  edge;
}ICU_ConfigType;

/****************************************************************************************
 * 									Function prototypes									*
 ****************************************************************************************/
/*
 * this function is used to deinit the ICU by de-initiating
 * the timer and ICU registers
 */
void ICU_deInit (void);
/*
 * this function is used to reset the timer value to zero
 */
void ICU_clearTimerValue(void);
/*
 * this function returns the value of the ICU unit stored in the ICR1 register
 */
uint16 ICU_getInputCaptureValue (void);
/*
 * this function is to initiate the ICU on the MCU
	 * select mode of the timer :OVF mode
	 * select the edge type
	 * select the required clock
	 * select the timer and ICU register initial values
	 * enable the ICU interrupt
 * this function is configurable for any required initial settings
 */
void ICU_init(const ICU_ConfigType * configuration);
/*
 * this function receives the function name that will be executed when the ISR is called
 * as a reaction of rising the flag..
 * the name of the function is stored in a pointer to function
 */
void ICU_setCallBack(void(*local_ptrToCallBack)(void));
/*
 * the edge may be changed by this function
 * this function receives the required edge as a function argument and inserts it inside the TCCR1B register
 */
void ICU_setEdgeDetectionType (const ICU_EdgeType new_edge);

#endif /* ICU_H_ */
