#include <iostream>
#include <iomanip>

#include "hardware/i2c.h"

#include "PICOI2CInterface.h"

using namespace std;

PICOI2CInterface::PICOI2CInterface(i2c_inst_t* hw, ostream& str) 
:   _hw(hw),
    _str(str) { 
}

PICOI2CInterface::~PICOI2CInterface() {
}

void PICOI2CInterface::write(uint8_t addr, uint8_t data) {
    //int rc = i2c_write_blocking(i2c0, addr, &data, 1, false);
    int rc = i2c_write_blocking(_hw, addr, &data, 1, false);
    if (rc != 1) {
        cout << "WRITE ERROR" << endl;
    }
    _cycleCount++;
}

void PICOI2CInterface::write(uint8_t addr, uint8_t* data, uint16_t len) {
    int rc = i2c_write_blocking(_hw, addr, data, len, false);
    if (rc != len) {
        cout << "WRITE ERROR" << endl;
    }
    _cycleCount++;
}

uint8_t PICOI2CInterface::read(uint8_t addr) {
    uint8_t data = 0;
    int rc = i2c_read_blocking(_hw, addr, &data, 1, false);
    if (rc != 1) {
        cout << "READ ERROR" << endl;
    }
    _cycleCount++;
    return data;
}
