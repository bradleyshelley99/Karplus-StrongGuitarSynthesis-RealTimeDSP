/*
 * SRAM.c
 *
 *  Created on: Apr 17, 2021
 *      Author: Brad
 */


#include "SRAM.h"


int16_t SRAM_Read(long addr){
    // Need to tell the board we are messing with GPIO

    volatile int16 LowByte;
    volatile int16 HighByte;
    volatile Uint16 garbage = 0xBB;
    if(addr <= 0x3FFFF){
        // Read from first SRAM
        // Turn off CS1
        GpioDataRegs.GPCSET.bit.GPIO66 = 1;
        // Turn on CS0
        GpioDataRegs.GPCCLEAR.bit.GPIO67 = 1;
    }

    else{
        // Read from Second SRAM
        // Turn OFF CS0
        GpioDataRegs.GPCSET.bit.GPIO67 = 1;
        // Turn ON CS1
        GpioDataRegs.GPCCLEAR.bit.GPIO66 = 1;
    }
        addr = addr & 0x3FFFF;
        SPI_TRANSMIT(0x03);
        SPI_Address(addr);
        // Write upper 2 and lower 2 bytes to the transmit SRAM
        // via SPI
        // Gotta send them left adjusted.
        // Read data in.
        SPI_TRANSMIT((garbage));
        // Actual read byte for SRAM1
        HighByte = SPI_TRANSMIT((garbage));
        LowByte = SPI_TRANSMIT(garbage);


    // Turn off chip selects so nothing is messed up.
    // Turn OFF CS0
    GpioDataRegs.GPCSET.bit.GPIO66 = 1;
    // Turn off CS1
    GpioDataRegs.GPCSET.bit.GPIO67 = 1;
    HighByte = ((HighByte & 0xFF) <<8);
    LowByte  = (LowByte & 0xFF);
    int16_t SRAMDATA = (HighByte |LowByte);
    return (SRAMDATA);
}

void SRAM_Write(long addr, int16_t data){
    // Need to tell the board we are messing with GPIO
    if(addr <= 0x3ffff){
        // Turn off CS1
        GpioDataRegs.GPCSET.bit.GPIO66 = 1;
        // Turn on CS0
        GpioDataRegs.GPCCLEAR.bit.GPIO67 = 1;
    }
    else{
        // Write to second SRAM
        // Turn OFF CS0
        GpioDataRegs.GPCSET.bit.GPIO67 = 1;
        // Turn ON CS1
        GpioDataRegs.GPCCLEAR.bit.GPIO66 = 1;
    }
        addr = addr & 0x3FFFF;
        SPI_TRANSMIT(0x02);
        SPI_Address(addr);
        SPI_TRANSMIT((data & 0xFF00)>>8);
        SPI_TRANSMIT((data & 0x00FF));

        // Turn off chip selects so nothing is messed up.
        // Turn OFF CS0
        GpioDataRegs.GPCSET.bit.GPIO66 = 1;
        // Turn off CS1
        GpioDataRegs.GPCSET.bit.GPIO67 = 1;
}

void SPI_Address(Uint32 Addr){
    // The way I've set this up
    // When the address is over 256k
    // The next SRAM will be kicked on
    // and it can be indexed as 512k x 8
    // Memory. Thus anything over 3FFFF
    // is not the correct memory location
    // for the vertical alignment of this SRAM
    // Config
    //volatile Uint32 Caddr =Addr;
    // Transmit Address
    //SPI_TRANSMIT(Caddr >> 16);
   // Addr = (Addr & 0x3FFFF);
    SPI_TRANSMIT(Addr >> 16);
    //  SPI_TRANSMIT(Caddr >> 8)
    SPI_TRANSMIT((Addr & 0xFF00)>>8);
    //SPI_TRANSMIT((Caddr & 0x00FF00) >> 4);
    SPI_TRANSMIT((Addr & 0xFF));
    //SPI_TRANSMIT((Caddr & 0xFF));
}

int16_t SPI_TRANSMIT(int16_t Sdata){
    while(SpibRegs.SPISTS.bit.BUFFULL_FLAG ==1); // Poll buffer
    SpibRegs.SPIDAT = (Sdata<<8);
    // Wait for it to send and be done
    while(SpibRegs.SPISTS.bit.INT_FLAG ==0);
    volatile int16_t ShiftData = SpibRegs.SPIRXBUF;
    return ShiftData;
}

