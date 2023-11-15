#include <iostream>
#include <iomanip>
#include "TestHD44780.h"

using namespace std;

TestHD44780::TestHD44780(bool isFourBit, uint8_t displayLines, bool fontMode)
:   HD44780(isFourBit, displayLines, fontMode) {
}

void TestHD44780::writeDR(uint8_t d) {
    cout << "WRITE DR: " << setfill('0') << setw(2) << right << hex << (int)d << endl;
}

void TestHD44780::writeIR(uint8_t d) {
    cout << "WRITE IR: " << setfill('0') << setw(2) << right << hex << (int)d << endl;
}

uint8_t TestHD44780::readDR() {
    return 0;
}

uint8_t TestHD44780::readIR() {
    return 0;
}