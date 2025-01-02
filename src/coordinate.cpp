#include "coordinate.h"

#include "ui/button.h"
#include "ui/canvas.h"
#include "ui/common.h"
#include "ui/decimal.h"
#include "ui/grid.h"

CoordinateDecimal::CoordinateDecimal(unsigned char n, unsigned char m):
    Decimal(n, m),
    origin_{0}
{
}

void CoordinateDecimal::update(int position)
{
    Decimal::update(position - origin_);
}

void CoordinateDecimal::reset()
{
    origin_ = value_ + origin_;
    Decimal::update(0);
}

CoordinateResetButton::CoordinateResetButton(const char *text, CoordinateDecimal &decimal):
    Button(text),
    decimal_{decimal}
{
}

void CoordinateResetButton::release(ui::Position position)
{
    decimal_.reset();
    Button::release(position);
}

CoordinateAxisGrid::CoordinateAxisGrid(char identifier):
    Grid(ui::Direction::RIGHT, 20),
    label_text_{identifier, ':', '\0'},
    label_{label_text_},
    decimal_{3, 2},
    label_unit_{"mm"},
    button_text_{identifier, '0', '\0'},
    button_{button_text_, decimal_}
{
    add(&label_);
    add(&decimal_);
    add(&label_unit_);
    add(&button_);
}

void CoordinateAxisGrid::set(int position)
{
    decimal_.update(position);
}

CoordinateFeedGrid::CoordinateFeedGrid():
    Grid(ui::Direction::RIGHT, 20),
    label_{"F:"},
    decimal_{3, 1},
    label_unit_{"mm/min"}
{
    add(&label_);
    add(&decimal_);
    add(&label_unit_);
}

void CoordinateFeedGrid::set(int rate)
{
    decimal_.update(rate);
}

CoordinatePanel::CoordinatePanel():
    Grid{ui::Direction::DOWN, 20},
    axes_{{'X'}, {'Y'}, {'Z'}},
    feed_{}
{
    add(&axes_[0]);
    add(&axes_[1]);
    add(&axes_[2]);
    add(&feed_);
}

void CoordinatePanel::set(const int position[3], int rate)
{
    axes_[0].set(position[0]);
    axes_[1].set(position[1]);
    axes_[2].set(position[2]);
    feed_.set(rate);
}

void CoordinateSystem::project(const int position[3], int rate) const
{
    panel_.set(position, rate);
}
