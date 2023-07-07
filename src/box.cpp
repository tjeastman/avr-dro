#include "box.h"
#include "color.h"

Box::Box(Control *control): control_{control}, hidden_{false}
{
    shape_.width = 4;
    shape_.height = 4;
    if (control_ != nullptr) {
        shape_.width += control_->shape().width;
        shape_.height += control_->shape().height;
    }
};

void Box::draw(Canvas &canvas) const
{
    Shape shape{0, 0};
    unsigned int color = hidden_ ? 0: 3;
    unsigned int color1 = 0;
    unsigned int color2 = 0;
    if (color != 0) {
        color1 = color - 1;
        color2 = color - 2;
    }

    // left side
    shape.width = 2;
    shape.height = shape_.height + 4;
    canvas.dimension(shape);
    canvas.fill(shape, color);

    // top side
    shape.width = shape_.width + 4;
    shape.height = 2;
    canvas.dimension(shape);
    canvas.fill(shape, color);

    // bottom side
    canvas.save();
    canvas.adjust(Direction::DOWN, shape_, 2);
    canvas.dimension(shape);
    canvas.dot(color, 1);
    canvas.dot(color1, shape_.width + 3);
    canvas.dot(color2, shape_.width + 4);
    canvas.restore();

    // right side
    shape.width = 1;
    shape.height = shape_.height + 4;
    canvas.save();
    canvas.adjust(Direction::RIGHT, shape_, 2);
    canvas.dimension(shape);
    canvas.dot(color, 1);
    canvas.dot(color1, shape_.height + 2);
    canvas.dot(color2, 1);
    canvas.restore();

    canvas.save();
    canvas.adjust(Direction::RIGHT, shape_, 3);
    canvas.dimension(shape);
    canvas.dot(color2, shape_.height + 4);
    canvas.restore();

    if (control_ != nullptr) {
        shape.width = 0;
        shape.height = 0;
        canvas.save();
        canvas.adjust(Direction::RIGHT, shape, 2);
        canvas.adjust(Direction::DOWN, shape, 2);
        control_->draw(canvas);
        canvas.restore();
    }
}

void InvisibleBox::draw(Canvas &canvas) const
{
    Shape shape{0, 0};
    if (control_ != nullptr) {
        canvas.save();
        canvas.adjust(Direction::RIGHT, shape, 2);
        canvas.adjust(Direction::DOWN, shape, 2);
        control_->draw(canvas);
        canvas.restore();
    }
}
