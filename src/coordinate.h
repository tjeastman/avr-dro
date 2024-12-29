#ifndef COORDINATE_H_
#define COORDINATE_H_

#include "button.h"
#include "canvas.h"
#include "common.h"
#include "control.h"
#include "decimal.h"
#include "grid.h"
#include "label.h"
#include "pendant.h"

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

class CoordinateResetButton : public Button {
private:
    CoordinateAxis &axis_;
public:
    CoordinateResetButton(const ControlProperties &, CoordinateAxis &);
    void release(Position) override;
};

class CoordinatePanelRow : public Grid {
private:
    CoordinateAxis &axis_;
    Label label_;
    Decimal decimal_;
    Label label_unit_;
    CoordinateResetButton button_;
public:
    CoordinatePanelRow(const ControlProperties &, CoordinateSystem &, int);
    void draw(Canvas) override;
};

class CoordinatePanel : public Grid {
private:
    CoordinatePanelRow row_[3];
public:
    CoordinatePanel(const ControlProperties &, CoordinateSystem &);
};

#endif
