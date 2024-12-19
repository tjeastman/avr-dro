#include <stdint.h>

#include "integer.h"

unsigned int UnsignedInteger::divisors_[5] = {10000, 1000, 100, 10, 1};

UnsignedInteger::UnsignedInteger(unsigned char digits, const Font &font, const Color &color):
    font_{font},
    color_{color},
    digits_{digits},
    changed_{true},
    magnitude_{0}
{
    for (int i = 0; i < digits_; ++i) {
        shape_.expand(Direction::RIGHT, font_.digit(0)->shape(), 1);
    }
}

void UnsignedInteger::update(unsigned int value)
{
    magnitude_ = value;
    changed_ = true;
}

void UnsignedInteger::draw(Canvas canvas)
{
    if (!changed_) {
        return;
    }

    for (int i = 5 - digits_; i < 5; ++i) {
        const Character *character = font_.digit(magnitude_ / divisors_[i]);
        character->draw(canvas, color_);
        canvas.adjust(Direction::RIGHT, character->shape(), 1);
    }

    changed_ = true;
}
