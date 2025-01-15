#ifndef UI_CANVAS_H_
#define UI_CANVAS_H_

#include <stdint.h>

#include "color.h"
#include "common.h"
#include "display.h"

namespace ui {

class Canvas {
private:
    const Display& display_;
    Position position_;
    Color color_;

public:
    Canvas(const Display&);
    void move(const Position&);
    void adjust(Direction, const Shape&, int8_t);
    void select(const Color&);
    void dimension(const Shape&) const;
    void fill(const Shape&) const;
    void fill(const Shape&, const Color&, uint8_t) const;
    void dot(const Color&, uint8_t, int16_t) const;
};

} // namespace ui

#endif // UI_CANVAS_H_
