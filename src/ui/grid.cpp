#include "grid.h"

#include <stdint.h>

#include "canvas.h"
#include "common.h"
#include "control.h"

namespace ui {

Grid::Grid(Direction direction, int8_t padding)
    : count_ { 0 }
    , direction_ { direction }
    , padding_ { padding }
{
    for (int8_t i = 0; i < 8; ++i) {
        controls_[i] = nullptr;
    }
}

void Grid::draw(Canvas canvas)
{
    for (int8_t i = 0; i < count_; ++i) {
        Control* control = controls_[i];
        control->draw(canvas);
        canvas.adjust(direction_, control->shape(), padding_);
    }
}

void Grid::add(Control* control)
{
    if (count_ < 8) {
        controls_[count_++] = control;
        shape_.expand(direction_, control->shape(), padding_);
    }
}

void Grid::press(Position position)
{
    Control* c = control(&position);
    if (c != nullptr) {
        c->press(position);
    }
}

void Grid::release(Position position)
{
    Control* c = control(&position);
    if (c != nullptr) {
        c->release(position);
    }
}

Control* Grid::control(Position* position)
{
    Direction direction;
    if (direction_ == Direction::RIGHT) {
        direction = Direction::LEFT;
    } else if (direction_ == Direction::DOWN) {
        direction = Direction::UP;
    } else {
        return nullptr;
    }

    for (int8_t i = 0; i < count_; ++i) {
        if (controls_[i]->contains(*position)) {
            return controls_[i];
        }
        position->adjust(direction, controls_[i]->shape(), padding_);
    }

    return nullptr;
}

} // namespace ui
