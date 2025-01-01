#ifndef UI_GRID_H_
#define UI_GRID_H_

#include "canvas.h"
#include "common.h"
#include "control.h"

namespace ui {

class Grid : public Control {
private:
    signed char count_;
    Control *controls_[8];
    Direction direction_;
    char padding_;
public:
    Grid(const ControlProperties &, Direction, char);
    void draw(Canvas) override;
    void add(Control *);
    void press(Position) override;
    void release(Position) override;
private:
    Control *control(Position *);
};

}  // namespace ui

#endif  // UI_GRID_H_
