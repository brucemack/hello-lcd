#ifndef _ClockInterface_h
#define _ClockInterface_h

#include <cstdint>

class ClockInterface {
public:

    virtual void sleepMs(uint16_t ms) const = 0;
    virtual void sleepUs(uint16_t us) const = 0;
};

#endif
