cmake_minimum_required(VERSION 3.18)

find_program(AVR_CXX avr-g++ REQUIRED)
find_program(AVR_SIZE avr-size REQUIRED)
find_program(AVR_OBJCOPY avr-objcopy REQUIRED)
find_program(AVR_FLASH avrdude REQUIRED)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_CXX_COMPILER ${AVR_CXX})

project(pendant LANGUAGES CXX)

add_compile_definitions(F_CPU=16000000L)
add_compile_options(-mmcu=atmega2560 -Os -Werror -Wall -Wextra)
add_link_options(-mmcu=atmega2560)

add_subdirectory(src)
