#include <stdint.h>

#include "decimal.h"

Decimal::Decimal(unsigned char n, unsigned char m, const Font &font, const Color &color):
    font_{font},
    color_{color},
    integer_{n, font, color},
    fractional_{m, font, color},
    changed_{true},
    value_{0},
    divisor_{1}
{
    shape_.expand(Direction::RIGHT, font_.character('-')->shape(), 1);
    shape_.expand(Direction::RIGHT, integer_.shape(), 0);
    shape_.expand(Direction::RIGHT, font_.character('.')->shape(), 1);
    shape_.expand(Direction::RIGHT, fractional_.shape(), 0);

    for (unsigned char i = 0; i < m; ++i) {
        divisor_ *= 10;
    }
}

void Decimal::update(int value)
{
    if (value_ == value) {
        return;
    }

    // safely calculate absolute value
    unsigned int magnitude;
    if (value >= 0) {
        magnitude = value;
    } else if (value > INT16_MIN) {
        magnitude = -value;
    } else {
        magnitude = INT16_MAX;
        magnitude++;
    }

    integer_.update(magnitude / divisor_);
    fractional_.update(magnitude % divisor_);

    value_ = value;
    changed_ = true;
}

void Decimal::draw(Canvas canvas)
{
    if (!changed_) {
        return;
    }

    draw_sign(canvas);
    draw_integer(canvas);
    draw_dot(canvas);
    fractional_.draw(canvas);

    changed_ = false;
}

void Decimal::draw_sign(Canvas &canvas)
{
    const Character *character = font_.character('-');
    if (value_ < 0) {
        character->draw(canvas, color_);
    } else {
        canvas.dimension(character->shape());
        canvas.fill(character->shape());
    }
    canvas.adjust(Direction::RIGHT, character->shape(), 1);
}

void Decimal::draw_integer(Canvas &canvas)
{
    integer_.draw(canvas);
    canvas.adjust(Direction::RIGHT, integer_.shape(), 0);
}

void Decimal::draw_dot(Canvas &canvas)
{
    const Character *character = font_.character('.');
    character->draw(canvas, color_);
    canvas.adjust(Direction::RIGHT, character->shape(), 1);
}
