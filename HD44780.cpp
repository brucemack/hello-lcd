#include "HD44780.h"

HD44780::HD44780(bool isFourBit, uint8_t displayLines, bool fontMode) 
:   _isFourBit(isFourBit),
    _displayLines(displayLines),
    _fontMode(fontMode) {
}

void HD44780::clearDisplay() {
    writeIR(0x01);
}



