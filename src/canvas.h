#ifndef CANVAS_H_
#define CANVAS_H_

#include "display.h"
#include "ui/color.h"
#include "ui/common.h"

class Canvas {
private:
    const Display &display_;
    UI::Position position_;
    UI::Color color_;
public:
    Canvas(const Display &);
    void move(const UI::Position &);
    void adjust(UI::Direction, const UI::Shape &, signed char);
    void select(const UI::Color &);
    void dimension(const UI::Shape &) const;
    void fill(const UI::Shape &) const;
    void fill(const UI::Shape &, const UI::Color &, unsigned char) const;
    void dot(const UI::Color &, unsigned char, int) const;
};

#endif
