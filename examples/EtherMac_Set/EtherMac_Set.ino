/*
 EtherMac Library Set Example
 
 This sketch stores a MAC address in the EEPROM on an Arduino. 

 created 09 May 2012
 by J.P. McGlinn
 */
 
#include <EtherMac.h>

void setup(){
  Serial.begin(57600);
  
  // MAC address to store. If you have a real MAC address assigned
  // to your Ethernet hardware you should use it. Arduino Ethernet
  // board should have a sticker on the reverse side with an assigned
  // MAC address.
  byte macToStore[6] = { 0xDE, 0xAD, 0xBA, 0xDD, 0xBE, 0xEF };
  
  //Store!
  if(EtherMac.write(macToStore))
    Serial.println("Stored MAC address.");
}

void loop(){
}


