#include <iostream>

//#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"

#include "HD44780_PCF8574.h"
#include "tests/TestHD44780.h"
#include "tests/TestI2CInterface.h"
#include "tests/TestClockInterface.h"
#include "pico/PICOI2CInterface.h"
#include "pico/PICOClockInterface.h"

#define I2C0_SDA 4 // Pin 6: I2C channel 0 - data
#define I2C0_SCL 5 // Pin 7: I2C channel 0 - clock
#define LED_PIN (25)

using namespace std;

int main(int argc, const char** argv) {

    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    // This example will use I2C0 on the default SDA and SCL pins (GP4, GP5 on a Pico)
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    
    gpio_put(LED_PIN, 1);
    sleep_ms(1000);
    gpio_put(LED_PIN, 0);
    sleep_ms(1000);

    //TestHD44780 display(false, 2, false, cout);
    //TestI2CInterface i2c(cout);
    //TestClockInterface clk;
    PICOI2CInterface i2c(cout);
    PICOClockInterface clk;
    uint8_t addr = 0x27;
    // 4-bit interface, 2 rows, 5x8 characters
    HD44780_PCF8574 display(2, false, addr, &i2c, &clk);

    gpio_put(LED_PIN, 1);
    sleep_ms(1000);
    gpio_put(LED_PIN, 0);
    sleep_ms(1000);

    // I2C SCAN
    printf("\nLCD Test\n");
    
    cout << "----- Init" << endl;
    display.init();
    cout << "----- Clear" << endl;
    display.clearDisplay();
    cout << "----- Set Display" << endl;
    display.setDisplay(true, true, true);
    cout << "----- Set Entry Mode" << endl;
    display.setEntryMode(true, false);  // Move sursor, no shift
    cout << "----- Set DDRAM Address" << endl;
    display.setDDRAMAddr(0);
    cout << "----- Write H" << endl;
    display.write(0x48); // H
    cout << "----- Write I" << endl;
    display.write(0x49); // I
    
    while (1) {
        gpio_put(LED_PIN, 0);
        sleep_ms(1000);
        gpio_put(LED_PIN, 1);
        sleep_ms(1000);
    }

    return 0;
}
