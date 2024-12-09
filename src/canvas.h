#ifndef CANVAS_H_
#define CANVAS_H_

#include "color.h"
#include "common.h"
#include "display.h"

class Canvas {
private:
    const Display &display_;
    Position position_;
    Color color_;
public:
    Canvas(const Display &);
    void move(const Position &);
    void adjust(Direction, const Shape &, signed char);
    void select(const Color &);
    void dimension(const Shape &) const;
    void fill(const Shape &) const;
    void fill(const Shape &, const Color &, unsigned char) const;
    void dot(const Color &, unsigned char, int) const;
};

#endif
