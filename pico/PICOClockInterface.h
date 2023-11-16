#ifndef _PICOClockInterface_h
#define _PICOClockInterface_h

#include <cstdint>
#include "../ClockInterface.h"

class PICOClockInterface : public ClockInterface {
public:

    virtual void sleepMs(uint16_t ms) const;
    virtual void sleepUs(uint16_t us) const;
};

#endif
