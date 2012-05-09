/*
  DHCP-based IP printer
 
 This sketch uses the DHCP extensions to the Ethernet library
 to get an IP address via DHCP and print the address obtained.
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 12 April 2011
 by Tom Igoe

 modified 09 May 2012
 by J.P. McGlinn

 Example part of EtherMac, Ethernet MAC address storage library.
 
 Requirements:
 Connection to LAN with DHCP server
 MAC addressed stored in EEPROM, see (and run) EtherMac_Set example
 */
 

#include <SPI.h>
#include <Ethernet.h>
#include <EtherMac.h>


// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup(){
  byte *mac = 0;
  Serial.begin(57600);

  mac = EtherMac.read();

  if(!mac){
    Serial.println("Error Reading MAC address.");
    while(1){
      //wait forever
    }
  }
  
 // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();  
  
   //Display the  MAC address
  char buffer[20];
  Serial.print("My MAC address: ");
  
  sprintf(buffer,"%02x:%02x:%02x:%02x:%02x:%02x",
          mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.println(buffer);
}

void loop(){
}


