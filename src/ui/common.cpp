#include "common.h"

namespace ui {

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

bool Shape::contains(int x, int y) const
{
    if (x < 0) {
        return false;
    } else if (y < 0) {
        return false;
    } else if (x >= width) {
        return false;
    } else if (y >= height) {
        return false;
    }
    return true;
}

void Position::adjust(Direction direction, Shape shape, signed char buffer)
{
    if (direction == Direction::LEFT) {
        x -= shape.width + buffer;
    } else if (direction == Direction::UP) {
        y -= shape.height + buffer;
    } else if (direction == Direction::RIGHT) {
        x += shape.width + buffer;
    } else if (direction == Direction::DOWN) {
        y += shape.height + buffer;
    }
}

} // namespace ui
