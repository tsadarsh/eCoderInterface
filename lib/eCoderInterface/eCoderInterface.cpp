#include <Arduino.h>
#include <HardwareSerial.h>
#include "board.h"
#include "eCoderInterface.h"

// Call this method {in setup()} before polling `update` method.
void eCoderInterface::setPins() {
  pinMode(RE_, OUTPUT);
  pinMode(DE, OUTPUT);
  pinMode(RO, INPUT);
  pinMode(DI, OUTPUT);
  digitalWrite(RE_, LOW);
  Serial2.begin(2500000);
}

// Returns 0 if there is a CRC error. Else returns 1
uint8_t eCoderInterface::update() {
  digitalWrite(DE, HIGH);
  Serial2.write(this->CM);
  delayMicroseconds(1);
  digitalWrite(DE, LOW);
  Serial2.readBytes(this->bytesIn, sizeof(this->bytesIn));
  data.cm = this->bytesIn[0];
  data.sa.info = (this->bytesIn[1] >> 4) & 0x0F;
  data.sa.error = (this->bytesIn[1] >> 2) & 0x03;
  data.sa.alarm = this->bytesIn[1] & 0x03;
  data.pos = ((uint32_t) this->bytesIn[2]) | ((uint32_t) this->bytesIn[3] << 8) | ((uint32_t) this->bytesIn[4] << 16);
  data.crc = this->bytesIn[5];
  
  uint8_t CRC_error = this->CRC_C(this->bytesIn, sizeof(this->bytesIn)-1);
  if (CRC_error) {
    return 0;
  }
  return 1;
}

eCoderInterface::EncoderData eCoderInterface::dataStruct() {
    return this->data;
}

uint32_t eCoderInterface::position() {
  if (this->setResolution >= this->MAX_Resolution)
    return this->data.pos;
  else
    return this->data.pos >> (this->MAX_Resolution - this->setResolution);
}

double eCoderInterface::normalize(uint32_t data) {
  if (this->setResolution >= this->MAX_Resolution)
    return (data/(double)(1<<this->MAX_Resolution));
  else
    return (data/(double)(1<<this->setResolution));
}

eCoderInterface::StatusField eCoderInterface::status() {
    return this->data.sa;
}

uint8_t* eCoderInterface::raw() {
  return this->bytesIn;
}

void eCoderInterface::CRC_8X1_TAB_Creat(void) {
  uint16_t i, j;
  uint8_t CRCResult;
  for(j=0; j<8; j++) {
    CRCResult = j;
    for(i=0; i<8; i++) {
      if(CRCResult & 0x80) {
        CRCResult = (CRCResult << 1) ^ 0x01;
      }
      else {
        CRCResult <<= 1;
      }
    }
    CRC_8X1[j] = (CRCResult & 0x00ff);
  }
}

uint8_t eCoderInterface::CRC_C(uint8_t *CRCbuf, uint8_t Length) {
  this->CRC_8X1_TAB_Creat();
  uint8_t CRCResult = 0;
  uint8_t CRCLength = 0;
  while(CRCLength < Length) {
    CRCResult ^= CRCbuf[CRCLength];
    CRCResult = (CRCResult & 0x00ff);
    CRCLength++;
    CRCResult = this->CRC_8X1[CRCResult];
  }
  return CRCResult;
}

