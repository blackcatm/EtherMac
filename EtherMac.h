/* 
 EtherMac.h - EtherMac library for Arduino
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


#ifndef ETHERMAC_h
#define ETHERMAC_h

#include <Arduino.h>
#include <avr/eeprom.h>


#define MACADDRESS_E2_LOCATION (E2END - 7)

class EtherMacClass{
public:
    int write(byte *mac);
    byte* read();
    int read(volatile byte *mac);
private:
    uint8_t e2read(int address);
    void e2write(int address, uint8_t value);
};

extern EtherMacClass EtherMac;

#endif

