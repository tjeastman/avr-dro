#ifndef UI_CONTROL_H_
#define UI_CONTROL_H_

#include "canvas.h"
#include "color.h"
#include "common.h"
#include "font.h"

namespace ui {

struct ControlProperties {
    const Font &font;
    const Color &color;
};

class Control {
protected:
    static const ControlProperties &properties_;
    Shape shape_;
public:
    Control(): shape_{0, 0} {}
    const Shape &shape() const { return shape_; }
    virtual void draw(Canvas) = 0;
    virtual void press(Position) {}
    virtual void release(Position) {}
    bool contains(const Position &) const;
};

}  // namespace ui

#endif  // UI_CONTROL_H_
