#include "coordinate.h"

CoordinateSystem::CoordinateSystem(const Pendant &pendant):
    pendant_{pendant},
    axes_{{pendant, 'X'}, {pendant, 'Y'}, {pendant, 'Z'}}
{
}

CoordinateAxis &CoordinateSystem::axis(int index)
{
    return axes_[index];
}

const unsigned char CoordinateAxis::digits[2] = {3, 2};

const char *CoordinateAxis::unit = "mm";

CoordinateAxis::CoordinateAxis(const Pendant &pendant, char identifier):
    axis_{pendant.axis(identifier)},
    origin_{0},
    label{identifier, ':', 0},
    zero{identifier, '0', 0}
{
}

int CoordinateAxis::position() const
{
    return axis_.position(origin_);
}

void CoordinateAxis::reset()
{
    origin_ = axis_.position(0);
}

CoordinateResetButton::CoordinateResetButton(const UI::ControlProperties &properties, CoordinateAxis &axis):
    Button(properties, axis.zero),
    axis_{axis}
{
}

void CoordinateResetButton::release(UI::Position position)
{
    axis_.reset();
    Button::release(position);
}

CoordinatePanelRow::CoordinatePanelRow(const UI::ControlProperties &properties, CoordinateSystem &system, int index):
    Grid(properties, UI::Direction::RIGHT, 20),
    axis_{system.axis(index)},
    label_{properties, axis_.label},
    decimal_{properties, axis_.digits[0], axis_.digits[1]},
    label_unit_{properties, axis_.unit},
    button_{properties, axis_}
{
    add(&label_);
    add(&decimal_);
    add(&label_unit_);
    add(&button_);
}

void CoordinatePanelRow::draw(UI::Canvas canvas)
{
    decimal_.update(axis_.position());
    Grid::draw(canvas);
}

CoordinatePanel::CoordinatePanel(const UI::ControlProperties &properties, CoordinateSystem &system):
    Grid{properties, UI::Direction::DOWN, 20},
    row_{{properties, system, 0}, {properties, system, 1}, {properties, system, 2}}
{
    add(&row_[0]);
    add(&row_[1]);
    add(&row_[2]);
}
