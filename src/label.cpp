#include "label.h"

Label::Label(const char *text, const Font &font, const Color &color):
    text_{text},
    font_{font},
    color_{color},
    changed_{true}
{
    for (signed char i = 0; i < 32 && text_[i] != '\0'; ++i) {
        shape_.expand(Direction::RIGHT, font_.character(text_[i])->shape, 1);
    }
}


void Label::draw(Canvas canvas)
{
    if (!changed_) {
        return;
    }

    for (signed char i = 0; i < 32 && text_[i] != '\0'; ++i) {
        const Character *character = font_.character(text_[i]);
        character->draw(canvas, color_);
        canvas.adjust(Direction::RIGHT, character->shape, 1);
    }
    changed_ = false;
}
