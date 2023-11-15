cmake_minimum_required(VERSION 3.13)
project(hello-lcd C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
add_executable(main
  main.cpp HD44780.cpp TestHD44780.cpp
)
#target_link_libraries(main )
