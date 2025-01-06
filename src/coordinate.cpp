#include "coordinate.h"

#include "ui/button.h"
#include "ui/canvas.h"
#include "ui/common.h"
#include "ui/decimal.h"
#include "ui/grid.h"

int CoordinateAxis::position() const
{
    return position_ - origin_;
}

void CoordinateAxis::project(int position)
{
    position_ = position;

}

void CoordinateAxis::reset()
{
    origin_ = position_;
}

CoordinateAxis &CoordinateSystem::axis(int index)
{
    return axes_[index];
}

void CoordinateSystem::project(const int position[3])
{
    axes_[0].project(position[0]);
    axes_[1].project(position[1]);
    axes_[2].project(position[2]);
}

CoordinateDecimal::CoordinateDecimal(const CoordinateAxis &axis):
    Decimal(3, 2),
    axis_{axis}
{
}

void CoordinateDecimal::draw(ui::Canvas canvas)
{
    Decimal::update(axis_.position());
    Decimal::draw(canvas);
}

CoordinateResetButton::CoordinateResetButton(CoordinateAxis &axis, const char *text):
    Button(text),
    axis_{axis}
{
}

void CoordinateResetButton::release(ui::Position position)
{
    axis_.reset();
    Button::release(position);
}

CoordinateAxisGrid::CoordinateAxisGrid(CoordinateAxis &axis, char identifier):
    Grid(ui::Direction::RIGHT, 20),
    label_text_{identifier, ':', '\0'},
    label_{label_text_},
    decimal_{axis},
    label_unit_{"mm"},
    button_text_{identifier, '0', '\0'},
    button_{axis, button_text_}
{
    add(&label_);
    add(&decimal_);
    add(&label_unit_);
    add(&button_);
}

CoordinatePanel::CoordinatePanel(CoordinateSystem &system):
    Grid{ui::Direction::DOWN, 20},
    row_{{system.axis(0), 'X'}, {system.axis(1), 'Y'}, {system.axis(2), 'Z'}}
{
    add(&row_[0]);
    add(&row_[1]);
    add(&row_[2]);
}
