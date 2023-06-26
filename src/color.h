#ifndef COLOR_H_
#define COLOR_H_

#include <stdint.h>

struct Color {
    uint16_t value;
    Color(uint8_t, uint8_t, uint8_t);
    uint8_t R();
    uint8_t G();
    uint8_t B();
};

#endif
