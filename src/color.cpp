#include <stdint.h>

#include "color.h"

Color::Color(uint8_t red, uint8_t green, uint8_t blue) {
    value = ((red & 0x1f) << 11) | (((2 * green) & 0x3f) << 5) | (blue & 0x1f);
}

uint8_t Color::R() {
    return value >> 11;
}

uint8_t Color::G() {
    return (value >> 6) & 0x1f;
}

uint8_t Color::B() {
    return value & 0x1f;
}
