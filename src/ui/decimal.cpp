#include "decimal.h"

#include <stdint.h>

#include "canvas.h"
#include "integer.h"

namespace ui {

Decimal::Decimal(unsigned char n, unsigned char m):
    value_{0},
    divisor_{1},
    changed_{true},
    integer_{n},
    fractional_{m}
{
    shape_.expand(Direction::RIGHT, properties_.font.character('-')->shape(), 1);
    shape_.expand(Direction::RIGHT, integer_.shape(), 0);
    shape_.expand(Direction::RIGHT, properties_.font.character('.')->shape(), 1);
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
    const Character *character = properties_.font.character('-');
    if (value_ < 0) {
        character->draw(canvas, properties_.color);
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
    const Character *character = properties_.font.character('.');
    character->draw(canvas, properties_.color);
    canvas.adjust(Direction::RIGHT, character->shape(), 1);
}

}  // namespace ui
