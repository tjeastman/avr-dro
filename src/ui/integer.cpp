#include <stdint.h>

#include "integer.h"

namespace ui {

unsigned int UnsignedInteger::divisors_[5] = {10000, 1000, 100, 10, 1};

UnsignedInteger::UnsignedInteger(const ControlProperties &properties, unsigned char digits):
    Control(properties),
    digits_{digits},
    changed_{true},
    magnitude_{0}
{
    for (int i = 0; i < digits_; ++i) {
        shape_.expand(Direction::RIGHT, properties_.font.digit(0)->shape(), 1);
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
        const Character *character = properties_.font.digit(magnitude_ / divisors_[i]);
        character->draw(canvas, properties_.color);
        canvas.adjust(Direction::RIGHT, character->shape(), 1);
    }

    changed_ = true;
}

}  // namespace ui
