#include <Arduino.h>
#include "eCoderInterface.h"

eCoderInterface encoder;

void setup() {
  encoder.setPins();
  Serial.begin(2000000);
  encoder.setResolution = 20;
}

void loop() {
  encoder.update();
  Serial.println(encoder.normalize(encoder.position()), 15);
  delay(1);
}
