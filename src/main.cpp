#include <Arduino.h>
#include "eCoderInterface.h"

eCoderInterface encoder;

void setup() {
  encoder.setPins();
  Serial.begin(9600);
}

void loop() {
  encoder.update();
  Serial.println(encoder.position());
  delay(100);
}
