#include "label.h"

Label::Label(const char *value, Font &font): value_{value}, font_{font}
{
    for (signed char i = 0; i < 32 && value_[i] != '\0'; ++i) {
        shape_.expand(Direction::RIGHT, font_.character(value_[i])->shape, 1);
    }
};

void Label::draw(Canvas &canvas) const
{
    canvas.save();
    for (signed char i = 0; i < 32 && value_[i] != '\0'; ++i) {
        const Character *character = font_.character(value_[i]);
        character->draw(canvas);
        canvas.adjust(Direction::RIGHT, character->shape, 1);
    }
    canvas.restore();
}
