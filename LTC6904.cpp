
#include "LTC6904.h"
#include <Wire.h>

//#define pwrpin PORTC2
//#define gndpin PORTC3
//DDRC |= _BV(pwrpin) | _BV(gndpin);
//PORTC &=~ _BV(gndpin);
//PORTC |=  _BV(pwrpin);
//delay(100); // wait for things to stabilize
//Wire.begin();

LTC6904::LTC6904(int ADR)
{
	this->setADR(ADR);
}

LTC6904::LTC6904(int ADR, float freq_MHz)
{
	this->setADR(ADR);
	this->setFrequency(freq_MHz);
}

void LTC6904::setADR(int ADR)
{
	if (ADR==0){
		this->_address = LTC6904_ADDRESS_A;
	}
	else if (ADR==1) {
		this->_address = LTC6904_ADDRESS_B;
	}
}

uint8_t LTC6904::getAddress()
{
	return this->_address;
}

float LTC6904::getFreq()
{
	return this->_freq;
}

uint8_t LTC6904::getOutputCfg()
{
	return this->_output_config;
}


void LTC6904::settings(uint8_t setting)
{
	switch(setting)
	{
		case 1:
			this->_output_config = LTC6904_CLK_ON_CLK_INV_ON;
			Serial.println("LTC6904_CLK_ON_CLK_INV_ON");
			break;
		case 2:
			this->_output_config = LTC6904_CLK_OFF_CLK_INV_ON;
			Serial.println("LTC6904_CLK_OFF_CLK_INV_ON");
			break;
		case 3:
			this->_output_config = LTC6904_CLK_ON_CLK_INV_OFF;
			Serial.println("LTC6904_CLK_ON_CLK_INV_OFF");
			break;
		case 4:
			this->_output_config = LTC6904_POWER_DOWN;
			Serial.println("LTC6904_POWER_DOWN");
			break;
		default:
			Serial.println(F("Invalid mode"));
			return;
	}
}


//! Sets the output frequency in kHz.
//! @return the ACK if 0, NACK if 1
uint8_t LTC6904::setFrequency(float freq_kHz)
{
	this->_freq = freq_kHz;
	uint16_t clock_code;
	uint8_t ack;

	// Calculates the code necessary to create the clock frequency (kHz)
	clock_code = frequency_to_code(this->_freq/1000, this->_output_config);

	ack = this->write(this->_address, (uint16_t)clock_code);
	return(ack);
}

//! Manually Sets OCT and DAC Code
//! @return ack
uint8_t LTC6904::manuallySetReg(uint8_t oct, uint8_t dac_code)
{
	uint8_t ack;
	if(oct > 15)
	oct = 15;

	//this->_freq = 
	
	// Manually set registers
	ack = this->write(this->_address, (uint16_t)((oct<<12)|(dac_code<<2)|this->_output_config));
	return(ack);
}


// Writes 2 bytes
uint8_t LTC6904::write(uint8_t address, uint16_t code)
{
	uint8_t high = (uint8_t)((code&0xFF00) >> 8);
	uint8_t low  = (uint8_t)(code&0x00FF);
	Wire.beginTransmission(address);
	Wire.write(high);
	Wire.write(low);
	Wire.endTransmission();
    return 1;
}

// Calculates the code necessary to create the clock frequency
// Returns the Code for the LTC6903 
uint32_t LTC6904::frequency_to_code(float frequency, uint8_t clk)
{
    byte oct;
    double oct_double;
    float float_dac;
    word dac;

    // Calculate OCT
    oct_double = log10((double)((frequency*1000000)/1039));
    oct_double *= 3.322;
    
    // Keep OCT within range
    if(oct_double>15)
        oct = 15;
    if(oct_double<0)
        oct = 0;
    oct = (uint8_t)oct_double;  // Cast as uint8_t , round down

    // Calculate DAC code
    float_dac = 2048-(2078*pow(2, (10+ oct)))/(frequency*1000000);   // Calculate the dac code
    float_dac = (float_dac > (floor(float_dac) + 0.5)) ? ceil(float_dac) : floor(float_dac);  // Round

    // Keep DAC within range
    if(float_dac>1023)
        float_dac = 1023;
    if(float_dac<0)
        float_dac = 0;
    
    dac = (uint16_t)float_dac;  // Cast as uint16_t

    return((uint32_t)((oct<<12)| (dac<<2) | clk));
}





