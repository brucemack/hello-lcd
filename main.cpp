#include <iostream>
#include "HD44780_PCF8574.h"
#include "tests/TestHD44780.h"
#include "tests/TestI2CInterface.h"
#include "tests/TestClockInterface.h"

using namespace std;

int main(int argc, const char** argv) {

    //TestHD44780 display(false, 2, false, cout);
    TestI2CInterface i2c(cout);
    TestClockInterface clk;
    uint8_t addr = 0x27;
    // 4-bit interface, 2 rows, 5x8 characters
    HD44780_PCF8574 display(2, false, addr, &i2c, &clk);

    display.init();
    display.clearDisplay();
    display.setDisplay(true, true, true);
    display.setEntryMode(true, false);  // Move sursor, no shift
    display.write(0x48); // H
    display.write(0x49); // H

    return 0;
}
