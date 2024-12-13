#include "target.h"

Target::Target(int size, const Color &color): color_{color}, pressed_{false}
{
    shape_.width = size;
    shape_.height = size;
}

void Target::draw(Canvas canvas)
{
    Shape shape{0, 0};

    // left side
    shape.width = 2;
    shape.height = shape_.height;
    canvas.dimension(shape);
    canvas.fill(shape, color_, 3);

    // top side
    shape.width = shape_.width;
    shape.height = 2;
    canvas.dimension(shape);
    canvas.fill(shape, color_, 3);

    // bottom side
    canvas.adjust(Direction::DOWN, shape_, -2);
    canvas.dimension(shape);
    canvas.dot(color_, 3, 1);
    canvas.dot(color_, 2, shape_.width - 1);
    canvas.dot(color_, 1, shape_.width);
    canvas.adjust(Direction::UP, shape_, -2);

    // right side
    shape.width = 1;
    shape.height = shape_.height;
    canvas.adjust(Direction::RIGHT, shape_, -2);
    canvas.dimension(shape);
    canvas.dot(color_, 3, 1);
    canvas.dot(color_, 2, shape_.height - 2);
    canvas.dot(color_, 1, 1);
    canvas.adjust(Direction::LEFT, shape_, -2);

    canvas.adjust(Direction::RIGHT, shape_, -1);
    canvas.dimension(shape);
    canvas.dot(color_, 1, shape_.height);
    canvas.adjust(Direction::LEFT, shape_, -1);

    // middle
    if (pressed_) {
        shape.width = 2;
        shape.height = 2;
        canvas.adjust(Direction::RIGHT, shape, 0);
        canvas.adjust(Direction::DOWN, shape, 0);
        shape.width = shape_.width - 4;
        shape.height = shape_.height - 4;
        canvas.dimension(shape);
        canvas.fill(shape, color_, 2);
    }
}

void Target::press(Position position)
{
    pressed_ = true;
}

void Target::release(Position position)
{
    pressed_ = false;
}
