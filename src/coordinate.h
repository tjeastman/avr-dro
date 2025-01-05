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
    const char label[3];
    static const unsigned char digits[2];
    static const char *unit;
    const char zero[3];
    CoordinateAxis(char);
    int position() const;
    void project(int);
    void reset();
};

class CoordinateSystem {
private:
    CoordinateAxis axes_[3];
public:
    CoordinateSystem();
    CoordinateAxis &axis(int);
    void project(const int[3]);
};

class CoordinateResetButton : public ui::Button {
private:
    CoordinateAxis &axis_;
public:
    CoordinateResetButton(CoordinateAxis &);
    void release(ui::Position) override;
};

class CoordinatePanelRow : public ui::Grid {
private:
    CoordinateAxis &axis_;
    ui::Label label_;
    ui::Decimal decimal_;
    ui::Label label_unit_;
    CoordinateResetButton button_;
public:
    CoordinatePanelRow(CoordinateSystem &, int);
    void draw(ui::Canvas) override;
};

class CoordinatePanel : public ui::Grid {
private:
    CoordinatePanelRow row_[3];
public:
    CoordinatePanel(CoordinateSystem &);
};

#endif
