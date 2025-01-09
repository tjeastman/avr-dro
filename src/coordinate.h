#ifndef COORDINATE_H_
#define COORDINATE_H_

#include "pendant.h"
#include "touch.h"
#include "ui/button.h"
#include "ui/canvas.h"
#include "ui/common.h"
#include "ui/decimal.h"
#include "ui/grid.h"
#include "ui/label.h"

class CoordinateLabel : public ui::Label {
private:
    bool selected_;
public:
    CoordinateLabel(const char *);
    void draw(ui::Canvas) override;
    void select(bool);
private:
    void draw_selector(ui::Canvas);
};

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
    CoordinateLabel label_;
    CoordinateDecimal decimal_;
    ui::Label label_unit_;
    const char button_text_[3];
    CoordinateResetButton button_;
public:
    CoordinateAxisGrid(char);
    void update(int);
    void select(bool);
};

class CoordinateFeedGrid : public ui::Grid {
private:
    CoordinateLabel label_;
    ui::Decimal decimal_;
    ui::Label label_unit_;
public:
    CoordinateFeedGrid();
    void update(int);
};

class CoordinateGrid : public ui::Grid {
private:
    CoordinateAxisGrid axes_[3];
    CoordinateFeedGrid feed_;
public:
    CoordinateGrid();
    void update(PendantAxis::Identifier, int, int);
};

class CoordinatePanel : public PendantAxisSpace {
private:
    CoordinateGrid grid_;
public:
    void project(PendantAxis::Identifier, int, int) override;
    void dispatch(Touch &);
    void draw(ui::Canvas &);
};

#endif  // COORDINATE_H_
