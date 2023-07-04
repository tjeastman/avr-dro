#include "common.h"

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
