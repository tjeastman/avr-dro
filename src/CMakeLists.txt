include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(
  main.elf
  main.c
)

add_custom_command(
  TARGET main.elf
  POST_BUILD
  COMMAND ${AVR_SIZE} --mcu=atmega328p main.elf
)

add_custom_command(
  TARGET main.elf
  POST_BUILD
  BYPRODUCTS main.hex
  COMMAND ${AVR_OBJCOPY} -j .text -j .data -O ihex main.elf main.hex
)

add_custom_target(
  flash
  DEPENDS main.hex
  COMMAND ${AVR_FLASH} -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -D -U flash:w:main.hex
)
