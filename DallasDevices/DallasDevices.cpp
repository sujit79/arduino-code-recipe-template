
#include <OneWire.h>

#include "DallasDevices.h"

/*********************************************************************/
/* manage a one wire Dallas bus, uses OneWire lib for communications */

#define parasitic 1

/* ======================================================== */
/* ======================================================== */
void DallasBus::discovery () {
	Serial.println("DallasBus::discovery()"); 
	reset_search();
	byte addr[addrLen+1];
	while (search(addr)) {
		printHexArray(" found: ",addr,addrLen,false); 
		if ( crc8( addr, 7) != addr[7]) {
			Serial.println("bad crc"); 
			continue;
		}
		Serial.println(); 
	}
}

/* ======================================================== */
boolean DallasBus::confirm ( byte* who, boolean reportToSerial ) {
	if (reportToSerial) {
		Serial.println(" DallasBus::confirm()"); 
		printHexArray("  confirming ",who,addrLen,true); 
	}
	byte test[addrLen];
	reset_search();
	while (search(test)) {
		if (reportToSerial) {
			printHexArray("   testing ",test,addrLen,true); 
		}
		if (addrCompare(who,test)) {
			if (reportToSerial) {
				Serial.print("  device found"); 
			}
			return true;
		}
	}
	reset();
	if (reportToSerial) {
		Serial.println("  device missing"); 
	}
	return false;
}

/* ======================================================== */
void DallasBus::printHexArray ( const char* tag, byte* arr, int len, boolean eol ) {
	Serial.print(tag); 
	Serial.print("{"); 
	for(int i = 0; i < len; i++) {
		Serial.print(" 0x");
		if (arr[i] < 10) {
			Serial.print("0");
		}
		Serial.print(arr[i], HEX);
		if (i < (len-1)) {
			Serial.print(",");
		}
	}
	Serial.print(" }"); 
	if (eol) { Serial.println(); }
}

/* ======================================================== */
void DallasBus::addrCopy ( const byte* srcAddr, byte* destAddr ) {
	for (int x=0; x<addrLen; x++) {
		destAddr[x] = (srcAddr == NULL)? 0x00 : srcAddr[x];
	}
}

/* ======================================================== */
boolean DallasBus::addrCompare ( const byte* addrOne, const byte* addrTwo ) const {
	for (int x=0; x<addrLen; x++) {
		if (((addrOne == NULL)? 0x00: addrOne[x]) != ((addrTwo == NULL)? 0x00: addrTwo[x])) {
			return false;
		}
	}
	return true;
}

/* ======================================================== */
/* ======================================================== */
void DallasDevice::loop () {
}

/* ======================================================== */
void DallasDevice::setup ( boolean reportToSerial ) {
	if (reportToSerial) {
		Serial.println("DallasDevice::setup()"); 
	}
	_exists = _myBus->confirm(_addr,reportToSerial);
	if (_exists && reportToSerial) {
		Serial.print(" type: "); 
		Serial.println(type(_family)); 
	}
}

/* ======================================================== */
const char* DallasDevice::type ( const byte ) {
	return "Unknown";
}

/* ======================================================== */
/* ======================================================== */
