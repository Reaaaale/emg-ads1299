#include "ads1299.h"

// **Configurazione ADS1299**
void configADS() {
    uint8_t byte2TX;

    // Configura i pin
    pinMode(PIN_RST, OUTPUT);
    pinMode(PIN_PWDN, OUTPUT);
    pinMode(PIN_START, OUTPUT);
    pinMode(PIN_DRDY, INPUT);

    // Reset ADS1299
    digitalWrite(PIN_RST, LOW);
    delay(1);
    digitalWrite(PIN_RST, HIGH);
    delay(100);

    // Alimentazione ADS1299
    digitalWrite(PIN_PWDN, HIGH);
    delay(1000);

    // Abilita SPI
    CS_enable();
    delay(1000);

    // Comando SDATAC (Stop Read Continuous)
    spiWrite(0x11);
    delayMicroseconds(3);

    // Configura CONFIG3 (Abilita riferimento interno)
    spiWrite(0x43); delayMicroseconds(3);
    spiWrite(0x00); delayMicroseconds(3);
    spiWrite(0xEC); delayMicroseconds(3); //prova E8

    // Configurazione CONFIG1 (1000 SPS)
    spiWrite(0x41); delayMicroseconds(3);
    spiWrite(0x00); delayMicroseconds(3);
    spiWrite(0xD4); delayMicroseconds(3);

    // Configurazione CONFIG2 
    spiWrite(0x42); delayMicroseconds(3);
    spiWrite(0x00); delayMicroseconds(3);
    spiWrite(0xD3); delayMicroseconds(3);

    // Configurazione i canali (CHnSET)
    spiWrite(0x45); delayMicroseconds(3);
    spiWrite(0x07); delayMicroseconds(3);

    // Imposta l'input cortocircuitato per la misurazione dell'offset
    for (int i = 0; i < 8; i++) {
        spiWrite(0x05);
        delayMicroseconds(3);
    }

    CS_disable();
}

// **Lettura dati da ADS1299**
int readRDATAC(uint8_t *data, uint8_t *statusBYTE) {
    while (digitalRead(PIN_DRDY) == HIGH);

    CS_enable();
    *statusBYTE = spiWrite(0x00);
    delayMicroseconds(3);

    uint8_t buffer[24];
    for (int i = 0; i < 24; i++) {
        buffer[i] = spiWrite(0x00);
        delayMicroseconds(3);
    }

    CS_disable();
    memcpy(data, buffer, 24);
    return 24;
}

void printBinary(uint32_t num) {
    for (int i = 31; i >= 0; i--) {
        Serial.print((num >> i) & 1);  // Stampa bit per bit
        if (i % 8 == 0) Serial.print(" ");  // Aggiungi uno spazio ogni 8 bit per leggibilità
    }
}

void readAllRegister (uint8_t *data){
    CS_enable();
    spiWrite(0x20); //RREG
    delayMicroseconds(3);
    spiWrite(0x17); //Numero di registri da leggere 
    delayMicroseconds(3);

    for (int i = 0; i < 24; i++) {
        data[i] = spiWrite(0x00);
        delayMicroseconds(3);
    }

    CS_disable();
}
void readADS1299Data(int32_t *channelData, uint32_t *status) {
    uint8_t byteReceived;

    // Attendi che DRDY diventi LOW (significa che i dati sono pronti)
    while (digitalRead(PIN_DRDY) == HIGH);

    CS_enable();

    // Lettura dello STATUS (3 byte, PRIMO ADS)
    *status = 0;
    for (uint8_t i = 0; i < 3; i++) {
        byteReceived = spiWrite(0x00);
        *status = (*status << 8) | byteReceived;
    }

    // Lettura dei dati dei canali (8 canali * 3 byte, PRIMO ADS)
   for (uint8_t i = 0; i < 8; i++) {
    byteReceived = spiWrite(0x00);  // Primo byte (MSB)
    channelData[i] = ((int32_t)byteReceived << 16);

    byteReceived = spiWrite(0x00);  // Secondo byte (Middle Byte)
    channelData[i] |= ((int32_t)byteReceived << 8);

    byteReceived = spiWrite(0x00);  // Terzo byte (LSB)
    channelData[i] |= ((int32_t)byteReceived);

    // Estende il segno per dati a 24 bit
    if (channelData[i] & 0x800000) {
        channelData[i] |= 0xFF000000;  // Estensione del segno per numeri negativi
    }
}

    // Lettura e scarto dei byte del SECONDO ADS1299 (27 byte)
    for (uint8_t i = 0; i < 27; i++) {
        spiWrite(0x00);  // Ricevi e ignora
    }

    CS_disable();
}

void configRDATAC() {
    digitalWrite(PIN_START, HIGH);  // Porta il pin START alto per avviare la conversione
    CS_enable();
    spiWrite(0x10);  // Comando RDATAC
    CS_disable();
}
void stopRDATAC() {
    digitalWrite(PIN_START, LOW);  // Ferma la conversione
    CS_enable();
    spiWrite(0x11);  // Comando STOP RDATAC
    delayMicroseconds(4);
    CS_disable();
}

void configADS_channelData() {
    uint8_t byte2TX;

    // Configura i pin
    pinMode(PIN_RST, OUTPUT);
    pinMode(PIN_PWDN, OUTPUT);
    pinMode(PIN_START, OUTPUT);
    pinMode(PIN_DRDY, INPUT);

    // Reset ADS1299
    digitalWrite(PIN_RST, LOW);
    delay(1);
    digitalWrite(PIN_RST, HIGH);
    delay(100);

    // Alimentazione ADS1299
    digitalWrite(PIN_PWDN, HIGH);
    delay(1000);

    // Abilita SPI
    CS_enable();
    delay(1000);

    // Comando SDATAC (Stop Read Continuous)
    spiWrite(0x11);
    delayMicroseconds(3);

    // Configura CONFIG3 (Abilita riferimento interno)
    spiWrite(0x43); delayMicroseconds(3);
    spiWrite(0x00); delayMicroseconds(3);
    spiWrite(0xEC); delayMicroseconds(3); //prova E8

    // Configura CONFIG1 (1000 SPS)
    spiWrite(0x41); delayMicroseconds(3);
    spiWrite(0x00); delayMicroseconds(3);
    spiWrite(0x94); delayMicroseconds(3);

    // Configura CONFIG2 (Impostazioni default)
    spiWrite(0x42); delayMicroseconds(3);
    spiWrite(0x00); delayMicroseconds(3);
    spiWrite(0xD3); delayMicroseconds(3);

    // Configura i canali (CHnSET)
spiWrite(0x45); // WREG starting from CH1SET
delayMicroseconds(3);
spiWrite(0x07); // scrivo su 8 registri consecutivi (CH1SET → CH8SET)
delayMicroseconds(3);

// CH1 = 0x00 (normal electrode input), CH2-CH8 = 0x05 (test signal)
for (int i = 0; i < 8; i++) {
  if (i == 0) {
    spiWrite(0b01100000);  // CH1: gain=24, ingresso normale
  } else {
    spiWrite(0x81);  // CH2–CH8: ingresso corto (disattivati)
  }
  delayMicroseconds(3);
}


    CS_disable();




}


void enableBiasOnCH1() {
    // 1. Aggiungi solo CH1P al circuito BIAS_SENSP
    spiWrite(0x4C);               // WREG BIAS_SENSP (0x0C | 0x40 = 0x4C)
    delayMicroseconds(3);
    spiWrite(0x00);               // 1 registro
    delayMicroseconds(3);
    spiWrite(0x01);               // 00000001 = solo CH1P ON

    // 2. Aggiungi solo CH1N al circuito BIAS_SENSN
    spiWrite(0x4D);               // WREG BIAS_SENSN (0x0D | 0x40 = 0x4D)
    delayMicroseconds(3);
    spiWrite(0x00);
    delayMicroseconds(3);
    spiWrite(0x01);               // 00000001 = solo CH1N ON

    // 3. Disabilita SRB1 se attivo
    spiWrite(0x55);               // WREG SRB1
    delayMicroseconds(3);
    spiWrite(0x00);
    delayMicroseconds(3);
    spiWrite(0x00);               // Disabilita SRB1 su tutti i canali

    // 4. Disattiva SRB1 globale (bit 5) in MISC1
    spiWrite(0x4A);               // WREG MISC1
    delayMicroseconds(3);
    spiWrite(0x00);
    delayMicroseconds(3);
    spiWrite(0x00);               // Bit SRB1 globale disattivato
}

