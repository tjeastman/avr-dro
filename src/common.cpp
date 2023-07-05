#include "common.h"

void Shape::expand(Direction direction, Shape shape, signed char buffer)
{
    if (direction == Direction::RIGHT || direction == Direction::LEFT) {
        width += shape.width + buffer;
        height = shape.height > height ? shape.height : height;
    } else if (direction == Direction::DOWN || direction == Direction::UP) {
        width = shape.width > width ? shape.width : width;
        height += shape.height + buffer;
    }
}

void Position::adjust(Direction direction, Shape shape, signed char buffer)
{
    if (direction == Direction::LEFT) {
        x -= shape.width - buffer;
    } else if (direction == Direction::UP) {
        y -= shape.height - buffer;
    } else if (direction == Direction::RIGHT) {
        x += shape.width + buffer;
    } else if (direction == Direction::DOWN) {
        y += shape.height + buffer;
    }
}
