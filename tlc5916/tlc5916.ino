#include <SoftwareSerial.h>


     
     /*for(int i=0;i<=16;i++)
     {
      setValue(pow(2,i));/*
Adapted by: d6stringer
Adapted from: Zeecue
June, 8 2018

This test program uses a TLC5916 shift register:
http://www.ti.com/lit/ds/symlink/tlc5916.pdf
Pins in this configuration are wired from an Arduino Nano to the IC in the following configuration:
ArdN---IC
D8-----13 This can be any arduino output wired to the IC's "OE" (output enable) pin
D10----04 This is the arduino's SS (Slave Select) pin wired to the IC's "LE" (latch enable) pin.
D11----02 This is the arduino's MOSI (Master out, slave in) pin wired to the IC's "SDI" (Serial Data In) pin.
D13----03 THis is the arduino's SCK(Serial Clock) pin wired to the IC's "CLK" (Clock) pin.

Current sinks through the TLC5916 pin # 15 (R-EXT). Use a resistor to set the current through the chip.

*/

#include "SPI.h" //library for using SPI


const int ss=8; // using digital pin 10 for SPI slave select
//const int OE=8; //Output Enable Pin

void setup()
{
 pinMode(ss, OUTPUT); // we use this for SS pin
 //pinMode(OE, OUTPUT); // we use this for OE pin
 //digitalWrite(OE, LOW); //enable/disable the OE pin
 SPI.begin(); // wake up the SPI bus.
 
 }

void setValue(word value)
{
 digitalWrite(ss, LOW);
 SPI.transfer16(value); // send value (0~255)
 digitalWrite(ss, HIGH);
}

void loop()
{
     setValue(65535);
     delay(200);
     setValue(0);
     delay(500);
     // delay(50);
     
     //delay(500);
     /*for(int i=16;i>=0;i--)
     {
      setValue(pow(2,i));
      delay(50);
     }*/
}
