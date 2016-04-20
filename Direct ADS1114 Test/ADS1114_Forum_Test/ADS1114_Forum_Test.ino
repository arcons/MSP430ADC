
#include <Wire.h>

// ADS1114 I2C address is 0x48(72)
#define Addr 0x48
#define LED RED_LED
uint16_t temp;
byte outputData[4];
void setup() 
{
  pinMode(LED, OUTPUT);  
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise Serial Communication, set baud rate = 9600
  Serial.begin(9600);
  Serial.println("Starting ADC analysis");
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select configuration register
  Wire.write(0x01);
  // AINP = AIN0 and AINN = AIN1, +/- 2.048V
  Wire.write(0x84);
    // Continuous conversion mode, 250 SPS
  Wire.write(0xC3);
  // Stop I2C Transmission
  Wire.endTransmission();
  Serial.println("Starting ADC analysis");
  delay(300);
}

void loop() 
{
  unsigned int data[2];

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // raw_adc msb, raw_adc lsb
  if(Wire.available() == 2)
  {
     data[0] = Wire.read();
     data[1] = Wire.read();
     digitalWrite(LED, HIGH);
  }
  else
  {
//      digitalWrite(LED, LOW); 
  }

  // Convert the data
  float raw_adc = (data[0] * 256.0) + data[1];
//  raw_adc=raw_adc/16;
  // Output data to serial monitor
  float voltage = raw_adc * 0.0000625;
//  Serial.print(data[0], HEX);
//  Serial.print("\t");
//  Serial.println(data[1], HEX);
//  Serial.print("Digital value of analog input : ");
//  Serial.println(raw_adc);
  Serial.print("Digital value of voltage input : ");
  Serial.println(voltage);
}

