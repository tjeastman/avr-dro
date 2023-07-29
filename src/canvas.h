#ifndef CANVAS_H_
#define CANVAS_H_

#include "color.h"
#include "common.h"
#include "display.h"

class Canvas {
private:
    Display &display_;
    Position position_;
    Color color_;
public:
    Canvas(Display &);
    void move(Position);
    void adjust(Direction, Shape, signed char);
    void select(Color);
    void dimension(Shape) const;
    void fill(Shape) const;
    void fill(Shape, Color, unsigned char) const;
    void dot(Color, unsigned char, int) const;
};

#endif
