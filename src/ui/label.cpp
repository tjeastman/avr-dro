#include "label.h"

#include "canvas.h"
#include "common.h"
#include "control.h"
#include "font.h"

namespace ui {

Label::Label(const ControlProperties &properties, const char *text):
    Control(properties),
    text_{text},
    changed_{true}
{
    for (signed char i = 0; i < 32 && text_[i] != '\0'; ++i) {
        shape_.expand(Direction::RIGHT, properties_.font.character(text_[i])->shape(), 1);
    }
}

void Label::draw(Canvas canvas)
{
    if (!changed_) {
        return;
    }

    for (signed char i = 0; i < 32 && text_[i] != '\0'; ++i) {
        const Character *character = properties_.font.character(text_[i]);
        character->draw(canvas, properties_.color);
        canvas.adjust(Direction::RIGHT, character->shape(), 1);
    }

    changed_ = false;
}

}  // namespace ui
