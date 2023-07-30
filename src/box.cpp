#include "box.h"
#include "color.h"

Box::Box(Control *control, Color color, bool hidden): control_{control}, color_{color}, hidden_{hidden}
{
    shape_.width = 4;
    shape_.height = 4;
    if (control_ != nullptr) {
        shape_.width += control_->shape().width;
        shape_.height += control_->shape().height;
    }
}

Box::Box(Control *control): Box{control, Color{0, 0, 0}, true}
{
}

void Box::draw(Canvas canvas) const
{
    Shape shape{0, 0};

    if (hidden_) {
        // left side
        shape.width = 2;
        shape.height = shape_.height + 4;
        canvas.dimension(shape);
        canvas.fill(shape, color_, 0);

        // right side
        canvas.adjust(Direction::RIGHT, shape_, 2);
        canvas.dimension(shape);
        canvas.fill(shape, color_, 0);
        canvas.adjust(Direction::LEFT, shape_, -2);

        // top side
        shape.width = shape_.width + 4;
        shape.height = 2;
        canvas.dimension(shape);
        canvas.fill(shape, color_, 0);

        // bottom side
        canvas.adjust(Direction::DOWN, shape_, 2);
        canvas.dimension(shape);
        canvas.dot(color_, 0, 2 * shape_.width + 8);
        canvas.adjust(Direction::UP, shape_, -2);
    } else {
        // left side
        shape.width = 2;
        shape.height = shape_.height + 4;
        canvas.dimension(shape);
        canvas.fill(shape, color_, 3);

        // top side
        shape.width = shape_.width + 4;
        shape.height = 2;
        canvas.dimension(shape);
        canvas.fill(shape, color_, 3);

        // bottom side
        canvas.adjust(Direction::DOWN, shape_, 2);
        canvas.dimension(shape);
        canvas.dot(color_, 3, 1);
        canvas.dot(color_, 2, shape_.width + 3);
        canvas.dot(color_, 1, shape_.width + 4);
        canvas.adjust(Direction::UP, shape_, -2);

        // right side
        shape.width = 1;
        shape.height = shape_.height + 4;
        canvas.adjust(Direction::RIGHT, shape_, 2);
        canvas.dimension(shape);
        canvas.dot(color_, 3, 1);
        canvas.dot(color_, 2, shape_.height + 2);
        canvas.dot(color_, 1, 1);
        canvas.adjust(Direction::LEFT, shape_, -2);

        canvas.adjust(Direction::RIGHT, shape_, 3);
        canvas.dimension(shape);
        canvas.dot(color_, 1, shape_.height + 4);
        canvas.adjust(Direction::LEFT, shape_, -3);
    }

    if (control_ != nullptr) {
        shape.width = 0;
        shape.height = 0;
        canvas.adjust(Direction::RIGHT, shape, 2);
        canvas.adjust(Direction::DOWN, shape, 2);
        control_->draw(canvas);
    }
}
