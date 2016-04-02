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
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>



SoftwareSerial mySerial(P1_1, P1_2); // RX, TX

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  delay(100);
  Serial.println("Hello world3");
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
}

void loop() // run over and over
{
  if (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  if (Serial.available())
  {
    mySerial.write(Serial.read());
  }
  delay(2);
  long time = millis();
  Serial.println(time);
  Serial.flush();
}
