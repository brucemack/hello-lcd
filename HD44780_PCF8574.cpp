#include "HD44780_PCF8574.h"

HD44780_PCF8574::HD44780_PCF8574(uint8_t displayLines, bool fontMode,
    uint8_t i2cAddr, I2CInterface* i2c, ClockInterface* clk) 
:   HD44780(true, displayLines, fontMode), 
    _i2cAddr(i2cAddr),
    _i2c(i2c),
    _clk(clk) {
}

void HD44780_PCF8574::_write8(bool rsBit, uint8_t d) {
    // Move the LCD data up to the high 4 bits of the I2C data
    uint8_t w0 = d << 4;
    // Turn on the backlight
    if (_backLight) {
        w0 |= 0b1000;
    } 
    // Turn on the RS bit
    if (rsBit) {
        w0 |= 1;
    }
    // Write with EN=0
    _i2c->write(_i2cAddr, (w0));
    // Write with EN=1
    _i2c->write(_i2cAddr, (w0 | 0b100));
    _clk->sleepUs(1);
    // Write with EN=0
    _i2c->write(_i2cAddr, (w0));
    _clk->sleepUs(50);
}

void HD44780_PCF8574::_writeDR8(uint8_t d) {
    _write8(true, d);
}

void HD44780_PCF8574::_writeIR8(uint8_t d) {
    _write8(false, d);
}

uint8_t HD44780_PCF8574::_readDR8() {
    return 0;
}

uint8_t HD44780_PCF8574::_readIR8() const {
    return 0;
}

void HD44780_PCF8574::_waitMs(uint16_t ms) const {
    _clk->sleepMs(ms);
}


