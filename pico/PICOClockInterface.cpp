#include <iostream>

#include "pico/stdlib.h"

#include "PICOClockInterface.h"

using namespace std;

void PICOClockInterface::sleepMs(uint16_t ms) const {
    sleep_ms(ms);    
}

void PICOClockInterface::sleepUs(uint16_t us) const {
    sleep_us(us);
}

