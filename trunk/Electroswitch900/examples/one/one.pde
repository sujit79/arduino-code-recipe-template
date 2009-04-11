

/* 
	NOTE: you must: #include <OneWire.h>
	BEFORE including the Dallas18x20.h header
*/

#include <SoftwareSerial.h>
#include <SparkFunSerLCD.h>

SparkFunSerLCD led(8,2,16); // desired pin, rows, cols

#include <OneWire.h>
#include <Dallas18x20.h>

Dallas18x20 temp(12); // desiredPin

#include <Electroswitch900.h>

void setup () {

  led.setup();
  temp.setup();
  
  led.at(1,4,"Temperature");
  led.at(2,2,"F:");
  led.at(2,13,"C:");
  
  led.bright(100);
  
  e90_setupAOnPin2(4);
  e90_setResolution(100);
  e90_setRange(0,100);
  e90_startAt(50);
  
  Serial.begin(9600);
}

long nextTime = 0;
void loop () {
  
  if (millis() > nextTime) {

    temp.loop();
    led.at(2,15,temp.celsius());
    led.at(2,4,temp.fahrenheit());
  
    led.bright(e90_getValue());
    
    nextTime = millis() + 1000;
  }
}

