#include "spi_ads1299.h"
#define SPI_FREQUENCY 8000000 //modifica fino a 8MHz
SPIClass SPIbus(SPI); 
// **Inizializzazione SPI**
void SPI_init() {
    SPIbus.begin(PIN_SCK, PIN_MISO, PIN_MOSI);  
    SPIbus.setDataMode(SPI_MODE1);  // Forza SPI Mode 0 per il test loopback
    SPIbus.setBitOrder(MSBFIRST);
    //SPIbus.setClockDivider(SPI_CLOCK_DIV8); //inutile togliere

    pinMode(PIN_CS, OUTPUT);
    CS_disable();
}

// **Abilita il Chip Select (CS)**
void CS_enable() {
    digitalWrite(PIN_CS, LOW);
}

// **Disabilita il Chip Select (CS)**
void CS_disable() {
    digitalWrite(PIN_CS, HIGH);
}

uint8_t spiWrite(uint8_t data) {
    SPIbus.beginTransaction(SPISettings(SPI_FREQUENCY, MSBFIRST, SPI_MODE1));  
    uint8_t received = SPIbus.transfer(data);
    SPIbus.endTransaction();
    //delayMicroseconds(10);  // Aggiungi un ritardo tra le operazioni, toglilo e prova di nuovo
    return received;
}
