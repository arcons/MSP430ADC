/*

 This example code is in the public domain.
 
 */
 
 /*
 Name: WWECGRIGHT
 MAC: 74DAEAA8A790
 IMME: 0
 PIN: Default 
 */ 


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

#define LED RED_LED
#define Addr 0x48

boolean start = false;
uint16_t runTime;
byte data[2];
uint8_t writeFormat[6];
float raw_adc;



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
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  //ads.startComparator_SingleEnded(0, 1000);
  delay(100);
}

void loop() // run over and over
{  
  if (start)
  {
    digitalWrite(LED, HIGH);
    //Serial.println("TEST TEST TEST");
//    runTime = millis();
//    char output[2];
//    uint16_t temp;
//    temp = runTime;
//    temp &= 0xFF;
//
//    char runTimeLSB = runTime>>8 & 0xFF;
//    char runTimeMSB = temp;
//
//    output[3] = runTimeLSB;
//    output[2] = runTimeMSB;

//    output[0] = 0x00;
//    output[1] = 0x00;
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
    raw_adc = (data[0] * 256.0) + data[1];
    //Serial.println(raw_adc);
    
//    //Serial.print("Write data angles");
//    writeFormat[0] = (uint8_t)data[0];
//    writeFormat[1] = (uint8_t)data[1];
//
if(Serial.available()>=1)
{
    writeFormat[0] = (uint8_t)1;
    writeFormat[1] = (uint8_t)2;
    writeFormat[2] = (uint8_t)3;
    writeFormat[3] = (uint8_t)4;
    writeFormat[4] = (uint8_t)5;
    writeFormat[5] = (uint8_t)6;
//    writeFormat[6] = (uint8_t)6;
//    writeFormat[7] = (uint8_t)7;
//    writeFormat[8] = (uint8_t)8;
//    writeFormat[9] = (uint8_t)9;
//    writeFormat[10] = (uint8_t)10;
//    writeFormat[11] = (uint8_t)11;
//    writeFormat[12] = (uint8_t)12;
//    writeFormat[13] = (uint8_t)13;
//    writeFormat[14] = (uint8_t)14;
//    writeFormat[15] = (uint8_t)15;
//    writeFormat[16] = (uint8_t)16;
//    writeFormat[17] = (uint8_t)17;
//    writeFormat[18] = (uint8_t)18;
//    writeFormat[19] = (uint8_t)19;
    Serial.write(writeFormat, 6);
    Serial.read();
}
    //digitalWrite(LED, LOW);
  }
  else
  {
    //Serial.println("Output LED");
    digitalWrite(LED, LOW);
    delay(500);
    digitalWrite(LED, HIGH);
    
    if (Serial.available()>=2)
    {
      char recMessage[2];
      //ASCII for go
      char goMessage[2] = {'g', 'o'};
      Serial.readBytes(recMessage, 2);
      //Check if the go message was received
      if(recMessage[0] == goMessage[0]  && recMessage[1] == goMessage[1]) 
      {
        //Start the run
        digitalWrite(LED, HIGH);
        delay(3000);
        digitalWrite(LED, LOW);
        start = true;
        //Serial.write(start);
      }
    }
  }
}


