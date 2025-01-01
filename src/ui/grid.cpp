#include "grid.h"

UI::Grid::Grid(const UI::ControlProperties &properties, Direction direction, char padding):
    Control(properties),
    count_{0},
    direction_{direction},
    padding_{padding}
{
    for (signed char i = 0; i < 8; ++i) {
        controls_[i] = nullptr;
    }
}

void UI::Grid::draw(Canvas canvas)
{
    for (signed char i = 0; i < count_; ++i) {
        Control *control = controls_[i];
        control->draw(canvas);
        canvas.adjust(direction_, control->shape(), padding_);
    }
}

void UI::Grid::add(Control *control)
{
    if (count_ < 8) {
        controls_[count_++] = control;
        shape_.expand(direction_, control->shape(), padding_);
    }
}

void UI::Grid::press(Position position)
{
    Control *c = control(&position);
    if (c != nullptr) {
        c->press(position);
    }
}

void UI::Grid::release(Position position)
{
    Control *c = control(&position);
    if (c != nullptr) {
        c->release(position);
    }
}

UI::Control *UI::Grid::control(Position *position)
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
