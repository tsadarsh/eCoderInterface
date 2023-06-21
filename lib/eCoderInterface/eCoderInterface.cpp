#include <Arduino.h>
#include <HardwareSerial.h>
#include "board.h"
#include "eCoderInterface.h"

void eCoderInterface::setPins() {
  pinMode(RE_, OUTPUT);
  pinMode(DE, OUTPUT);
  pinMode(RO, INPUT);
  pinMode(DI, OUTPUT);
  digitalWrite(RE_, LOW);
  Serial2.begin(2500000);
}

void eCoderInterface::update() {
  digitalWrite(DE, HIGH);
  Serial2.write(this->CM);
  delayMicroseconds(1);
  digitalWrite(DE, LOW);
  Serial2.readBytes(this->bytesIn, sizeof(this->bytesIn));
  data.cm = this->bytesIn[0];
  data.sa.info = (this->bytesIn[1] >> 4) & 0x0F;
  data.sa.error = (this->bytesIn[1] >> 2) & 0x03;
  data.sa.alarm = this->bytesIn[1] & 0x03;
  data.pos = (uint32_t) this->bytesIn[2] | ((uint32_t) this->bytesIn[3] << 8) | ((uint32_t) this->bytesIn[4] << 16);
  data.crc = this->bytesIn[5];
}

eCoderInterface::EncoderData eCoderInterface::raw() {
    return this->data;
}

uint32_t eCoderInterface::position() {
    return this->data.pos;
}

eCoderInterface::StatusField eCoderInterface::status() {
    return this->data.sa;
}


