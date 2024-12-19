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
    char padding_;
public:
    Grid(Direction, char);
    void draw(Canvas) override;
    void add(Control *);
    void press(Position) override;
    void release(Position) override;
private:
    Control *control(Position *);
};

#endif
