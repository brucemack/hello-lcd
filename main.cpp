#include <iostream>

#ifdef PICO_BUILD
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#endif

#include "HD44780_PCF8574.h"
#include "tests/TestHD44780.h"
#include "tests/TestI2CInterface.h"
#include "tests/TestClockInterface.h"

#ifdef PICO_BUILD
#include "pico/PICOI2CInterface.h"
#include "pico/PICOClockInterface.h"
#endif

#define I2C0_SDA 4 // Pin 6: I2C channel 0 - data
#define I2C0_SCL 5 // Pin 7: I2C channel 0 - clock
#define LED_PIN (25)

using namespace std;

uint32_t get_us() {
    absolute_time_t at = get_absolute_time();
    return to_us_since_boot(at);
}

const char* testPattern = "0123456789ABCDEF01230123456789ABCDEF01230123456789ABCDEF01230123456789ABCDEF0123";

int main(int argc, const char** argv) {

#ifdef PICO_BUILD
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
#endif

    //TestHD44780 display(false, 2, false, cout);
#ifdef PICO_BUILD
    PICOI2CInterface i2c(i2c0, cout);
    PICOClockInterface clk;
#else
    TestI2CInterface i2c(cout);
    TestClockInterface clk;
#endif

    // Use the scanner to find this address
    uint8_t addr = 0x27;
    // 4-bit interface, 2 rows, 5x8 characters
    HD44780_PCF8574 display(2, false, addr, &i2c, &clk);

    printf("\nLCD Test\n");
    
    cout << "----- Init" << endl;
    display.init();
    cout << "----- Set Display" << endl;
    display.setDisplay(false, false, false);
    cout << "----- Clear" << endl;
    display.clearDisplay();
    
    cout << "----- Set Entry Mode" << endl;
    display.setEntryMode(true, false);  // Move sursor, no shift
    cout << "----- Set Display" << endl;
    display.setDisplay(true, true, true);
    cout << "----- Home" << endl;
    display.returnHome();
    cout << "----- Set DDRAM Address" << endl;
    display.setDDRAMAddr(0);
    // This is an important test - it should demonstrate a wrap-around

    cout << "----- Write Message" << endl;
    uint32_t start = get_us();
    //display.writeLinear(HD44780::Format::FMT_20x4, 
    //    (uint8_t*)"Hi Izzy and Henry! This is a test.", 34, 0);
    display.writeLinear(HD44780::Format::FMT_20x4, 
        (uint8_t*)testPattern, 80, 0);
    uint32_t end = get_us();
    display.setCursor(HD44780::Format::FMT_20x4, 0, 0);
    display.setCursorLinear(HD44780::Format::FMT_20x4, 0);
    
    cout << "I2C cycles: " << i2c.getCycleCount() << endl;
    cout << "Busy Count: " << display.getBusyCount() << endl;
    cout << "Time: " << (end - start) << endl;

    // Prevent exit
    while (1) { }

    return 0;
}
