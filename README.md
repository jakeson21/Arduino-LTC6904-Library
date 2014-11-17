Arduino-LTC6904-Library
=======================

Arduino library for Linear Technologies LTC6904 I2C programmable oscillator

Member Functions
-----------

LTC6904(int ADR)

LTC6904(int ADR, float freq_kHz)

void settings(uint8_t setting)

uint8_t setFrequency(float freq_kHz)

uint8_t manuallySetReg(uint8_t oct, uint8_t dac_code)

void setADR(int ADR)

uint8_t getAddress()

float getFreq()

uint8_t getOutputCfg()
