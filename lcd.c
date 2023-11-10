/*
 * lcd.c
 *
 *  Created on: Oct 3, 2023
 *      Author: fatma albaz
 */
#include "lcd.h"
#include "lcd_private.h"
#include "common_macros.h"
#include "gpio.h"
#include <util/delay.h>
/****************************************************************************************************
 * 									Function Definitions											*
 ****************************************************************************************************/
void LCD_init(void){
	/*set RS and e pins as output*/
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);
	/*delay for 20 milli seconds to make sure that*/
	_delay_ms(20);
#if (LCD_DATA_BITS_MODE== LCD_4BITS_MODE)
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,PIN_OUTPUT);
	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
#endif

	/*data port is set as output*/
#if (LCD_DATA_BITS_MODE== LCD_8BITS_MODE)
	GPIO_setupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT);
	/*sending commands*/
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);/*2lines +8 bit mode*/
#endif
	LCD_sendCommand(LCD_CURSOR_OFF);/*cursor off*/
	LCD_sendCommand(LCD_CLEAR_COMMAND);/*clear screen*/
}


void LCD_sendCommand (uint8 command){
	/*Rs is equal to zero "a command is sent"*/
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW);
	/* delay for 1 micro sec*/
	_delay_ms(1);
	/* set enable by 1	 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	/* delay for 1 micro sec	 */
	_delay_ms(1);
#if (LCD_DATA_BITS_MODE== LCD_4BITS_MODE)
	/*from data sheet send MSB first*/
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,7));
	_delay_ms(1);
	/* clear enable by 0		 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	/* delay for 1 micro sec	 */
	_delay_ms(1);
	/* clear enable by 0		 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	/* delay for 1 micro sec	 */
	_delay_ms(1);
	/*from data sheet send LSB second*/
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,3));
	_delay_ms(1);
	/* clear enable by 0		 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
#elif(LCD_DATA_BITS_MODE== LCD_8BITS_MODE)
	/* send the required command */
	GPIO_writePort(LCD_DATA_PORT_ID,command);
	/* delay for 1 micro sec	 */
	_delay_ms(1);
	/* clear enable by 0		 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	/* delay for 1 micro sec	 */
	_delay_ms(1);
#endif
}


void LCD_displayChar (const uint8 char_value){
	/*Rs is equal to ONE "a command is sent"*/
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH);
	/* delay for 1 micro sec*/
	_delay_ms(1);
	/* set enable by 1	 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	/* delay for 1 micro sec	 */
	_delay_ms(1);
#if (LCD_DATA_BITS_MODE== LCD_4BITS_MODE)
	/*from data sheet send MSB first*/
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(char_value,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(char_value,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(char_value,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(char_value,7));
	_delay_ms(1);
	/* clear enable by 0		 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	/* delay for 1 micro sec	 */
	_delay_ms(1);
	/* clear enable by 0		 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	/* delay for 1 micro sec	 */
	_delay_ms(1);
	/*from data sheet send LSB second*/
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(char_value,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(char_value,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(char_value,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(char_value,3));
	_delay_ms(1);
	/* clear enable by 0		 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
#elif(LCD_DATA_BITS_MODE== LCD_8BITS_MODE)
	/* send the required command */
	GPIO_writePort(LCD_DATA_PORT_ID,char_value);
	/* delay for 1 micro sec	 */
	_delay_ms(1);
	/* clear enable by 0		 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	/* delay for 1 micro sec	 */
	_delay_ms(1);
#endif
}
void LCD_displayString (const uint8 * string_ptr){
	uint8 loop_iterator=0;
	for(loop_iterator=0; string_ptr[loop_iterator]!= '\0';loop_iterator++){
		LCD_displayChar(string_ptr[loop_iterator]);
	}
}




void LCD_moveCursor(uint8 row, uint8 column){
	uint8 lcd_locationRequired=0;
	if ((row>=LCD_NUM_OF_ROWS)||(column>=LCD_NUM_OF_COLS)){
		/*
		 * do nothing
		 */
	}
	else{
		switch (row){
		case LCD_ROW0_ID:
			lcd_locationRequired= LCD_ROW0_FIRST_LOCATION_ID+column;
			break;
		case LCD_ROW1_ID:
			lcd_locationRequired= LCD_ROW1_FIRST_LOCATION_ID+column;
			break;
		case LCD_ROW2_ID:
			lcd_locationRequired= LCD_ROW2_FIRST_LOCATION_ID+column;
			break;
		case LCD_ROW3_ID:
			lcd_locationRequired= LCD_ROW3_FIRST_LOCATION_ID+column;
			break;
		}
	}
	LCD_sendCommand(lcd_locationRequired|LCD_SET_CURSOR_LOCATION);
}


void LCD_displyStringRowColumns(uint8 row, uint8 column,const uint8 *data){
	LCD_moveCursor(row,column);
	LCD_displayString(data);
}

void LCD_clearScreen(void){
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}
void LCD_intToStringDisplay (sint16 data){
	uint8 arrOfStrings [16];
	//	uint8 loopOneIterator =0, loopTwoIterator;
	//	uint32 copyOfData=data;
	//	while (copyOfData!=0){
	//		loopOneIterator++;
	//		copyOfData/=10;
	//	}
	//	for (loopTwoIterator=loopOneIterator-1; loopTwoIterator>=0;loopTwoIterator--){
	//		arrOfStrings[loopTwoIterator]= (data%10)+48;
	//		data/=10;
	//	}
	//	arrOfStrings[loopOneIterator]='\0';
	itoa(data,arrOfStrings,10);
	LCD_displayString(arrOfStrings);
}

