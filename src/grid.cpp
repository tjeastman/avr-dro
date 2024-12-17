#include "grid.h"

Grid::Grid(Direction direction, char padding):
    count_{0},
    direction_{direction},
    padding_{padding}
{
    for (signed char i = 0; i < 8; ++i) {
        controls_[i] = nullptr;
    }
}

void Grid::draw(Canvas canvas)
{
    Shape shape{0, 0};
    if (direction_ == Direction::RIGHT) {
        shape.width = padding_;
    } else if (direction_== Direction::DOWN) {
        shape.height = padding_;
    } else {
        return;
    }

    for (signed char i = 0; i < count_; ++i) {
        canvas.adjust(direction_, shape, padding_);
        Control *control = controls_[i];
        control->draw(canvas);
        shape = control->shape();
    }
}

void Grid::add(Control *control)
{
    if (count_ < 8) {
        controls_[count_++] = control;
        shape_.expand(direction_, control->shape(), padding_);
    }
}

void Grid::press(Position position)
{
    Control *c = control(&position);
    if (c != nullptr) {
        c->press(position);
    }
}

void Grid::release(Position position)
{
    Control *c = control(&position);
    if (c != nullptr) {
        c->release(position);
    }
}

Control *Grid::control(Position *position)
{
    Direction direction;
    if (direction_ == Direction::RIGHT) {
        direction = Direction::LEFT;
    } else if (direction_ == Direction::DOWN) {
        direction = Direction::UP;
    } else {
        return nullptr;
    }

    for (signed char i = 0; i < count_; ++i) {
        if (controls_[i]->contains(*position)) {
            return controls_[i];
        }
        position->adjust(direction, controls_[i]->shape(), padding_);
    }

    return nullptr;
}
