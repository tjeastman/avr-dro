#include <stdint.h>

#include "integer.h"

unsigned int Integer::divisors_[5] = {10000, 1000, 100, 10, 1};

Integer::Integer(unsigned char digits, const Font &font, const Color &color):
    digits_{digits},
    magnitude_{0},
    font_{font},
    color_{color}
{
    for (int i = 0; i < digits_; ++i) {
        shape_.expand(Direction::RIGHT, font_.digit(0)->shape, 1);
    }
}

void Integer::draw(Canvas canvas)
{
    for (int i = 5 - digits_; i < 5; ++i) {
        const Character *character = font_.digit(magnitude_ / divisors_[i]);
        character->draw(canvas, color_);
        canvas.adjust(Direction::RIGHT, character->shape, 1);
    }
}

UnsignedInteger::UnsignedInteger(unsigned char digits, const Font &font, const Color &color):
  Integer(digits, font, color)
{
}

void UnsignedInteger::update(unsigned int value)
{
    magnitude_ = value;
}

SignedInteger::SignedInteger(unsigned char digits, const Font &font, const Color &color):
  Integer(digits, font, color),
  negative_{false}
{
    shape_.expand(Direction::RIGHT, font_.character('-')->shape, 1);
}

void SignedInteger::draw(Canvas canvas)
{
    const Character *character = font_.character('-');
    if (negative_) {
        character->draw(canvas, color_);
    } else {
        canvas.dimension(character->shape);
        canvas.fill(character->shape);
    }
    canvas.adjust(Direction::RIGHT, character->shape, 1);

    Integer::draw(canvas);
}

void SignedInteger::update(int value)
{
    if (value >= 0) {
        magnitude_ = value;
        negative_ = false;
    } else if (value > INT16_MIN) {
        magnitude_ = -value;
        negative_ = true;
    } else {
        magnitude_ = INT16_MAX;
        magnitude_++;
        negative_ = true;
    }
}
