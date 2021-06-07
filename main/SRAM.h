/*
 * SRAM.h
 *
 *  Created on: Apr 17, 2021
 *      Author: Brad
 */


#ifndef _AIC_23_H
#define _AIC_23_H

#include <F2837xD_device.h>


int16_t SRAM_Read(long addr);

void SRAM_Write(long addr, int16_t data);

void SPI_Address(Uint32 Addr);

int16_t SPI_TRANSMIT(int16_t Sdata);
















#endif
