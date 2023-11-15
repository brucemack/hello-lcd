#include "HD44780.h"

HD44780::HD44780(bool isFourBit, uint8_t displayLines, bool fontMode) 
:   _isFourBit(isFourBit),
    _displayLines(displayLines),
    _fontMode(fontMode) {
}

void HD44780::init() {
    // 8-bit initialization sequence
    if (!_isFourBit) {
        _waitMs(15);
        _writeIR8(0x30);
        _waitMs(5);
        _writeIR8(0x30);
        _waitMs(1);
        _writeIR8(0x30);
        _waitMs(1);
        // Now we setup the usual way
        uint8_t word = 0x30;
        if (_displayLines == 2) {
            word |= 0x08;
        }
        if (_fontMode) {
            word |= 0x04;
        }
        _writeIR(word);
    }
    // 4-bit initialization 
    else {
        _waitMs(15);
        _writeIR8(0x30);
        _waitMs(5);
        _writeIR8(0x30);
        _waitMs(1);
        _writeIR8(0x30);
        // Switch modes
        _writeIR8(0x20);
        _waitMs(10);
        // Now we setup the usual way
        uint8_t word = 0x20;
        if (_displayLines == 2) {
            word |= 0x08;
        }
        if (_fontMode) {
            word |= 0x04;
        }
        _writeIR(word);
    }
}

void HD44780::clearDisplay() {
    waitUntilNotBusy();
    _writeIR(0x01);
}

void HD44780::returnHome() {
    waitUntilNotBusy();
    _writeIR(0x02);
}

void HD44780::setEntryMode(bool increment, bool shift) {
    uint8_t word = 0x04;
    word |= increment ? 0x02 : 0x00;
    word |= shift ? 0x01 : 0x00;
    waitUntilNotBusy();
    _writeIR(word);
}

void HD44780::setDisplay(bool displayOn, bool cursorOn, bool blinkOn) {    
    uint8_t word = 0x08;
    word |= displayOn ? 0x04 : 0x00;
    word |= cursorOn ? 0x02 : 0x00;
    word |= blinkOn ? 0x01 : 0x00;
    waitUntilNotBusy();
    _writeIR(word);
}

void HD44780::setCGRAMAddr(uint8_t a) {
    waitUntilNotBusy();
    _writeIR(0x40 | (a & 0b00111111));
}

void HD44780::setDDRAMAddr(uint8_t a) {
    waitUntilNotBusy();
    _writeIR(0x80 | (a & 0b01111111));
}

void HD44780::write(uint8_t d) {
    // TODO: FIND OUT IF THE BUSY FLAG APPLIES TO DATA
    waitUntilNotBusy();
    _writeDR(d);
}

uint8_t HD44780::read() {
    return _readDR();
}

bool HD44780::isBusy() const {
    return (_readIR() & 0x80) != 0;
}

// TODO: CONSIDER A TIMEOUT FEATURE
void HD44780::waitUntilNotBusy() const {
    //while (isBusy()) { }
}

void HD44780::_writeDR(uint8_t d){
    if (_isFourBit) {
        _writeDR8((d & 0xf0) >> 4);
        _writeDR8((d & 0x0f));
    } else {
        _writeDR8(d);
    }
}

void HD44780::_writeIR(uint8_t d) {
    if (_isFourBit) {
        _writeIR8((d & 0xf0) >> 4);
        _writeIR8((d & 0x0f));
    } else {
        _writeIR8(d);
    }
}

uint8_t HD44780::_readDR() {
    if (_isFourBit) {
        uint8_t result = _readDR8() << 4;
        result |= _readDR8() & 0x0f;
        return result;
    } else {
        return _readDR8();
    }
}

uint8_t HD44780::_readIR() const {
    if (_isFourBit) {
        uint8_t result = _readIR8() << 4;
        result |= _readIR8() & 0x0f;
        return result;
    } else {
        return _readIR8();
    }
}

