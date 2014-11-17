Arduino-LTC6904-Library
=======================

# Arduino library for Linear Technologies LTC6904 I2C programmable oscillator

## Member Functions

```
LTC6904(int ADR)
LTC6904(int ADR, float freq_kHz)
void settings(uint8_t setting)
uint8_t setFrequency(float freq_kHz)
uint8_t manuallySetReg(uint8_t oct, uint8_t dac_code)
void setADR(int ADR)
uint8_t getAddress()
float getFreq()
uint8_t getOutputCfg()
```

## Basic Usage
### Example 1
```
// This assumes you've configured Wire
// creates an instance of LTC6904
myosc = LTC6904(0);
// set the ocs frequency to 4.25 kHz
myosc.setFrequency(4.25); 
```

### Example 2
```
// This assumes you've configured Wire
// creates an instance of LTC6904
myosc = LTC6904(0);
// sets the output mode to LTC6904_CLK_ON_CLK_INV_OFF
myosc.settings(2);
// set the ocs frequency to 100.5 kHz
myosc.setFrequency(100.5); 
```


