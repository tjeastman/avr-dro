#include "canvas.h"

Canvas::Canvas(Display &display, Palette &palette): display_(display), palette_(palette)
{
    positions_[0].x = 0;
    positions_[0].y = 0;
    position_index_ = 0;
}

void Canvas::save()
{
    if (position_index_ < 7) {
        positions_[position_index_ + 1] = positions_[position_index_];
        position_index_++;
    }
}

void Canvas::restore()
{
    if (position_index_ > 0) {
        position_index_--;
    }
}

void Canvas::move(Position position)
{
    positions_[position_index_] = position;
}

void Canvas::adjust(Direction direction, Shape shape, signed char buffer)
{
    positions_[position_index_].adjust(direction, shape, buffer);
}

void Canvas::dimension(Shape shape) const
{
    display_.address(positions_[position_index_].x,
                     positions_[position_index_].y,
                     positions_[position_index_].x + shape.width - 1,
                     positions_[position_index_].y + shape.height - 1);
}

void Canvas::fill(Shape shape, unsigned char c) const
{
    unsigned int color = palette_.color(c);
    for (int i = 0; i < shape.height; ++i) {
        for (int j = 0; j < shape.width; ++j) {
            display_.data(color);
        }
    }
}

void Canvas::dot(unsigned int c, int n) const
{
    unsigned int color = palette_.color(c);
    for (int i = 0; i < n; ++i) {
        display_.data(color);
    }
}
