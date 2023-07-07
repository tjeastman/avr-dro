#include "label.h"

Label::Label(const char *value, const Font &font, const Color &color): value_{value}, font_{font}, color_{color}, changed_{true}
{
    for (signed char i = 0; i < 32 && value_[i] != '\0'; ++i) {
        shape_.expand(Direction::RIGHT, font_.character(value_[i])->shape, 1);
    }
}


void Label::draw(Canvas canvas)
{
    if (!changed_) {
        return;
    }

    for (signed char i = 0; i < 32 && value_[i] != '\0'; ++i) {
        const Character *character = font_.character(value_[i]);
        character->draw(canvas, color_);
        canvas.adjust(Direction::RIGHT, character->shape, 1);
    }
    changed_ = false;
}
