

#include <SparkFunPIR.h>

SparkFunPIR pir(7); // sensePin

void setup () {
  
  Serial.begin(9600);
  pir.setup();
  
  pir.movementCallback(movement);
  pir.noMotionCallback(noMotion);
  
}

void noMotion () {
  Serial.print(millis());
  Serial.println(" no motion [called]");
}

void movement () {
  Serial.print(millis());
  Serial.println(" movement [called]");
}


int holdUntil = 0; // slow things down a bit
void loop () {
  
  pir.loop();
  
  if (holdUntil < millis()) {
    if (pir.movement()) {
      Serial.print(millis());
      Serial.println(" no motion");
      holdUntil = millis() + 1000;
    }
  
    if (pir.noMotion()) {
      Serial.print(millis());
      Serial.println(" movement");
      holdUntil = millis() + 1000;
    }
  }

}

