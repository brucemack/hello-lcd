#ifndef _TestHD44780_h
#define _TestHD44780_h

#include "HD44780.h"

class TestHD44780 : public HD44780 {
public:

    TestHD44780(bool isFourBit, uint8_t displayLines, bool fontMode);

protected:

    virtual void writeDR(uint8_t d);
    virtual void writeIR(uint8_t d);
    virtual uint8_t readDR();
    virtual uint8_t readIR();
};

#endif
