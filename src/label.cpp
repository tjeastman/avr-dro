#include "label.h"

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
