#ifndef _PICOI2CInterface_h
#define _PICOI2CInterface_h

#include <iostream>
#include "../I2CInterface.h"

/**
 * A dummy implementation that prints data activity to a stream. Useful
 * for unit testing.
*/
class PICOI2CInterface : public I2CInterface {
public:

    PICOI2CInterface(std::ostream& str);

    virtual void write(uint8_t addr, uint8_t data);
    virtual void write(uint8_t addr, uint8_t* data, uint16_t len);
    virtual uint8_t read(uint8_t addr);

private:

    std::ostream& _str;
};

#endif
