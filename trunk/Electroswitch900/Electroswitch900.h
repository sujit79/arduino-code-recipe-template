
#ifndef Electroswitch900_h
#define Electroswitch900_h

#include "WProgram.h"

/****************************************************************/
/* Electroswitch900 -- manages the OakGrigsby Electroswitch 900 */

void e90_setupAOnPin2 ( int pinB ); // if pinB is 2 or 3 then we'll use interrupt handling on it too
void e90_setupAOnPin3 ( int pinB ); // if pinB is 2 or 3 then we'll use interrupt handling on it too

void e90_setResolution ( int resolution );
void e90_setRange ( long min, long max );
void e90_startAt ( long value );

long e90_getValue ();

#endif
