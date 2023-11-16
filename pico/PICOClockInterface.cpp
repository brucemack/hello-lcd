#include <iostream>

#include "pico/stdlib.h"

#include "PICOClockInterface.h"

using namespace std;

void PICOClockInterface::sleepMs(uint16_t ms) const {
    cout << "SLEEP " << ms << "ms" << endl;
    sleep_ms(ms);    
}

void PICOClockInterface::sleepUs(uint16_t us) const {
    cout << "SLEEP " << us << "us" << endl;
    sleep_us(us);
}

