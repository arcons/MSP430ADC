#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
float voltage = 0.0;
void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Hello!");
  
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  Wire.begin();
}

void loop(void) 
{
  int16_t adc0;
//  adc1, adc2, adc3;
  Serial.print("AIN0: "); Serial.println(adc0);
  adc0 = readADC_SingleEnded(0);
  voltage = (adc0 * 0.1875)/1000;
  Serial.print("AIN0: "); Serial.println(adc0);
  Serial.print("\tVoltage: ");
  Serial.println(voltage, 7);  
  Serial.println(" ");
  
  delay(200);
}
   uint8_t   m_i2cAddress=0x48;
   uint8_t   m_conversionDelay=8;
   uint8_t   m_bitShift=0;
   adsGain_t m_gain;

int16_t readADC_SingleEnded(uint8_t channel) {
  // Start with default values
  uint16_t config = ADS1015_REG_CONFIG_CQUE_NONE    | // Disable the comparator (default val)
                    ADS1015_REG_CONFIG_CLAT_NONLAT  | // Non-latching (default val)
                    ADS1015_REG_CONFIG_CPOL_ACTVLOW | // Alert/Rdy active low   (default val)
                    ADS1015_REG_CONFIG_CMODE_TRAD   | // Traditional comparator (default val)
                    ADS1015_REG_CONFIG_DR_1600SPS   | // 1600 samples per second (default)
                    ADS1015_REG_CONFIG_MODE_SINGLE; 
  // Set PGA/voltage range
  config |= m_gain;
  
 Serial.println("Config is set ");
  // Set single-ended input channel
  switch (channel)
  {
    case (0):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_0;
      break;
    case (1):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_1;
      break;
    case (2):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_2;
      break;
    case (3):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_3;
      break;
  }

  // Set 'start single-conversion' bit
  config |= 0x8000;
 Serial.println("Single conversion bit set");
  // Write config register to the ADC
  writeRegister(m_i2cAddress, ADS1015_REG_POINTER_CONFIG, config);
 Serial.println("register has been written");
  // Wait for the conversion to complete
  delay(m_conversionDelay);
 Serial.println("conversion delay is over");
  // Read the conversion results
  // Shift 12-bit results right 4 bits for the ADS1015
   Serial.println("Returning the registers read");
  return readRegister(m_i2cAddress, 0x00) >> m_bitShift;  
}

 byte  test;

static void writeRegister(uint8_t i2cAddress, uint8_t reg, uint16_t value) {
     Serial.println("Beginning i2c transmission");
  Wire.beginTransmission(i2cAddress);
     Serial.print("Writing to register ");
     Serial.println(reg);
  Wire.write(reg);
     Serial.print("Writting 8 bit shift");
     Serial.println(value>>8);
  Wire.write((uint8_t)(value>>8));
     Serial.print("writing end value");
     Serial.println(value & 0xFF);
  Wire.write((uint8_t)(value & 0xFF));
     Serial.println("End of transmission");
     Wire.endTransmission(true);
}

int16_t readRegister(uint8_t i2cAddress, uint8_t reg) {
     Serial.println("Reading from register");
  Wire.beginTransmission(i2cAddress);
     Serial.println("Returning the registers read");
  Wire.write((uint8_t)0x00);
  Wire.endTransmission();
     Serial.println("requesting from i2c the registers read");
  Wire.requestFrom(i2cAddress, (uint8_t)2);
  return ((Wire.read() << 8) | Wire.read());  
}
