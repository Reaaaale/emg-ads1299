#ifndef SPI_ADS1299_H
#define SPI_ADS1299_H

#include <Arduino.h>
#include <SPI.h>
#include <SPI.h>

extern SPIClass SPIbus;


#define PIN_MOSI 23
#define PIN_MISO 19
#define PIN_SCK  18
#define PIN_CS   10  // Chip Select (CS)

// Funzioni SPI
void SPI_init();
void CS_enable();
void CS_disable();
uint8_t spiWrite(uint8_t data);

#endif