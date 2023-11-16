#include <iostream>
#include "HD44780_PCF8574.h"
#include "tests/TestHD44780.h"
#include "tests/TestI2CInterface.h"
#include "tests/TestClockInterface.h"
#include "pico/PICOI2CInterface.h"
#include "pico/PICOClockInterface.h"

using namespace std;

int main(int argc, const char** argv) {

    //TestHD44780 display(false, 2, false, cout);
    //TestI2CInterface i2c(cout);
    //TestClockInterface clk;
    PICOI2CInterface i2c(cout);
    PICOClockInterface clk;
    uint8_t addr = 0x27;
    // 4-bit interface, 2 rows, 5x8 characters
    HD44780_PCF8574 display(2, false, addr, &i2c, &clk);

    cout << "----- Init" << endl;
    display.init();
    cout << "----- Clear" << endl;
    display.clearDisplay();
    cout << "----- Set Display" << endl;
    display.setDisplay(true, true, true);
    cout << "----- Set Entry Mode" << endl;
    display.setEntryMode(true, false);  // Move sursor, no shift
    cout << "----- Write H" << endl;
    display.write(0x48); // H
    cout << "----- Write I" << endl;
    display.write(0x49); // I

    return 0;
}
