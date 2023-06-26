#ifndef PALETTE_H_
#define PALETTE_H_

#include <stdint.h>

#include "color.h"

class Palette {
private:
    uint16_t colors_[4];
    static uint8_t scale_[2][32];
public:
    Palette(Color, Color);
    uint16_t color(uint8_t);
};

#endif
