#ifndef _TestClockInterface_h
#define _TestClockInterface_h

#include <cstdint>
#include "../ClockInterface.h"

class TestClockInterface : public ClockInterface {
public:

    TestClockInterface();

    virtual void sleepMs(uint16_t ms) const;
    virtual void sleepUs(uint16_t us) const;
};

#endif
