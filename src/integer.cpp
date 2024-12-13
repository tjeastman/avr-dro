#include "integer.h"

Integer::Integer(int value, const Font &font, const Color &color):
    value_{value},
    font_{font},
    color_{color},
    changed_{true}
{
    shape_.expand(Direction::RIGHT, font_.character('-')->shape, 1);
    for (unsigned int divisor = 10000; divisor > 0; divisor /= 10) {
        shape_.expand(Direction::RIGHT, font_.digit(value_.magnitude / divisor)->shape, 1);
    }
}

Integer::Value::Value(int v)
{
    negative = v < 0 ? true : false;
    value = v;
    if (magnitude != 0x8000 && negative) {
        magnitude = ~magnitude;
        magnitude += 1;
    }
}

void Integer::draw_sign(Canvas &canvas)
{
    const Character *character = font_.character('-');
    if (value_.negative) {
        character->draw(canvas, color_);
    } else {
        canvas.dimension(character->shape);
        canvas.fill(character->shape);
    }
    canvas.adjust(Direction::RIGHT, character->shape, 1);
}

void Integer::draw_magnitude(Canvas &canvas)
{
    for (unsigned int divisor = 10000; divisor > 0; divisor /= 10) {
        const Character *character = font_.digit(value_.magnitude / divisor);
        character->draw(canvas, color_);
        canvas.adjust(Direction::RIGHT, character->shape, 1);
    }
}

void Integer::draw(Canvas canvas)
{
    if (changed_) {
        changed_ = false;
        draw_sign(canvas);
        draw_magnitude(canvas);
    }
}

void Integer::update(int v)
{
    value_ = Value(v);
    changed_ = true;
}
