#include "canvas.h"

namespace ui {

Canvas::Canvas(const Display &display):
    display_{display},
    position_{0, 0},
    color_{0, 0, 0}
{
}

void Canvas::move(const Position &position)
{
    position_ = position;
}

void Canvas::adjust(Direction direction, const Shape &shape, signed char buffer)
{
    position_.adjust(direction, shape, buffer);
}

void Canvas::select(const Color &color)
{
    color_ = color;
}

void Canvas::dimension(const Shape &shape) const
{
    display_.address(position_.x,
                     position_.y,
                     position_.x + shape.width - 1,
                     position_.y + shape.height - 1);
}

void Canvas::fill(const Shape &shape) const
{
    unsigned int value = color_.value();
    for (int i = 0; i < shape.height; ++i) {
        for (int j = 0; j < shape.width; ++j) {
            display_.data(value);
        }
    }
}

void Canvas::fill(const Shape &shape, const Color &color, unsigned char alpha) const
{
    unsigned int value = color_.blend(color, alpha).value();
    for (int i = 0; i < shape.height; ++i) {
        for (int j = 0; j < shape.width; ++j) {
            display_.data(value);
        }
    }
}

void Canvas::dot(const Color &color, unsigned char alpha, int n) const
{
    unsigned int value = color_.blend(color, alpha).value();
    for (int i = 0; i < n; ++i) {
        display_.data(value);
    }
}

}  // namespace ui
