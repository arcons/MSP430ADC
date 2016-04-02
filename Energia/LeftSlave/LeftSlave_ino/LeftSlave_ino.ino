/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin P1.4 (connect to TX of other device)
 * TX is digital pin P1.3 (connect to RX of other device)
 
 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example
 modified again 8 Feb 2013
 by Brian Baker for MSP430
 
 This example code is in the public domain.
 
 */
 
 /*
 Name: WWECGLEFT
 MAC ADDR:74DAEAA8A7AE 
 IMME: 0
 PIN: Default 
 */ 
#include <SoftwareSerial.h>

SoftwareSerial mySerial(P1_1, P1_2); // RX, TX

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  Serial.println("Hello Karson");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}

void loop() // run over and over
{
//  if (mySerial.available())
//  {
//    Serial.println("Y -4.370000 157");
//    Serial.write(mySerial.read());
//  }
//  if (Serial.available())
//    mySerial.write(Serial.read());
//    
    //Serial.write("Y -4.370000 157")
    uint8_t data[13] = {0x00, 0x01, 0x02, 0x03, 0x00, 0x01, 0x02, 0x03, 0x00, 0x01, 0x02, 0x03, 0x10};
    Serial.write(data, 13);
    delay(500);
}
