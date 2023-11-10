/*
 * icu_private.h
 *
 *  Created on: Oct 15, 2023
 *      Author: fatma albaz
 */

#ifndef ICU_PRIVATE_H_
#define ICU_PRIVATE_H_

#define TCCR1A (*(volatile uint8  * const  )0x004F)
#define TCCR1B (*(volatile uint8  * const  )0x004E)
#define TCNT1  (*(volatile uint16 * const  )0x004C)
#define ICR1   (*(volatile uint16 * const  )0x0046)
#define TIMSK  (*(volatile uint8  * const  )0x0059)


#define WGM10 			0
#define WGM11 			1
#define FOC1B 			2
#define FOC1A 			3
#define COM1B0 			4
#define COM1B1 			5
#define COM1A0 			6
#define COM1A1 			7

#define CS10 			0
#define CS11 			1
#define CS12 			2
#define WGM12 			3
#define WGM13 			4
#define ICES1 			6
#define ICNC1 			7

#define TICIE1			5

#endif /* ICU_PRIVATE_H_ */
