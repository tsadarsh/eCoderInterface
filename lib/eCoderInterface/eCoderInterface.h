#ifndef eCoderInterface_h
#define eCoderInterface_h

#include <Arduino.h>
#include <stdint.h>


class eCoderInterface
{
    uint8_t CM = 0b00000010;
    uint8_t bytesIn[6];
    public:
        struct StatusField {
            uint8_t info;
            uint8_t error;
            uint8_t alarm;
        }sa;

        struct EncoderData {
            uint8_t cm;
            StatusField sa;
            uint32_t pos;
            uint8_t crc;
        } data;

        void setPins();
        void update();
        EncoderData raw();
        uint32_t position();
        StatusField status();

};

#endif