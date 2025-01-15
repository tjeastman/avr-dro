#ifndef UI_GRID_H_
#define UI_GRID_H_

#include <stdint.h>

#include "canvas.h"
#include "common.h"
#include "control.h"

namespace ui {

class Grid : public Control {
private:
    int8_t count_;
    Control* controls_[8];
    Direction direction_;
    int8_t padding_;

public:
    Grid(Direction, int8_t);
    void draw(Canvas) override;
    void add(Control*);
    void press(Position) override;
    void release(Position) override;

private:
    Control* control(Position*);
};

} // namespace ui

#endif // UI_GRID_H_
