#include "coordinate.h"

#include "ui/button.h"
#include "ui/canvas.h"
#include "ui/common.h"
#include "ui/grid.h"

const unsigned char CoordinateAxis::digits[2] = {3, 2};

const char *CoordinateAxis::unit = "mm";

CoordinateAxis::CoordinateAxis(char identifier):
    origin_{0},
    position_{0},
    label{identifier, ':', 0},
    zero{identifier, '0', 0}
{
}

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

CoordinateSystem::CoordinateSystem(): axes_{{'X'}, {'Y'}, {'Z'}}
{
}

CoordinateAxis &CoordinateSystem::axis(int index)
{
    return axes_[index];
}

CoordinateResetButton::CoordinateResetButton(CoordinateAxis &axis):
    Button(axis.zero),
    axis_{axis}
{
}

void CoordinateResetButton::release(ui::Position position)
{
    axis_.reset();
    Button::release(position);
}

CoordinatePanelRow::CoordinatePanelRow(CoordinateSystem &system, int index):
    Grid(ui::Direction::RIGHT, 20),
    axis_{system.axis(index)},
    label_{axis_.label},
    decimal_{axis_.digits[0], axis_.digits[1]},
    label_unit_{axis_.unit},
    button_{axis_}
{
    add(&label_);
    add(&decimal_);
    add(&label_unit_);
    add(&button_);
}

void CoordinatePanelRow::draw(ui::Canvas canvas)
{
    decimal_.update(axis_.position());
    Grid::draw(canvas);
}

CoordinatePanel::CoordinatePanel(CoordinateSystem &system):
    Grid{ui::Direction::DOWN, 20},
    row_{{system, 0}, {system, 1}, {system, 2}}
{
    add(&row_[0]);
    add(&row_[1]);
    add(&row_[2]);
}
