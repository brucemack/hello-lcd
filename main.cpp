#include "TestHD44780.h"

int main(int argc, const char** argv) {

    TestHD44780 display(false, 2, false);
    display.clearDisplay();

    return 0;
}

