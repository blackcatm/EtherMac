/*
 EtherMac Library Read Example
 
 This sketch reads a MAC address from the EEPROM on an Arduino. 

 created 09 May 2012
 by J.P. McGlinn
 */
 
#include <EtherMac.h>

byte *MACADDRESS = 0;

void setup(){
  Serial.begin(57600);

  MACADDRESS = EtherMac.read();

  if(!MACADDRESS){
    Serial.println("Error Reading MAC address.");
    while(1){
      //wait forever
    }
  }
  
  //Display the stored MAC address
  char buffer[20];
  Serial.print("Ethernet Hardware Address: ");
  
  sprintf(buffer,"%02x:%02x:%02x:%02x:%02x:%02x",
          MACADDRESS[0],
          MACADDRESS[1],
          MACADDRESS[2],
          MACADDRESS[3],
          MACADDRESS[4],
          MACADDRESS[5]);
  Serial.println(buffer);
  
}

void loop(){
}


