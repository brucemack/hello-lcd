#ifndef _I2CInterface_h
#define _I2CInterface_h

#include <cstdint>

class I2CInterface {
public:

    virtual void write(uint8_t addr, uint8_t data) = 0;
    virtual void write(uint8_t addr, uint8_t* data, uint16_t len) = 0;
    virtual uint8_t read(uint8_t addr) = 0;

};

#endif
