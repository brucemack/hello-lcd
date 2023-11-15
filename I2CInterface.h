#ifndef _I2CInterface_h
#define _I2CInterface_h

#include <cstdint>

class I2CInterface {
public:

    I2CInterface();

    virtual void write(uint8_t addr, uint8_t data);
    virtual void write(uint8_t addr, uint8_t* data, uint16_t len);
}

#endif
