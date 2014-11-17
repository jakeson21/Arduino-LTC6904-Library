/*!
An Arduino library adapted from example source code provided by
Linear Technology.

LTC6904: 1kHz to 68MHz Serial Port Programmable Oscillator

The LTC6903/LTC6904 are low power self contained digital
frequency sources providing a precision frequency from 
1kHz to 68MHz, set through a serial port. The LTC6903/
LTC6904 require no external components other than a 
power supply bypass capacitor, and they operate over a 
single wide supply range of 2.7V to 5.5V.

http://www.linear.com/product/LTC6904

*/

#ifndef LTC6904_H
#define LTC6904_H

#include <Arduino.h>
// LT6904 address options
#define LTC6904_ADDRESS_A 0x17    //!< ADR 0
#define LTC6904_ADDRESS_B 0x16     //!< ADR 1

/*!
@{ 
|   OCT Options     |   f>=  (MHz)  |   f< (MHz)    |
|   :-----------    |   :--------:  |   :-------:   |
|   LTC6904_OCT_15  |   34.05       |   68.03       |
|   LTC6904_OCT_14  |   17.02       |   34.01       |
|   LTC6904_OCT_13  |   8.5111      |   17.01       |
|   LTC6904_OCT_12  |   4.256       |   8.503       |
|   LTC6904_OCT_11  |   2.128       |   4.252       |
|   LTC6904_OCT_10  |   1.064       |   2.126       |
|   LTC6904_OCT_9   |   0.532       |   1.063       |
|   LTC6904_OCT_8   |   0.266       |   0.5314      |
|   LTC6904_OCT_7   |   0.133       |   0.2657      |
|   LTC6904_OCT_6   |   0.0665      |   0.1329      |
|   LTC6904_OCT_5   |   0.03325     |   0.06643     |
|   LTC6904_OCT_4   |   0.01662     |   0.03322     |
|   LTC6904_OCT_3   |   0.008312    |   0.01661     |
|   LTC6904_OCT_2   |   0.004156    |   0.008304    |
|   LTC6904_OCT_1   |   0.002078    |   0.004152    |
|   LTC6904_OCT_0   |   0.001039    |   0.002076    |
*/
// OCT Options
                                // f>=  (MHz)       | f< (MHz)
#define LTC6904_OCT_15  0x0F    // 34.05            | 68.03
#define LTC6904_OCT_14  0x0E    // 17.02            | 34.01
#define LTC6904_OCT_13  0x0D    // 8.5111           | 17.01
#define LTC6904_OCT_12  0x0C    // 4.256            | 8.503
#define LTC6904_OCT_11  0x0B    // 2.128            | 4.252
#define LTC6904_OCT_10  0x0A    // 1.064            | 2.126
#define LTC6904_OCT_9   0x09    // 0.532            | 1.063
#define LTC6904_OCT_8   0x08    // 0.266            | 0.5314
#define LTC6904_OCT_7   0x07    // 0.133            | 0.2657
#define LTC6904_OCT_6   0x06    // 0.0665           | 0.1329
#define LTC6904_OCT_5   0x05    // 0.03325          | 0.06643
#define LTC6904_OCT_4   0x04    // 0.01662          | 0.03322
#define LTC6904_OCT_3   0x03    // 0.008312         | 0.01661
#define LTC6904_OCT_2   0x02    // 0.004156         | 0.008304
#define LTC6904_OCT_1   0x01    // 0.002078         | 0.004152
#define LTC6904_OCT_0   0x00    // 0.001039         | 0.002076
//! @}

// Output Configuration
#define LTC6904_CLK_ON_CLK_INV_ON   0x00    //!< Clock on, inverted clock on
#define LTC6904_CLK_OFF_CLK_INV_ON  0x01    //!< Clock off, inverted clock on
#define LTC6904_CLK_ON_CLK_INV_OFF  0x02    //!< Clock on, inverted clock off
#define LTC6904_POWER_DOWN          0x03    //!< Powers down clocks


class LTC6904{
public:
	LTC6904(int ADR); // ADR=0 or ADR=1
	LTC6904(int ADR, float freq_kHz);
	void settings(uint8_t setting);
	uint8_t setFrequency(float freq_kHz);
	uint8_t manuallySetReg(uint8_t oct, uint8_t dac_code);
	void setADR(int ADR);
	uint8_t getAddress();
	float getFreq();
	uint8_t getOutputCfg();
	
private:
	//! Writes 2 bytes
	//! @return 1 if successful, 0 if failure
	uint8_t write(uint8_t address, //!< I2C address 
                      uint16_t code        //!< Code to be written
                      );
	//! Calculates the code necessary to create the clock frequency
	//! @return the code for the LTC6904 
	uint32_t frequency_to_code(float frequency, //!< Clock frequency in MHz
                                  uint8_t clk           //!< Output configuration
                                  );
	uint8_t _address;
	uint8_t _output_config;
	float _freq;
};


#endif

