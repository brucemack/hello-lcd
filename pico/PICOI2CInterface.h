#ifndef _PICOI2CInterface_h
#define _PICOI2CInterface_h

#include <iostream>
#include "../I2CInterface.h"

/**
 * Interface with PICO hardware
 */
class PICOI2CInterface : public I2CInterface {
public:

    PICOI2CInterface(i2c_inst_t* hw, std::ostream& str);
    virtual ~PICOI2CInterface();

    virtual void write(uint8_t addr, uint8_t data);
    virtual void write(uint8_t addr, uint8_t* data, uint16_t len);
    virtual uint8_t read(uint8_t addr);

    uint16_t getCycleCount() const { return _cycleCount; };

private:

    i2c_inst_t* _hw;
    std::ostream& _str;
    uint16_t _cycleCount = 0;
};

#endif
