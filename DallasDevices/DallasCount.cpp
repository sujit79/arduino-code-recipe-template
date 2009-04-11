
#include <OneWire.h>

#include "DallasCount.h"

/*********************************************/
/* utilize Dallas one wire counting devices  */

#define parasitic 1

//  DS2423  4k ram with counter
#define DS2324 0x1D

/* ======================================================== */
/* ======================================================== */
DallasCount::DallasCount ( int busPin, DallasBus& aBus, byte* address ) 
: DallasDevice(busPin,aBus,address) { 
	_known = false;
}

/* ======================================================== */
const char* DallasCount::type ( const byte family ) {
	switch (family) {
		case DS2324: { return "DS2324"; break; }
	}
	return DallasDevice::type(family);
}

/* ======================================================== */
void DallasCount::setup ( boolean reportToSerial ) {
	DallasDevice::setup(reportToSerial);
	_wantCount = _exists;
}

/* ======================================================== */
void DallasCount::loop () {
	DallasDevice::loop();
	if (_exists && _known) {
		if (_wantCount && _myBus->isBusAvailable()) {
			if (_myBus->reserveBus(_addr)) {
				if (getCount()) { 
					_wantCount=false; _gotCount=true;
					_myBus->releaseBus(_addr); 
				}
			}
		}
	}
}

/* ========================================================* 
**	The DS2423 returns the counter A count at the end      **
**	of page 0x01c0 and is returned by sending              **
*	the instruction 0xa5.									*/
boolean DallasCount::getCount () {
	reset();
	skip();
	write(0xa5, 0);			// Read memory and counter command
	write(0xc0, 0);			// Start at page 14 which has external counter A at the end...
	write(0x01, 0);			// = 0x01c0 
	for (int i = 0; i<32; i++)	//Read back the 32 bits in the datapage (no information for us here)
	{
		read();
	}
	byte data[4];
	for (int i = 0; i < 4; i++)	// Read back the 4 bytes of external counter A
	{
		data[i] = read();
	}
	_counter = data[0];		//As we're only using the lowest byte we don't need data[1 to 3]
	return true;
}

/* ======================================================== */
/* ======================================================== */
