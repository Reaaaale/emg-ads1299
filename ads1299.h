#ifndef ADS1299_H
#define ADS1299_H

#include "spi_ads1299.h"

// Definizione dei pin di controllo ADS1299
#define PIN_RST   9   // Reset
#define PIN_PWDN  8   // Power Down
#define PIN_START 7   // Start Conversion
#define PIN_DRDY  2   // Data Ready (DRDY)

// Funzioni per ADS1299
void configADS();
int readRDATAC(uint8_t *data, uint8_t *statusBYTE);
void readAllRegister (uint8_t *data);
void readADS1299Data(int32_t *channelData, uint32_t *status);
void configRDATAC();
void stopRDATAC();
void printBinary(uint32_t num);
void configADS_channelData();
void enableBiasOnCH1();
#endif
