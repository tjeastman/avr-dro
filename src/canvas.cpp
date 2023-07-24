#include "canvas.h"

Canvas::Canvas(Display &display): display_{display}, index_{0}
{
    positions_[0].x = 0;
    positions_[0].y = 0;
}

void Canvas::save()
{
    if (++index_ < 7) {
        positions_[index_] = positions_[index_ - 1];
        colors_[index_] = colors_[index_ - 1];
    }
}

void Canvas::restore()
{
    if (index_ > 0) {
        index_--;
    }
}

void Canvas::move(Position position)
{
    positions_[index_] = position;
}

void Canvas::adjust(Direction direction, Shape shape, signed char buffer)
{
    positions_[index_].adjust(direction, shape, buffer);
}

void Canvas::select(Color color)
{
    colors_[index_] = color;
}

void Canvas::dimension(Shape shape) const
{
    display_.address(positions_[index_].x,
                     positions_[index_].y,
                     positions_[index_].x + shape.width - 1,
                     positions_[index_].y + shape.height - 1);
}

void Canvas::fill(Shape shape) const
{
    unsigned int value = colors_[index_].value();
    for (int i = 0; i < shape.height; ++i) {
        for (int j = 0; j < shape.width; ++j) {
            display_.data(value);
        }
    }
}

void Canvas::fill(Shape shape, Color color, unsigned char alpha) const
{
    unsigned int value = colors_[index_].blend(color, alpha).value();
    for (int i = 0; i < shape.height; ++i) {
        for (int j = 0; j < shape.width; ++j) {
            display_.data(value);
        }
    }
}

void Canvas::dot(Color color, unsigned char alpha, int n) const
{
    unsigned int value = colors_[index_].blend(color, alpha).value();
    for (int i = 0; i < n; ++i) {
        display_.data(value);
    }
}
