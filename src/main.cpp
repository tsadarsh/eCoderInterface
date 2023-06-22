#include <Arduino.h>
#include "eCoderInterface.h"

eCoderInterface encoder;

void setup() {
  encoder.setPins();
  encoder.setResolution = 21; //todo
  Serial.begin(9600);
}

void loop() {
  if(encoder.update()) 
  {
    Serial.println(encoder.normalize(encoder.position()));
  }
  else 
  {
    Serial.println("CRC Error!");
  }
  delay(100);
}
