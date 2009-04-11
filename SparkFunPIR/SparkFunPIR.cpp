/* ======================================================== */
/* ======================================================== */

/* 
	allen joslin
	payson productions
	allen@joslin.net
*/

/* ======================================================== */
/* ======================================================== */

#include "SparkFunPIR.h"

/* ======================================================== */
SparkFunPIR::SparkFunPIR ( int sensePin, int deBounce, boolean minimizeStateChanges ) {
  _callbackHIGH = _callbackLOW = NULL;
  _lastLOW = _lastHIGH = millis();
  _debounce = deBounce;
  _pin = sensePin;
  _waitUntil = 0;
}

/* ======================================================== */
void SparkFunPIR::setup ( boolean useOnboardPullup ) { 
  pinMode(_pin,INPUT); 
  if (useOnboardPullup) { 
    digitalWrite(_pin,HIGH); 
  } 
  _waitUntil = millis() + _debounce;
}

/* ======================================================== */
void SparkFunPIR::loop () { 
  
  if (_waitUntil > millis()) {
    return; // debouncing
  }
  
  int stateWAS = (_lastLOW > _lastHIGH)? LOW: HIGH;
  int stateNOW = digitalRead(_pin); // look now
  boolean stateCHANGED = (stateWAS != stateNOW);
  
  switch (stateNOW) {
    
    case LOW: {
      _lastLOW = millis();
      _waitUntil = _lastLOW + _debounce;
      if (_callbackLOW && stateCHANGED) {
        _callbackLOW();
      }
      break;
    }
    
    case HIGH: {
      _lastHIGH = millis();
      _waitUntil = _lastHIGH + _debounce;
      if (_callbackHIGH && stateCHANGED) {
        _callbackHIGH();
      }
      break;
    }
  }
  
}

/* ======================================================== */
/* ======================================================== */
/* ======================================================== */
