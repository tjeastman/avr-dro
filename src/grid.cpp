#include "grid.h"

Grid::Grid(Direction direction): count_{0}, direction_{direction}
{
    for (signed char i = 0; i < 8; ++i) {
        controls_[i] = nullptr;
    }
};

void Grid::draw(Canvas &canvas) const
{
    canvas.save();
    for (signed char i = 0; i < count_; ++i) {
        Control *control = controls_[i];
        control->draw(canvas);
        canvas.adjust(direction_, control->shape(), 4);
    }
    canvas.restore();
}

void Grid::add(Control *control)
{
    if (count_ < 8) {
        controls_[count_++] = control;
        shape_.expand(direction_, control->shape(), 4);
    }
}
