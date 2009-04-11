
#include <OneWire.h>

#include "DallasTemp.h"

/************************************************/
/* utilize Dallas one wire temperature devices  */

#define parasitic 1

#define DS18B20 0x28
#define DS18S20 0x10

/* ======================================================== */
/* ======================================================== */
DallasTemp::DallasTemp ( int busPin, DallasBus& aBus, byte* address ) 
: DallasDevice(busPin,aBus,address) { 
	_doGet = _doAsk = _known = false;
	if (_family == DS18B20) { _known = true; }
	if (_family == DS18S20) { _known = true; }
}

/* ======================================================== */
const char* DallasTemp::type ( const byte family ) {
	switch (family) {
		case DS18S20: { return "DS18S20"; break; }
		case DS18B20: { return "DS18B20"; break; }
	}
	return DallasDevice::type(family);
}

/* ======================================================== */
void DallasTemp::setup ( boolean reportToSerial ) {
	DallasDevice::setup(reportToSerial);
	_doAsk = _exists;
}

/* ======================================================== */
void DallasTemp::loop() {
	DallasDevice::loop();
	if (_exists && _known) {
		if (_doAsk && _myBus->isBusAvailable()) {
			if (_myBus->reserveBus(_addr)) { askTemp(); }
		}

		if (_doGet && _myBus->isBusOwner(_addr)) {
			if (getTemp()) { _myBus->releaseBus(_addr); }
		}
	}
}

/* ======================================================== */
void DallasTemp::askTemp() {
	reset();
	select(_addr);
	write(0x44,parasitic); // assume parasite mode
	_doAsk=false; _doGet=true;
	_tempDoneTime = millis() + 800;
}

/* ======================================================== */
boolean DallasTemp::getTemp() {
	if (_tempDoneTime > millis()) {
		return false;
	}
	reset();
	select(_addr);   
	write(0xBE);
	_tempData1 = read();
	_tempData2 = read();
	_doGet=false;
	_doAsk=true;
	return true;
}

/* ======================================================== */
int DallasTemp::fahrenheit() {
	if (! _exists || ! _known) { 
		return 0;
	}
	int fahrenheit = (celsius()*1.8)+32;
	return fahrenheit;
}

/* ======================================================== */
int DallasTemp::celsius() {
	if (! _exists || ! _known) { 
		return 0;
	}
	int celsius = 0;
	switch (_family) {
		case DS18B20: {
			// ignore the top two bits
			celsius = (_tempData2<<8)+_tempData1;
			// divide by 16 to get pure celsius readout
			celsius = celsius>>4;
			break;
		}
		case DS18S20: {
			// load all 8 bits of the LSB
			celsius = _tempData1 >> 1; 
			// sign bit set, temp is negative
			if (_tempData2 > 0x80) { 
				celsius = celsius * -1;
			}
			break;
		}
	}
	return celsius;
}

/* ======================================================== */
/* ======================================================== */
