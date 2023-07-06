#include "integer.h"

Integer::Integer(int value, Font &font): value_{value}, font_{font}
{
    shape_.expand(Direction::RIGHT, font_.character('-')->shape, 1);
    for (unsigned int divisor = 10000; divisor > 0; divisor /= 10) {
        shape_.expand(Direction::RIGHT, font_.digit(value_.magnitude / divisor)->shape, 1);
    }
    shape_.width -= 1;
};

Integer::Value::Value(int v)
{
    negative = v < 0 ? true : false;
    value = v;
    if (magnitude != 0x8000 && negative) {
        magnitude = ~magnitude;
        magnitude += 1;
    }
}

void Integer::draw_sign(Canvas &canvas) const
{
    const Character *character = font_.character('-');
    if (value_.negative) {
        character->draw(canvas);
    } else {
        canvas.dimension(character->shape);
        canvas.fill(character->shape, 0);
    }
    canvas.adjust(Direction::RIGHT, character->shape, 1);
}

void Integer::draw_magnitude(Canvas &canvas) const
{
    for (unsigned int divisor = 10000; divisor > 0; divisor /= 10) {
        const Character *character = font_.digit(value_.magnitude / divisor);
        character->draw(canvas);
        canvas.adjust(Direction::RIGHT, character->shape, 1);
    }
}

void Integer::draw(Canvas &canvas) const
{
    canvas.save();
    draw_sign(canvas);
    draw_magnitude(canvas);
    canvas.restore();
}

void Integer::update(int v)
{
    value_ = Value(v);
}
