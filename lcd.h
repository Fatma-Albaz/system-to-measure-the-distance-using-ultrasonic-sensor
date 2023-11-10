/*
 * lcd.h
 *
 *  Created on: Oct 3, 2023
 *      Author: fatma albaz
 */

#ifndef LCD_H_
#define LCD_H_
#include "std_types.h"

/****************************************************************************************************
 * 										Definitions													*
 ****************************************************************************************************/

#define LCD_NUM_OF_ROWS     2
#define LCD_NUM_OF_COLS     16

#define LCD_ROW0_ID  		0
#define LCD_ROW1_ID  		1
#define LCD_ROW2_ID  		2
#define LCD_ROW3_ID  		3

#define LCD_COL0_ID  		0
#define LCD_COL1_ID  		1
#define LCD_COL2_ID  		2
#define LCD_COL3_ID  		3
#define LCD_COL4_ID  		4
#define LCD_COL5_ID  		5
#define LCD_COL6_ID  		6
#define LCD_COL7_ID  		7
#define LCD_COL8_ID  		8
#define LCD_COL9_ID  		9
#define LCD_COL10_ID  		10
#define LCD_COL11_ID  		11
#define LCD_COL12_ID  		12
#define LCD_COL13_ID  		13
#define LCD_COL14_ID  		14
#define LCD_COL15_ID  		15


/*LCD commands required*/
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80


/****************************************************************************************************
 * 										Function Prototypes											*
 ****************************************************************************************************/
void LCD_init(void);
void LCD_sendCommand (uint8 command);
void LCD_displayChar (const uint8 char_value);
void LCD_displayString (const uint8 * string_ptr);
void LCD_moveCursor(uint8 row, uint8 column);
void LCD_displyStringRowColumns(uint8 row, uint8 column, const uint8 *data);
void LCD_clearScreen (void);
void LCD_intToStringDisplay (sint16 data);



#endif /* LCD_H_ */
