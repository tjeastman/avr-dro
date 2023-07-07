#ifndef GRID_H_
#define GRID_H_

#include "canvas.h"
#include "common.h"
#include "control.h"

class Grid : public Control {
private:
    signed char count_;
    Control *controls_[8];
    Direction direction_;
public:
    Grid(Direction);
    void draw(Canvas) override;
    void add(Control *);
};

#endif
