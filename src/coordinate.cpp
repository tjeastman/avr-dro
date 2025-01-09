#include "coordinate.h"

#include "pendant.h"
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

CoordinateAxisGrid::CoordinateAxisGrid(char identifier, CoordinateDecimal &decimal):
    Grid(ui::Direction::RIGHT, 20),
    label_text_{identifier, ':', '\0'},
    label_{label_text_},
    decimal_{decimal},
    label_unit_{"mm"},
    button_text_{identifier, '0', '\0'},
    button_{button_text_, decimal_}
{
    add(&label_);
    add(&decimal_);
    add(&label_unit_);
    add(&button_);
}

CoordinateFeedGrid::CoordinateFeedGrid(ui::Decimal &decimal):
    Grid(ui::Direction::RIGHT, 20),
    label_{"F:"},
    decimal_{decimal},
    label_unit_{"mm/min"}
{
    add(&label_);
    add(&decimal_);
    add(&label_unit_);
}

CoordinateGrid::CoordinateGrid(CoordinateDecimal &decimal0, CoordinateDecimal &decimal1, CoordinateDecimal &decimal2, ui::Decimal &decimal):
    Grid{ui::Direction::DOWN, 20},
    axes_{{'X', decimal0}, {'Y', decimal1}, {'Z', decimal2}},
    feed_{decimal}
{
    add(&axes_[0]);
    add(&axes_[1]);
    add(&axes_[2]);
    add(&feed_);
}

void CoordinatePanel::project(PendantAxis::Identifier identifier, int position, int rate)
{
    if (identifier == PendantAxis::Identifier::X) {
        decimals_[0].update(position);
    } else if (identifier == PendantAxis::Identifier::Y) {
        decimals_[1].update(position);
    } else if (identifier == PendantAxis::Identifier::Z) {
        decimals_[2].update(position);
    }
    decimal_.update(rate);
}

CoordinatePanel::CoordinatePanel():
    decimals_{{3, 2}, {3, 2}, {3, 2}},
    decimal_{3, 1},
    grid_{decimals_[0], decimals_[1], decimals_[2], decimal_}
{
}

void CoordinatePanel::dispatch(Touch &touch)
{
    touch.dispatch(grid_);
}

void CoordinatePanel::draw(ui::Canvas &canvas)
{
    grid_.draw(canvas);
}
