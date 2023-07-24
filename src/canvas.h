#ifndef CANVAS_H_
#define CANVAS_H_

#include "color.h"
#include "common.h"
#include "display.h"

class Canvas {
private:
    Display &display_;
    signed char index_;
    Position positions_[8];
    Color colors_[8];
public:
    Canvas(Display &);
    void save();
    void restore();
    void move(Position);
    void adjust(Direction, Shape, signed char);
    void select(Color);
    void dimension(Shape) const;
    void fill(Shape) const;
    void fill(Shape, Color, unsigned char) const;
    void dot(Color, unsigned char, int) const;
};

#endif
