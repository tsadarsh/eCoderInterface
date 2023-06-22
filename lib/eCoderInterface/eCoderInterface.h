#ifndef eCoderInterface_h
#define eCoderInterface_h

#include <Arduino.h>
#include <stdint.h>


class eCoderInterface
{
    uint8_t CM = 0b00000010;
    uint8_t bytesIn[6];
    uint8_t CRC_8X1[9];
    void CRC_8X1_TAB_Creat(void);
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
        uint8_t update();
        EncoderData dataStruct();
        uint8_t* raw();
        uint32_t position();
        StatusField status();
        uint8_t CRC_C(uint8_t* CRCbuf, uint8_t Length);
        uint8_t setResolution = 21;
};

#endif