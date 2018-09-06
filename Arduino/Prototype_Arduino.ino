/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>
#include <Servo.h> 

//int PIN of servo moter to PIN 9 of Arduino
int servoPin = 9;
Servo servo; 

//Blutooth communication
SoftwareSerial mySerial(2, 3); // RX, TX
String str;  //String from Bluetooth device
#define STRART "start"

int angle = 0; // servo position in degrees 

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);

  servo.attach(servoPin,544,2400); 
}

void loop() { // run over and over
  if (mySerial.available()) {
    str = mySerial.readString();
    
    //if string from the device is "start", trun on the moter
    if(str.equals(STRART)) {
      Serial.println(str);
      for(angle = 1; angle < 118; angle++) { 
        servo.write(angle);
        delay(7); 
      }
      // now scan back from current angle to 0 degrees
     for(angle = servo.read(); angle > 0; angle--) { 
        servo.write(angle); 
        delay(7); 
      } 
    }
  }
}
