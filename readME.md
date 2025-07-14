# EMG Acquisition System using ADS1299 and ESP32

Sistema di acquisizione dati EMG da 8 canali basato sul convertitore ADC **ADS1299** e il microcontrollore **ESP32**, utilizzando comunicazione SPI.  
Il codice permette di configurare i registri dell'ADS1299, avviare l'acquisizione in tempo reale e leggere i dati grezzi per applicazioni biomediche.

---

## 📂 File inclusi

- `ads1299.cpp / ads1299.h`  
  Funzioni di configurazione dell’ADS1299, gestione dei registri, comandi SPI, lettura dei dati in modalità continua.

- `spi_ads1299.cpp / spi_ads1299.h`  
  Funzioni per la comunicazione SPI su ESP32 (basate su `SPIClass`), inclusi i segnali di controllo (CS, START, RESET, DRDY, ecc.).

- `main.ino`  
  Programma principale per inizializzare l’ADS1299, avviare l’acquisizione continua e stampare i dati su seriale.

---

## ⚙️ Funzionalità

- Inizializzazione ADS1299 (power-up e reset)
- Configurazione dei registri (CONFIG1, CONFIG2, CHnSET, ecc.)
- Frequenza di campionamento selezionabile
- Modalità RDATAC per lettura continua
- Lettura dei dati grezzi da 8 canali
- Gestione diretta dei segnali digitali `START`, `PWDN`, `CS`, `DRDY`, `RESET`

---

## 🔌 Collegamenti hardware (ESP32)

| Segnale ADS1299 | Pin ESP32 (esempio) |
|------------------|---------------------|
| `MISO`           | 19                  |
| `MOSI`           | 23                  |
| `SCLK`           | 18                  |
| `CS`             | 10                   |
| `DRDY`           | 2                   |
| `START`          | 7                  |
| `PWDN`           | 8                   |
| `RESET`          | 9                  |

> I pin sono configurabili nei file `spi_ads1299.h` e `ads1299.h`.

---

## 🚀 Istruzioni per l’uso

1. Clona la repository:
   ```bash
   git clone https://github.com/tuo-username/emg-ads1299.git
   cd emg-ads1299
