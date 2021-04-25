/*
 * LCD_Header.c
 *
 *  Created on: Apr 9, 2021
 *      Author: Bradley Shelley
 */

#include <F2837xD_Device.h>
#include <OneToOneI2CDriver.h>
#include "LCD_Headers.h"

#define delay_5ms() for(long t =0; t<1000000;t++)
// LCD SPI INIT
// Initializes LCD SPI protocol for use the the LCD within the DSP board.
void LCD_SPI_INIT(){
    Uint16  LCDCommand[] = {0x3C,0x38,0x3C,0x38,0x3C,0x38,0x2C,0x28,0x2C,0x28,0x8C,0x88,0x0C,0x08,0xFC,0xF8,0x0C,0x08,0x1C,0x18};
    I2C_O2O_Master_Init(0x27,200,100);
    delay_5ms();
    I2C_O2O_SendBytes(LCDCommand,20);
    delay_5ms();
    LCD_Command_Clear();
    delay_5ms();
}

// LCD Command Home
// Sends the Command Home to the LCD
void LCD_Command_Home(){
    volatile Uint16 Write_Command[] =  {0x02,0};
    Uint16 CommandBreaker;
    Uint16 HigherByte;
    Uint16 LowerByte;
    Uint16 Sent_Command[10];
   // Splits up the byte into what needs to be sent
   // for the LCD to understand
   for(int lp =0; lp<1;lp++){
       CommandBreaker = Write_Command[lp];
       HigherByte = (CommandBreaker & 0xF0);
       LowerByte = (CommandBreaker & 0x0F)<<4;
           for(int k =lp*4; k<lp*4+1; k++){
               Sent_Command[k]  = (HigherByte | 0xC);
               Sent_Command[k+1] = (HigherByte | 0x8);
               Sent_Command[k+2] = (LowerByte  | 0xC);
               Sent_Command[k+3] = (LowerByte  | 0x8);
               }
       }

   I2C_O2O_SendBytes(Sent_Command,4);
   delay_5ms();
}


// LCD Command Clear
// Sends the Command Clear to the LCD
void LCD_Command_Clear(){
    volatile Uint16 Write_Command[] =  {0x01,0};
    Uint16 CommandBreaker;
    Uint16 HigherByte;
    Uint16 LowerByte;
    Uint16 Sent_Command[10];
   // Splits up the byte into what needs to be sent
   // for the LCD to understand
   for(int lp =0; lp<1;lp++){
       CommandBreaker = Write_Command[lp];
       HigherByte = (CommandBreaker & 0xF0);
       LowerByte = (CommandBreaker & 0x0F)<<4;
           for(int k =lp*4; k<lp*4+1; k++){
               Sent_Command[k]  = (HigherByte | 0xC);
               Sent_Command[k+1] = (HigherByte | 0x8);
               Sent_Command[k+2] = (LowerByte  | 0xC);
               Sent_Command[k+3] = (LowerByte  | 0x8);
               }
       }

   I2C_O2O_SendBytes(Sent_Command,4);
   delay_5ms();
}


// LCD Command Next Line
// Sends the Command Next Line to the LCD
void LCD_Command_Next_Line(){
    volatile Uint16 Write_Command[] =  {0xC0,0};
    Uint16 CommandBreaker;
    Uint16 HigherByte;
    Uint16 LowerByte;
    Uint16 Sent_Command[10];
   // Splits up the byte into what needs to be sent
   // for the LCD to understand
   for(int lp =0; lp<1;lp++){
       CommandBreaker = Write_Command[lp];
       HigherByte = (CommandBreaker & 0xF0);
       LowerByte = (CommandBreaker & 0x0F)<<4;
           for(int k =lp*4; k<lp*4+1; k++){
               Sent_Command[k]  = (HigherByte | 0xC);
               Sent_Command[k+1] = (HigherByte | 0x8);
               Sent_Command[k+2] = (LowerByte  | 0xC);
               Sent_Command[k+3] = (LowerByte  | 0x8);
               }
       }

   I2C_O2O_SendBytes(Sent_Command,4);
   delay_5ms();
}


/******************LCD Write***************/
/* Take in String and send it to the LCD*/
void LCD_Write(char words[]){
    Uint16 STRLen = 0;
    Uint16 ByteBreaker;
    Uint16 HighByte;
    Uint16 LowByte;
    Uint16 Sent_String[100];
   // Splits up the byte into what needs to be sent
   // for the LCD to understand
        for(int lp =0; lp<100;lp++){
        ByteBreaker = words[lp];
            if(ByteBreaker == 0){
                STRLen = lp;
                break;
            }
        HighByte = (ByteBreaker & 0xF0);
        LowByte = (ByteBreaker & 0x0F)<<4;
            for(int k =lp*4; k<lp*4+1; k++){
                Sent_String[k]  = (HighByte | 0xD);
                Sent_String[k+1] = (HighByte | 0x9);
                Sent_String[k+2] = (LowByte  | 0xD);
                Sent_String[k+3] = (LowByte  | 0x9);
                }
        }
       I2C_O2O_SendBytes(Sent_String,STRLen*4);
       delay_5ms();
}
