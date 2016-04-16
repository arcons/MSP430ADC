/*
 Left Slave
 By Alexander Consunji
 
 After connection is established
 begin sending the data 
 
 Name: WWECGLEFT
 MAC ADDR:74DAEAA8A7AE 
 IMME: 0
 PIN: Default 
 */

#include <Wire.h>
#include <Adafruit_ADS1015.h>

#define LED RED_LED
#define Addr 0x48

boolean start = false;
uint16_t runTime;

void setup()  
{

  // Open serial communications and wait for port to open:
  pinMode(LED, OUTPUT);  
  Serial.begin(9600);
  delay(100);
  Wire.begin();
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select configuration register
  Wire.write(0x01);
  // AINP = AIN0 and AINN = AIN1, +/- 2.048V
  Wire.write(0x84);
  // Continuous conversion mode, 128 SPS
  Wire.write(0x83);
  // Continuous conversion mode, 128 SPS
  Wire.write(0xC3);
  //Allow the LED to output
  Wire.endTransmission();
  digitalWrite(LED, LOW);
  //ads.startComparator_SingleEnded(0, 1000);
  delay(300);
}

void loop() // run over and over
{
  if(Serial.available())
  {
    char recMessage[2];
    //ASCII for go
    char goMessage[2] = {'g', 'o'};
    Serial.readBytes(recMessage, 2);
    //Check if the go message was received
    if(recMessage[0] == goMessage[0]  && recMessage[1] == goMessage[1]) 
    {
      //Start the run
      start = true;
    }
  }
  if(start)
  {
    digitalWrite(LED, HIGH);
    //Serial.println("TEST TEST TEST");
    runTime = millis();
    char output[4];
    unsigned int data[2];
    uint16_t temp;
    temp = runTime;
    temp &= 0xFF;

    char runTimeLSB = runTime>>8 & 0xFF;
    char runTimeMSB = temp;

    output[3] = runTimeLSB;
    output[2] = runTimeMSB;
    //Serial.println("Start I2C Transmission");
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select data register
    //Serial.println("Write Select Data Register");
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
    }
    //Serial.print("Digital value of analog input : ");
    //float raw_adc = (data[0] * 256.0) + data[1];
    //Serial.println(raw_adc);
    uint8_t writeFormat[4];
    //Serial.print("Write data angles");
    writeFormat[0] = (uint8_t)output[0];
    writeFormat[1] = (uint8_t)output[1];
    writeFormat[2] = (uint8_t)data[0];
    writeFormat[3] = (uint8_t)data[1];
    Serial.write(writeFormat, 4);
    digitalWrite(LED, LOW);
  }
  else
  {
    Serial.println("Output LED");
    digitalWrite(LED, LOW);
    delay(500);
    digitalWrite(LED, HIGH);
  }
}


