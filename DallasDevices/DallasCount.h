
/* 
NOTE: you must: #include <OneWire.h>
	BEFORE including this header file
*/

#include "DallasDevices.h"

#ifndef DallasCount_h
#define DallasCount_h

#include "WProgram.h"

/*********************************************/
/* utilize Dallas one wire counting devices  */

/* ======================================================== */
/* ======================================================== */
class DallasCount : public DallasDevice {

protected:
	
	int _counter;
	
	boolean _gotCount;
	boolean _wantCount;
	boolean getCount ();

public:

	DallasCount ( int busPin, DallasBus& aBus, byte* theAddress );

	void setup ( boolean reportToSerial=false );
	void loop (); // must not block

	const char* type ( const byte family );
	
	void needCount () { _wantCount = true; _gotCount = false; }
	boolean haveCount() const { return _gotCount; } // count during 
	int getCounter () const { return _counter; } // loop() as avail
	int countNow () { if ( (_gotCount = getCount()) ) { return getCounter(); } return 0xFF; }// do it now
	
	
};

/* ======================================================== */
/* ======================================================== */

#endif
