
#include <WProgram.h>

#include <OneWire.h>
#include <DallasTemp.h>

#include <SoftwareSerial.h>
#include <SparkFunSerLCD.h>

SparkFunSerLCD led(8,2,16); // desired pin, rows, cols

/* ======================================================== */

byte breadTempAddr[] = { 0x28, 0xEA, 0xBC, 0x46, 0x01, 0x00, 0x00, 0xD4 };
byte wiredTempAddr[] = { 0x10, 0xC4, 0x48, 0x1B, 0x00, 0x08, 0x00, 0xB5 }; // on station

DallasBus busOne(12);

DallasTemp wiredTemp = DallasTemp(12,busOne,wiredTempAddr);
DallasTemp breadTemp = DallasTemp(12,busOne,breadTempAddr);

void setup () {
  Serial.begin(9600); 
  led.setup();

  busOne.discovery();
  
  wiredTemp.setup(false);
  breadTemp.setup(false);
  
  if (breadTemp.exists()) {
    led.at(1,1,"< F:"); 
  }
  
  if (wiredTemp.exists()) {
    led.at(2,1,"> F:"); 
  }
}

unsigned long nextTime = 0;
void loop () {
  
  if (millis() > nextTime) {

    if (breadTemp.exists()) {
      led.at(1,5,breadTemp.fahrenheit()); 
      breadTemp.loop();
    }
  
    if (wiredTemp.exists()) {
      led.at(2,5,wiredTemp.fahrenheit()); 
      wiredTemp.loop();
    }
    
    nextTime = millis() + 1000;
  }
}

