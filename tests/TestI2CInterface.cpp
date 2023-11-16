#include <iostream>
#include <iomanip>
#include "TestI2CInterface.h"

using namespace std;

TestI2CInterface::TestI2CInterface(std::ostream& str) 
:   _str(str) { 
}

void TestI2CInterface::write(uint8_t addr, uint8_t data) {
    _str << "I2C WRITE ADDR: ";
    _str << setfill('0') << setw(2) << hex << (int)addr;
    _str << " DATA: ";
    _str << setfill('0') << setw(2) << hex << (int)data;
    _str << endl;
}

void TestI2CInterface::write(uint8_t addr, uint8_t* data, uint16_t len) {
    _str << "I2C WRITE ADDR: " << setfill('0') << setw(2) << hex << (int)addr;
    _str << endl;
    _str << " DATA: [";
    for (uint16_t i = 0; i < len; i++) {
        _str << setfill('0') << setw(2) << hex << (int)data[i] << " ";
    }
    _str << "]" << endl;
}

uint8_t TestI2CInterface::read(uint8_t addr) {
    return 0;
}
