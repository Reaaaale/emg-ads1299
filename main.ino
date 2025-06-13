#include "ads1299.h"

#define NUM_CHANNELS 8
#define DEBUG_MODE false  // true: stampa SPS, false: invia dati binari

unsigned long counter = 0;
unsigned long lastPrint = 0;

void setup() {
    Serial.begin(2000000);
    SPI_init();
    //configADS();
    configADS_channelData();  // Frequenza di campionamento impostata nei registri
    enableBiasOnCH1();
    configRDATAC();
}

void loop() {
    if (digitalRead(PIN_DRDY) == LOW) { //modifica
        int32_t raw[NUM_CHANNELS];
        uint32_t status;
        readADS1299Data(raw, &status);

        float VREF = 4.5;
        int GAIN = 1;
        long FULL_SCALE = 8388608;
        float voltages[NUM_CHANNELS];

        for (int i = 0; i < NUM_CHANNELS; i++) {
            voltages[i] = (float)raw[i] * VREF / (FULL_SCALE * GAIN);
        }

        if (!DEBUG_MODE) {
            Serial.write((uint8_t *)voltages, sizeof(voltages));  // 8 x 4 = 32 byte
        }

        counter++;

        unsigned long now = millis();
        if (DEBUG_MODE && (now - lastPrint >= 1000)) {
            Serial.printf("SPS: %lu\n", counter);
            counter = 0;
            lastPrint = now;
        }
    }
}
