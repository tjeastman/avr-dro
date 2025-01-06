#ifndef COORDINATE_H_
#define COORDINATE_H_

#include "ui/button.h"
#include "ui/canvas.h"
#include "ui/common.h"
#include "ui/control.h"
#include "ui/decimal.h"
#include "ui/grid.h"
#include "ui/label.h"

class CoordinateAxis {
private:
    int origin_;
    int position_;
public:
    CoordinateAxis(): origin_{0}, position_{0} {}
    int position() const;
    void project(int);
    void reset();
};

class CoordinateSystem {
private:
    CoordinateAxis axes_[3];
public:
    CoordinateAxis &axis(int);
    void project(const int[3]);
};

class CoordinateDecimal : public ui::Decimal {
private:
    const CoordinateAxis &axis_;
public:
    CoordinateDecimal(const CoordinateAxis &);
    void draw(ui::Canvas) override;
};

class CoordinateResetButton : public ui::Button {
private:
    CoordinateAxis &axis_;
public:
    CoordinateResetButton(CoordinateAxis &, const char *);
    void release(ui::Position) override;
};

class CoordinateAxisGrid : public ui::Grid {
private:
    const char label_text_[3];
    ui::Label label_;
    CoordinateDecimal decimal_;
    ui::Label label_unit_;
    const char button_text_[3];
    CoordinateResetButton button_;
public:
    CoordinateAxisGrid(CoordinateAxis &, char);
};

class CoordinatePanel : public ui::Grid {
private:
    CoordinateAxisGrid row_[3];
public:
    CoordinatePanel(CoordinateSystem &);
};

#endif
