cmake_minimum_required(VERSION 3.13)
# OPTIONAL!
include(pico_sdk_import.cmake)
project(hello-lcd C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# PICO build
pico_sdk_init()

add_executable(main
  main.cpp HD44780.cpp HD44780_PCF8574.cpp 
  tests/TestI2CInterface.cpp tests/TestClockInterface.cpp
  pico/PICOI2CInterface.cpp pico/PICOClockInterface.cpp
)
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 1)
target_compile_definitions(main PUBLIC PICO_BUILD=1)

target_link_libraries(main pico_stdlib hardware_i2c)
