#ifndef PALETTE_H_
#define PALETTE_H_

#include "color.h"

class Palette {
private:
    static unsigned char scale_[2][32];
    unsigned int colors_[4];
public:
    Palette(Color, Color);
    unsigned int color(unsigned char) const;
};

#endif
