#include "button.h"
#include "common.h"

Button::Button(const ControlProperties &properties, const char *text):
    Control(properties),
    text_{text},
    pressed_{false},
    changed_{true}
{
    for (signed char i = 0; i < 32 && text_[i] != '\0'; ++i) {
        shape_.expand(Direction::RIGHT, properties_.font.character(text_[i])->shape(), 1);
    }
    shape_.width += 16;
    shape_.height += 8;
}

void Button::draw(Canvas canvas)
{
    if (!changed_) {
        return;
    }

    Shape shape{0, 0};

    // left side
    shape.width = 2;
    shape.height = shape_.height;
    canvas.dimension(shape);
    canvas.fill(shape, properties_.color, 3);

    // top side
    shape.width = shape_.width;
    shape.height = 2;
    canvas.dimension(shape);
    canvas.fill(shape, properties_.color, 3);

    // bottom side
    canvas.adjust(Direction::DOWN, shape_, -2);
    canvas.dimension(shape);
    canvas.dot(properties_.color, 3, 1);
    canvas.dot(properties_.color, 2, shape_.width - 1);
    canvas.dot(properties_.color, 1, shape_.width);
    canvas.adjust(Direction::UP, shape_, -2);

    // right side
    shape.width = 1;
    shape.height = shape_.height;
    canvas.adjust(Direction::RIGHT, shape_, -2);
    canvas.dimension(shape);
    canvas.dot(properties_.color, 3, 1);
    canvas.dot(properties_.color, 2, shape_.height - 2);
    canvas.dot(properties_.color, 1, 1);
    canvas.adjust(Direction::LEFT, shape_, -2);

    canvas.adjust(Direction::RIGHT, shape_, -1);
    canvas.dimension(shape);
    canvas.dot(properties_.color, 1, shape_.height);
    canvas.adjust(Direction::LEFT, shape_, -1);

    // label
    shape.width = 8;
    shape.height = 4;
    canvas.adjust(Direction::RIGHT, shape, 0);
    canvas.adjust(Direction::DOWN, shape, 0);

    for (signed char i = 0; i < 32 && text_[i] != '\0'; ++i) {
        const Character *character = properties_.font.character(text_[i]);
        character->draw(canvas, properties_.color);
        canvas.adjust(Direction::RIGHT, character->shape(), 1);
    }

    changed_ = false;
}
