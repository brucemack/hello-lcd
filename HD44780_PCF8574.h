#ifndef _HD44780_PCF8574_H
#define _HD44780_PCF8574_H

#include "HD44780.h"
#include "I2CInterface.h"
#include "ClockInterface.h"

/**
 * Used to interface with an HD44780-based LCD display via an I2C
 * interface using a PCF8574.
 * 
 * We have no choice but to use 4-bit mode since the PCF8574 module
 * only has 8 bits and a few bits are needed for the control signals.
*/
class HD44780_PCF8574 : public HD44780 {
public:
    
    HD44780_PCF8574(uint8_t displayLines, bool fontMode,
        uint8_t i2cAddr,
        I2CInterface* i2c, ClockInterface* clk);

protected:

    virtual void _writeDR8(uint8_t d);
    virtual void _writeIR8(uint8_t d);
    virtual uint8_t _readDR8();
    virtual uint8_t _readIR8();
    virtual void _writeDR8Multi(const uint8_t* d, uint16_t dLen);

    virtual void _waitUs(uint16_t ms) const;

private:

    void _write8(bool rsBit, uint8_t d);
    uint8_t _read8(bool rsBit);

    uint8_t _i2cAddr;
    I2CInterface* _i2c;
    ClockInterface* _clk;
    bool _backLight = true;
};

#endif
