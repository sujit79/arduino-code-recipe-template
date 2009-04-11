/* ======================================================== */
/* ======================================================== */

/* 
	allen joslin
	payson productions
	allen@joslin.net
*/

/* ======================================================== */
/* ======================================================== */

#ifndef SparkFunPIR_h
#define SparkFunPIR_h

#include "WProgram.h"

/* ======================================================== */
class SparkFunPIR {
  
  private:
  
    int _pin;
    
    unsigned long _debounce;
    unsigned long _waitUntil;
    
    unsigned long _lastLOW;
    unsigned long _lastHIGH;
    
    typedef void (*callback)(void);

    callback _callbackLOW;
    callback _callbackHIGH;
    
  public:
  
	SparkFunPIR ( int sensePin, int deBounce=2000, boolean minimizeStateChanges=true );
    
    void setup ( boolean useOnboardPullup=true );
    void loop (); // does not block
    
    // state of view -- as of the last loop()
    boolean movement () { return (_lastHIGH > _lastLOW); }
    boolean noMotion () { return (_lastLOW > _lastHIGH); }
    
    // called only when the state changes -- from loop()
    void movementCallback ( callback func ) { _callbackLOW = func; }
    void noMotionCallback ( callback func ) { _callbackHIGH = func; }
  
};

#endif
