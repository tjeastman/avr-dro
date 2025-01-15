#include "coordinate.h"

#include "pendant.h"
#include "ui/button.h"
#include "ui/canvas.h"
#include "ui/common.h"
#include "ui/decimal.h"
#include "ui/grid.h"

CoordinateLabel::CoordinateLabel(const char* text)
    : Label(text)
    , selected_ { false }
{
    ui::Shape shape { 30, 0 };
    shape_.expand(ui::Direction::RIGHT, shape, 0);
}

void CoordinateLabel::draw(ui::Canvas canvas)
{
    if (!changed_) {
        return;
    }

    draw_selector(canvas);

    ui::Shape shape { 30, 0 };
    canvas.adjust(ui::Direction::RIGHT, shape, 0);
    Label::draw(canvas);
}

void CoordinateLabel::draw_selector(ui::Canvas canvas)
{
    ui::Shape shape { 0, 0 };

    canvas.adjust(ui::Direction::RIGHT, shape, 12);
    canvas.adjust(ui::Direction::DOWN, shape, 8);

    shape.width = 8;
    shape.height = shape_.height - 16;
    canvas.dimension(shape);
    canvas.fill(shape, properties_.color, selected_ ? 3 : 0);
}

void CoordinateLabel::select(bool selected)
{
    if (selected_ == selected) {
        return;
    }

    selected_ = selected;
    changed_ = true;
}

CoordinateDecimal::CoordinateDecimal(unsigned char n, unsigned char m)
    : Decimal(n, m)
    , origin_ { 0 }
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

CoordinateResetButton::CoordinateResetButton(const char* text, CoordinateDecimal& decimal)
    : Button(text)
    , decimal_ { decimal }
{
}

void CoordinateResetButton::release(ui::Position position)
{
    decimal_.reset();
    Button::release(position);
}

CoordinateAxisGrid::CoordinateAxisGrid(char axis)
    : Grid(ui::Direction::RIGHT, 20)
    , label_text_ { axis, ':', '\0' }
    , label_ { label_text_ }
    , decimal_ { 3, 2 }
    , label_unit_ { "mm" }
    , button_text_ { axis, '0', '\0' }
    , button_ { button_text_, decimal_ }
{
    add(&label_);
    add(&decimal_);
    add(&label_unit_);
    add(&button_);
}

void CoordinateAxisGrid::update(int position)
{
    decimal_.update(position);
    label_.select(true);
}

void CoordinateAxisGrid::select(bool selected)
{
    label_.select(selected);
}

CoordinateFeedGrid::CoordinateFeedGrid()
    : Grid(ui::Direction::RIGHT, 20)
    , label_ { "F:" }
    , decimal_ { 3, 1 }
    , label_unit_ { "mm/min" }
{
    add(&label_);
    add(&decimal_);
    add(&label_unit_);
}

void CoordinateFeedGrid::update(int rate)
{
    decimal_.update(rate);
}

CoordinateGrid::CoordinateGrid()
    : Grid { ui::Direction::DOWN, 20 }
    , axes_ { { 'X' }, { 'Y' }, { 'Z' } }
    , feed_ {}
{
    add(&axes_[0]);
    add(&axes_[1]);
    add(&axes_[2]);
    add(&feed_);
}

void CoordinateGrid::update(char axis, int position, int rate)
{
    axes_[0].select(false);
    axes_[1].select(false);
    axes_[2].select(false);

    if (axis == 'X') {
        axes_[0].update(position);
    } else if (axis == 'Y') {
        axes_[1].update(position);
    } else if (axis == 'Z') {
        axes_[2].update(position);
    }

    if (axis == 0) {
        feed_.update(0);
    } else {
        feed_.update(rate);
    }
}

void CoordinatePanel::project(char axis, int position, int rate)
{
    grid_.update(axis, position, rate);
}

void CoordinatePanel::dispatch(Touch& touch)
{
    touch.dispatch(grid_);
}

void CoordinatePanel::draw(ui::Canvas& canvas)
{
    grid_.draw(canvas);
}
