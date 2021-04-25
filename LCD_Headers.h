/*
 * LCD_Headers.h
 *
 *  Created on: April 9, 2021
 *      Author: Bradley Shelley
 */



#ifndef LCD_HEADERS_H_
#define LCD_HEADERS_H_

// Configures LCD for writing function
void LCD_SPI_INIT();


// Resets LCD cursor back to Home location
void LCD_Command_Home();

// Clears the LCD's screen
void LCD_Command_Clear();


// Jumps to Next Line on LCD
void LCD_Command_Next_Line();

// Writes the characters passed to function to LCD
void LCD_Write(char words[]);
#endif
