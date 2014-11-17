/*!
Linear Technology DC726A-B Demonstration Board.
LTC6904: 1kHz to 68MHz Serial Port Programmable Oscillator

http://www.linear.com/product/LTC6904

*/

#include <LTC6904.h>
#include <Wire.h>
#define pi 3.1415926535

LTC6904 LTC6904_A(0);
LTC6904 LTC6904_B(1);

float Frequency_kHz = 1.0;
void I2C_setpowerpins();
void I2C_Init();
long timeout = 50;
long timer = 0;
float Fo_Hz = 0.1;

//! Initialize Arduino
void setup()
{
  I2C_setpowerpins();
  I2C_Init();
    
  Serial.begin(115200);          // Initialize the serial port to the PC
  Serial.setTimeout(30);
  timer = millis();
  
  // Output Configuration
  // LTC6904_CLK_ON_CLK_INV_ON   0x00    //!< Clock on, inverted clock on
  // LTC6904_CLK_OFF_CLK_INV_ON  0x01    //!< Clock off, inverted clock on
  // LTC6904_CLK_ON_CLK_INV_OFF  0x02    //!< Clock on, inverted clock off
  // LTC6904_POWER_DOWN          0x03    //!< Powers down clocks
  LTC6904_A.settings(LTC6904_CLK_ON_CLK_INV_ON);  
}

void loop()
{
  float f;
  long time = millis();
  float A = 5.0;
  if (time - timer > timeout)
  {
    f = sin(2*pi*time*Fo_Hz/1000.0);
    Frequency_kHz = f*A + A + 1; // cycly frequency from (A-A) to (A+A) at a rate of Fo_Hz
    LTC6904_A.setFrequency(Frequency_kHz);
    Serial.print(F("Frequency_kHz = "));
    Serial.println(Frequency_kHz);
    
    // Frequency_kHz = Frequency_kHz + 0.025;
    timer = time;
    
  }
}


void I2C_setpowerpins()
{
  DDRC |= _BV(PORTC2) | _BV(PORTC3);
  PORTC &=~ _BV(PORTC3);
  PORTC |=  _BV(PORTC2);
  delay(100); // wait for things to stabilize
}

void I2C_Init()
{
  Wire.begin();
}

