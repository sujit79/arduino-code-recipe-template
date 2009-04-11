
/* 
NOTE: you must: #include <OneWire.h>
	BEFORE including this header file
*/

#include "DallasDevices.h"

#ifndef DallasTemp_h
#define DallasTemp_h

#include "WProgram.h"

/************************************************/
/* utilize Dallas one wire temperature devices  */

/* ======================================================== */
/* ======================================================== */
class DallasTemp : public DallasDevice {

protected:

	unsigned long _tempDoneTime;
	byte _tempData1, _tempData2;

	boolean _doAsk; void askTemp ();
	boolean _doGet; boolean getTemp ();

public:

	DallasTemp ( int busPin, DallasBus& aBus, byte* theAddress );

	void setup ( boolean reportToSerial=false );
	void loop (); // must not block

	const char* type ( const byte family );

	int fahrenheit ();
	int celsius ();

};

/* ======================================================== */
/* ======================================================== */

#endif
