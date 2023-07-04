#ifndef CANVAS_H_
#define CANVAS_H_

#include "common.h"
#include "display.h"
#include "palette.h"

class Canvas {
private:
    Display &display_;
    Palette &palette_;
    Position positions_[8];
    signed char position_index_;
public:
    Canvas(Display &display, Palette &palette);
    void save();
    void restore();
    void move(Position);
    void adjust(Direction, Shape, signed char);
    void dimension(Shape) const;
    void fill(Shape, unsigned char) const;
    void dot(unsigned int, int) const;
};

#endif
