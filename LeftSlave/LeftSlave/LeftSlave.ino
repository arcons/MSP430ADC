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

#define LED RED_LED

float voltage;
Adafruit_ADS1115 ads; 
SoftwareSerial mySerial(P1_1, P1_2); // RX, TX

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  delay(100);
  Serial.println("Hello world");
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  // set the data rate for the SoftwareSerial port
  //mySerial.begin(9600);
  ads.setGain(GAIN_TWOTHIRDS);
  pinMode(LED, OUTPUT);  
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  ads.begin();
  //ads.startComparator_SingleEnded(0, 1000);
}

void loop() // run over and over
{
//  if (mySerial.available())
//  {
//    Serial.write(mySerial.read());
//  }
//  if (Serial.available())
//  {
//    mySerial.write(Serial.read());
//  }
//  delay(2);
//  long time = millis();
//  Serial.println(time);
//  Serial.flush();

  int16_t adc0;
  //adc0 = ads.getLastConversionResults();
  adc0 = ads.readADC_SingleEnded(0);
  Serial.print("AIN0: "); Serial.println(adc0);
  Serial.println(" ");
  voltage = (adc0 * 0.1875)/1000;
  Serial.print("\tVoltage: ");
  Serial.println(voltage, 7);  
  Serial.println(" ");
  delay(1000);
}
