#include "TestClockInterface.h"

#include <iostream>

using namespace std;

TestClockInterface::TestClockInterface() {
}

void TestClockInterface::sleepMs(uint16_t ms) const {
    cout << "SLEEP MS " << dec << ms << endl;
}

void TestClockInterface::sleepUs(uint16_t us) const {
    cout << "SLEEP US " << dec << us << endl;
}
