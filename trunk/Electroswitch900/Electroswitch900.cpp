
#include "Electroswitch900.h"

long e90_pinA;
long e90_pinB;

long e90_step;

long e90_minValue;
long e90_maxValue;

void e90_setup();
void e90_setupA( int pinA );
void e90_setupB( int pinB );

void e90_readEncoderA();
void e90_readEncoderB();

volatile long e90_currValue;

/* ======================================================== */

void e90_setupAOnPin2( int pinB ) {
	e90_setupB(pinB);
	e90_setupA(2);
	e90_setup();
}
	
void e90_setupAOnPin3( int pinB ) {
	e90_setupB(pinB);
	e90_setupA(3);
	e90_setup();
}

void e90_setRange ( long lowest, long highest ) {
	e90_minValue=lowest; 
	e90_maxValue=highest;
}

void e90_setResolution( int resolution ) {
	e90_step = 128/resolution;
	if (e90_step < 0) { 
		e90_step=1; 
	}
}

void e90_startAt( long value ) {
	e90_currValue = value;
}
	
long e90_getValue() {
	return e90_currValue;
}

/* ======================================================== */

void e90_setup () {
	e90_currValue = 0;
	e90_maxValue=128;
	e90_minValue=0; 
	e90_step = 1;
}

void e90_setupA ( int pinA ) {
	e90_pinA = pinA; // hook up the pin and the pullup 
	pinMode (e90_pinA,INPUT); digitalWrite(e90_pinA, HIGH);
	attachInterrupt((e90_pinA - 2), e90_readEncoderA, CHANGE);
}

void e90_setupB ( int pinB ) {
	e90_pinB = pinB; // hook up the pin and the pullup 
	pinMode (e90_pinB,INPUT); digitalWrite(e90_pinB, HIGH);
	if ((pinB == 2) || (pinB == 3)) {
		attachInterrupt((e90_pinB - 2), e90_readEncoderB, CHANGE);
	}
}

/* ======================================================== */

void e90_readEncoderA(){
	if (digitalRead(e90_pinA) == HIGH) {   			// found a low-to-high on channel A
	  if (digitalRead(e90_pinB) == LOW) {  			// check channel B to see which way
	                                       			// encoder is turning
	    e90_currValue = e90_currValue + e90_step;	// CW
	  }                                          	
	  else {                                     	
	    e90_currValue = e90_currValue - e90_step;	// CWW
	  }                                    
	}                                      
	else                                   			// found a high-to-low on channel A
	{                                      			
	  if (digitalRead(e90_pinB) == LOW) {  			// check channel B to see which way
	                                       			// encoder is turning  
	    e90_currValue = e90_currValue - e90_step;	// CWW
	  }                                    
	  else {                               
	    e90_currValue = e90_currValue + e90_step;	// CW
	  }
	}
	if (e90_currValue < e90_minValue) { e90_currValue = e90_minValue; }
	if (e90_currValue > e90_maxValue) { e90_currValue = e90_maxValue; }
}

void e90_readEncoderB(){
	if (digitalRead(e90_pinB) == HIGH) {   			// found a low-to-high on channel B
	  if (digitalRead(e90_pinA) == LOW) {  			// check channel A to see which way
	                                       			// encoder is turning
	    e90_currValue = e90_currValue - e90_step;	// CCW
	  }                                    
	  else {                               
	    e90_currValue = e90_currValue + e90_step;	// CW
	  }                                    
	}                                      
	else                                   			// found a high-to-low on channel B
	{                                            	
	  if (digitalRead(e90_pinA) == LOW) {  			// check channel A to see which way
	                                       			// encoder is turning  
	    e90_currValue = e90_currValue + e90_step;	// CW
	  }                                    
	  else {                               
	    e90_currValue = e90_currValue - e90_step;	// CCW
	  }                                    
	}
	if (e90_currValue < e90_minValue) { e90_currValue = e90_minValue; }
	if (e90_currValue > e90_maxValue) { e90_currValue = e90_maxValue; }
}

/* done */

