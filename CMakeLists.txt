cmake_minimum_required(VERSION 3.18)

find_program(AVR_CC avr-gcc REQUIRED)
find_program(AVR_SIZE avr-size REQUIRED)
find_program(AVR_OBJCOPY avr-objcopy REQUIRED)
find_program(AVR_FLASH avrdude REQUIRED)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_C_COMPILER ${AVR_CC})

project(pendant LANGUAGES C)

add_compile_definitions(F_CPU=16000000L)
add_compile_options(-mmcu=atmega328p -Os)
add_link_options(-mmcu=atmega328p)

add_subdirectory(src)
