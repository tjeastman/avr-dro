include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(
  main.elf
  main.cpp
  canvas.cpp
  color.cpp
  common.cpp
  display.cpp
  ui/font.cpp
  ui/integer.cpp
  ui/label.cpp
  ui/grid.cpp
  touch.cpp
  calibration.cpp
  coordinate.cpp
  ui/decimal.cpp
  ui/button.cpp
  pendant.cpp
)

set_property(TARGET main.elf PROPERTY CXX_STANDARD 17)

add_custom_command(
  TARGET main.elf
  POST_BUILD
  COMMAND ${AVR_SIZE} --mcu=atmega2560 main.elf
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
  COMMAND ${AVR_FLASH} -v -p atmega2560 -c wiring -P /dev/ttyUSB0 -b 115200 -D -U flash:w:main.hex
)
