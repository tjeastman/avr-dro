#ifndef COORDINATE_H_
#define COORDINATE_H_

#include "ui/button.h"
#include "ui/canvas.h"
#include "ui/common.h"
#include "ui/decimal.h"
#include "ui/grid.h"
#include "ui/label.h"

class CoordinateDecimal : public ui::Decimal {
private:
    int origin_;
public:
    CoordinateDecimal(unsigned char, unsigned char);
    void update(int);
    void reset();
};

class CoordinateResetButton : public ui::Button {
private:
    CoordinateDecimal &decimal_;
public:
    CoordinateResetButton(const char *, CoordinateDecimal &);
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
    CoordinateAxisGrid(char);
    void set(int);
};

class CoordinateFeedGrid : public ui::Grid {
private:
    ui::Label label_;
    ui::Decimal decimal_;
    ui::Label label_unit_;
public:
    CoordinateFeedGrid();
    void set(int);
};

class CoordinatePanel : public ui::Grid {
private:
    CoordinateAxisGrid axes_[3];
    CoordinateFeedGrid feed_;
public:
    CoordinatePanel();
    void set(const int[3], int);
};

class CoordinateSystem {
private:
    CoordinatePanel &panel_;
public:
    CoordinateSystem(CoordinatePanel &panel): panel_{panel} {}
    void project(const int[3], int) const;
};

#endif
