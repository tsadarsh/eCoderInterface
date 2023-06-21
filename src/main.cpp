#include <Arduino.h>
#include "eCoderInterface.h"

eCoderInterface encoder;

void setup() {
  encoder.setPins();
  Serial.begin(9600);
}

void loop() {
  if(encoder.update()) 
  {
    Serial.println(encoder.position());
  }
  else 
  {
    Serial.println("CRC Error!");
  }
  delay(100);
}
