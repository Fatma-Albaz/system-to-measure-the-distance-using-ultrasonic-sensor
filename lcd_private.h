/*
 * lcd_private.h
 *
 *  Created on: Oct 5, 2023
 *      Author: fatma albaz
 */

#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_
/****************************************************************************************************
 * 										Definitions													*
 ****************************************************************************************************/

/*Pins and ports configurations */
#define LCD_DATA_BITS_MODE             LCD_8BITS_MODE
#define LCD_4BITS_MODE				   4
#define LCD_8BITS_MODE				   8

#if ((LCD_DATA_BITS_MODE!=LCD_4BITS_MODE)&&(LCD_DATA_BITS_MODE!=LCD_8BITS_MODE))
#error "non defined bit mode (must be 4 or 8)"
#endif

#define LCD_RS_PORT_ID 				   PORTB_ID
#define LCD_RS_PIN_ID                  PIN0_ID

#define LCD_E_PORT_ID                  PORTB_ID
#define LCD_E_PIN_ID                   PIN1_ID

#define LCD_DATA_PORT_ID               PORTA_ID
/*on the 4 bit mode we only have four data bits*/
#if (LCD_DATA_BITS_MODE== LCD_4BITS_MODE)
#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN4_ID
#define LCD_DB6_PIN_ID                 PIN5_ID
#define LCD_DB7_PIN_ID                 PIN6_ID
#endif


/*first location of each row*/
#define LCD_ROW0_FIRST_LOCATION_ID  		0x00
#define LCD_ROW1_FIRST_LOCATION_ID   		0x40
#define LCD_ROW2_FIRST_LOCATION_ID   		0x10
#define LCD_ROW3_FIRST_LOCATION_ID   		0x50


#endif /* LCD_PRIVATE_H_ */
