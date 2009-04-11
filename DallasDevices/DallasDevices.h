
/* 
NOTE: you must: #include <OneWire.h>
	BEFORE including this header file
*/

#ifndef DallasDevices_h
#define DallasDevices_h

#include "WProgram.h"

/*********************************************************************/
/* manage a one wire Dallas bus, uses OneWire lib for communications */

#define addrLen 8

/* ======================================================== */
/* ======================================================== */
class DallasBus : public OneWire {

protected:

	int _pin;

	boolean busHasOwner;
	byte busOwner[addrLen+1];

public:

	DallasBus ( int busPin ) : OneWire(busPin) { _pin = busPin; }

	boolean reserveBus ( byte* who ) { if (isBusAvailable()) { addrCopy(who,busOwner); return true; } return false; }
	boolean releaseBus ( byte* who ) { if (addrCompare(who,busOwner)) { addrCopy(NULL,busOwner); return true; } return false; }

	boolean isBusOwner ( byte* who ) { return addrCompare(who,busOwner); } 
	boolean isBusAvailable () { return addrCompare(NULL,busOwner); }

	void discovery (); // search the bus and print the found device list to default serial output
	boolean confirm ( byte* who, boolean reportToSerial ); // confirm a device is on the bus

	void printHexArray ( const char* tag, byte* arr, int len, boolean eol );
	boolean addrCompare ( const byte*, const byte* ) const;
	void addrCopy ( const byte* src, byte* dest );

	int getBusPin () { return _pin; }

};

/* ======================================================== */
/* ======================================================== */
class DallasDevice : public OneWire {

protected:

	int _pin; 
	boolean _known;
	boolean _exists;
	DallasBus* _myBus;
	byte _family, _addr[addrLen+1];

public:

	DallasDevice ( int busPin, DallasBus& aBus, byte* theAddress )
	: OneWire(busPin) { 
		_myBus = &aBus; _pin = busPin;
		_exists = _known = false;
		_family = theAddress[0];
		*this = theAddress; 
	}

	boolean operator== ( const byte* address ) const { return _myBus->addrCompare(_addr,address); }
	void operator= ( const byte* address ) { _myBus->addrCopy(address,_addr); }

	virtual void setup ( boolean reportToSerial=false );
	virtual void loop (); // must not block

	virtual const char* type ( const byte family );
	boolean exists () const { return _exists; }
	boolean known () const { return _known; }
};

/* ======================================================== */
/* ======================================================== */

#endif
