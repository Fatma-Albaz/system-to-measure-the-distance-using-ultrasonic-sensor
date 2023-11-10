/*
 * gpio_registers.h
 *
 *  Created on: Oct 2, 2023
 *      Author: fatma albaz
 */

#ifndef GPIO_REGISTERS_H_
#define GPIO_REGISTERS_H_
#include "std_types.h"
/*typedef union
{
	uint8 Byte;
	struct
	{
		uint8 Bit0:1;
		uint8 Bit1:1;
		uint8 Bit2:1;
		uint8 Bit3:1;
		uint8 Bit4:1;
		uint8 Bit5:1;
		uint8 Bit6:1;
		uint8 Bit7:1;
	}Bits;
}Reg_8bit;
*/
#define PORTA  (*(volatile uint8 * const )0x003B)
#define DDRA   (*(volatile uint8 * const )0x003A)
#define PINA   (*(volatile uint8 const * const )0x0039)

#define PORTB  (*(volatile uint8 * const )0x0038)
#define DDRB   (*(volatile uint8 * const )0x0037)
#define PINB   (*(volatile uint8 const * const )0x0036)

#define PORTC  (*(volatile uint8 * const )0x0035)
#define DDRC   (*(volatile uint8 * const )0x0034)
#define PINC   (*(volatile uint8 const * const )0x0033)

#define PORTD  (*(volatile uint8 * const )0x0032)
#define DDRD   (*(volatile uint8 * const )0x0031)
#define PIND   (*(volatile uint8 const * const )0x0030)

#endif /* GPIO_REGISTERS_H_ */
