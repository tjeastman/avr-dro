#ifndef COORDINATE_H_
#define COORDINATE_H_

#include "pendant.h"
#include "ui/button.h"
#include "ui/canvas.h"
#include "ui/common.h"
#include "ui/control.h"
#include "ui/decimal.h"
#include "ui/grid.h"
#include "ui/label.h"

class CoordinateAxis {
private:
    const PendantAxis &axis_;
    int origin_;
public:
    const char label[3];
    static const unsigned char digits[2];
    static const char *unit;
    const char zero[3];
    CoordinateAxis(const Pendant &, char);
    int position() const;
    void reset();
};

class CoordinateSystem {
private:
    const Pendant &pendant_;
    CoordinateAxis axes_[3];
public:
    CoordinateSystem(const Pendant &);
    CoordinateAxis &axis(int);
};

class CoordinateResetButton : public ui::Button {
private:
    CoordinateAxis &axis_;
public:
    CoordinateResetButton(const ui::ControlProperties &, CoordinateAxis &);
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
    CoordinatePanelRow(const ui::ControlProperties &, CoordinateSystem &, int);
    void draw(ui::Canvas) override;
};

class CoordinatePanel : public ui::Grid {
private:
    CoordinatePanelRow row_[3];
public:
    CoordinatePanel(const ui::ControlProperties &, CoordinateSystem &);
};

#endif
