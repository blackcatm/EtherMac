/* 
  EtherMac.cpp - EtherMac library for Arduino
  Copyright (c) 2012 J.P. McGlinn.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*
 EtherMac is an Arduio Library for reading and writing Ethernet
 MAC addresses from EEPROM
 */


/******************************************************************************
 * Includes
 ******************************************************************************/

#include "EtherMac.h"


/******************************************************************************
 * Definitions
 ******************************************************************************/

/******************************************************************************
 * Constructors
 ******************************************************************************/

/******************************************************************************
 * Private Methods
 ******************************************************************************/
uint8_t EtherMacClass::e2read(int address){
	return eeprom_read_byte((unsigned char *) address);
}

void EtherMacClass::e2write(int address, uint8_t value){
	eeprom_write_byte((unsigned char *) address, value);
}
/******************************************************************************
 * User API
 ******************************************************************************/


int EtherMacClass::write(byte *mac){
    uint8_t CRC = 0;
    
    //sanity check, must have non-null pointer
    if(mac==0)
        return -1;
    
    //write the MAC address generate CRC
    for(int i = 0; i < 6; i++){
        e2write(MACADDRESS_E2_LOCATION + 1 + i, mac[i]);
        CRC ^= mac[i];
    }
    
    //write the CRCs
    e2write(MACADDRESS_E2_LOCATION, CRC);
    e2write(MACADDRESS_E2_LOCATION + 7, CRC ^ 0xFF);
    
    //VERIFY
    //read the CRCs from EEPROM
    uint8_t CRC0 = e2read(MACADDRESS_E2_LOCATION);
    uint8_t CRC1 = e2read(MACADDRESS_E2_LOCATION + 7);
    
    //check that CRCs match each other
    if((CRC0 ^ CRC1) != 0xFF)
        return -2;
    
    //check that the CRCs match the previous computed value
    if(CRC0 != CRC)
        return -2;
    
    //Read the mac address from EEPROM
    for(int i = 0; i < 6; i++){
        CRC ^=  e2read(MACADDRESS_E2_LOCATION + 1 + i);
    }
    
    //check CRC
    if(CRC0 != CRC)
        return -3;
    
    return CRC;
}

byte* EtherMacClass::read(){
    byte *mac = (byte*) malloc(6);
    
    if(!mac)
        return 0;
    
    if(read(mac) < 0){
        free(mac);
        return 0;
    }
    
    return mac;
}


int EtherMacClass::read(volatile byte *mac){
    uint8_t CRC = 0;
    
    //read the CRCs from EEPROM
    uint8_t CRC0 = e2read(MACADDRESS_E2_LOCATION);
    uint8_t CRC1 = e2read(MACADDRESS_E2_LOCATION + 7);
    
    //check that CRCs match each other
    if((CRC0 ^ CRC1) != 0xFF)
        return -2;
    
    //Read the mac address from EEPROM
    for(int i = 0; i < 6; i++){
        mac[i] = e2read(MACADDRESS_E2_LOCATION + 1 + i);
        CRC ^= mac[i];
    }
    
    //check CRC
    if(CRC0 != CRC)
        return -3;
    
    return CRC;
}


EtherMacClass EtherMac;
