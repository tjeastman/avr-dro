#ifndef UI_CANVAS_H_
#define UI_CANVAS_H_

#include "ui/display.h"
#include "ui/color.h"
#include "ui/common.h"

namespace UI {

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

}  // namespace UI

#endif  // UI_CANVAS_H_
