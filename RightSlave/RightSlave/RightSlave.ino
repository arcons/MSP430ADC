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
 Name: WWECGLEFT
 MAC: 209148AABE0E
 IMME: 0
 PIN: Default 
 */ 
#include <Wire.h>
#include <Adafruit_ADS1015.h>

#define LED RED_LED
#define Addr 0x48

boolean start = false;
uint16_t runTime;
char recMessage[2];
//ASCII for go
char goMessage[2] = {'g', 'o'};
byte outputData[6];

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
  // Continuous conversion mode, 250 SPS
  Wire.write(0xC3);
  //Allow the LED to output
  Wire.endTransmission();
  //Check for reset
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
  delay(300);
}

void loop() // run over and over
{
  if(start)
  {
    
    //Set the LED High
    digitalWrite(LED, HIGH);
//    //Serial.println("Start I2C Transmission");
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
      outputData[3] = Wire.read();
      outputData[4] = Wire.read();
    }
    if(Serial.available()>=1)
    {
    outputData[0]=1;
    outputData[1]=2;
    outputData[2]=3;
//    outputData[3]=4;
//    outputData[4]=5;
    outputData[5]=6;
    Serial.write(outputData, 6);
    Serial.read();
    }
    //Develop a recognized disconnect method
//    if(!Serial.available())
//    {
//      start=false;
//    }
  }
  
  else
  {
//Serial.println("Output LED");
    digitalWrite(LED, LOW);
    delay(500);
    digitalWrite(LED, HIGH);
  }
  
  if(Serial.available()>=2 && !start)
  {
    Serial.readBytes(recMessage, 2);
    //Check if the go message was received
    if(recMessage[0] == goMessage[0]  && recMessage[1] == goMessage[1]) 
    {
      //Start the run
      start = true;
      digitalWrite(LED,HIGH);
      delay(3000);
      digitalWrite(LED,LOW);
      
    }
  }
}


