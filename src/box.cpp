#include "box.h"
#include "color.h"

Box::Box(Control *control, Color &color): control_{control}, hidden_{false}, color_{color}
{
    shape_.width = 4;
    shape_.height = 4;
    if (control_ != nullptr) {
        shape_.width += control_->shape().width;
        shape_.height += control_->shape().height;
    }
};

void Box::draw(Canvas canvas) const
{
    Shape shape{0, 0};
    unsigned char alpha = hidden_ ? 0: 3;
    unsigned char alpha1 = 0;
    unsigned char alpha2 = 0;
    if (alpha != 0) {
        alpha1 = alpha - 1;
        alpha2 = alpha - 2;
    }

    // left side
    shape.width = 2;
    shape.height = shape_.height + 4;
    canvas.dimension(shape);
    canvas.fill(shape, color_, alpha);

    // top side
    shape.width = shape_.width + 4;
    shape.height = 2;
    canvas.dimension(shape);
    canvas.fill(shape, color_, alpha);

    // bottom side
    canvas.adjust(Direction::DOWN, shape_, 2);
    canvas.dimension(shape);
    canvas.dot(color_, alpha, 1);
    canvas.dot(color_, alpha1, shape_.width + 3);
    canvas.dot(color_, alpha2, shape_.width + 4);
    canvas.adjust(Direction::UP, shape_, -2);

    // right side
    shape.width = 1;
    shape.height = shape_.height + 4;
    canvas.adjust(Direction::RIGHT, shape_, 2);
    canvas.dimension(shape);
    canvas.dot(color_, alpha, 1);
    canvas.dot(color_, alpha1, shape_.height + 2);
    canvas.dot(color_, alpha2, 1);
    canvas.adjust(Direction::LEFT, shape_, -2);

    canvas.adjust(Direction::RIGHT, shape_, 3);
    canvas.dimension(shape);
    canvas.dot(color_, alpha2, shape_.height + 4);
    canvas.adjust(Direction::LEFT, shape_, -3);

    if (control_ != nullptr) {
        shape.width = 0;
        shape.height = 0;
        canvas.adjust(Direction::RIGHT, shape, 2);
        canvas.adjust(Direction::DOWN, shape, 2);
        control_->draw(canvas);
    }
}

InvisibleBox::InvisibleBox(Control *control): control_{control}
{
    shape_.width = 4;
    shape_.height = 4;
    if (control_ != nullptr) {
        shape_.width += control_->shape().width;
        shape_.height += control_->shape().height;
    }
};

void InvisibleBox::draw(Canvas canvas) const
{
    Shape shape{0, 0};
    if (control_ != nullptr) {
        canvas.adjust(Direction::RIGHT, shape, 2);
        canvas.adjust(Direction::DOWN, shape, 2);
        control_->draw(canvas);
    }
}
