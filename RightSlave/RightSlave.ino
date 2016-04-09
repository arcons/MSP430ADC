/*

 This example code is in the public domain.
 
 */
 
 /*
 Name: WWECGRIGHT
 MAC: 74DAEAA8A790
 IMME: 0
 PIN: Default 
 */ 


#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <SoftwareSerial.h>

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
float voltage = 0.0;
float voltage2 = 0.0;

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // set the data rate for the SoftwareSerial port
 // mySerial.begin(9600);
  Serial.println("Starting ADC");
  ads.begin();
  Serial.println("No error with the ads begin"); 
  //ads.startComparator_SingleEnded(0, 1000); 
}

void loop() // run over and over
{
  int16_t adc0, adc1;
//  adc1, adc2, adc3;
  int16_t timestamp;
  //timestamp = millis();
  //adc0 = ads.getLastConversionResults();
  adc0 = ads.readADC_SingleEnded(0);
  //adc1 = ads.readADC_SingleEnded(1);
  voltage = (adc0 * 0.1875)/1000;
  //voltage2 = (adc1 * 0.1875)/1000;
  //Serial.print("AIN0: ");
  //Serial.println(adc0);
  //  Serial.print("AIN1: "); Serial.println(adc1);
  Serial.print("\tVoltage: ");
  Serial.println(voltage);  
  Serial.println(" ");
  delay(100); 
}
