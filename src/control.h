#ifndef CONTROL_H_
#define CONTROL_H_

#include "canvas.h"
#include "color.h"
#include "common.h"
#include "font.h"

struct ControlProperties {
    const Font &font;
    const Color &color;
};

class Control {
protected:
    const ControlProperties &properties_;
    Shape shape_;
public:
    Control(const ControlProperties &properties): properties_{properties}, shape_{0, 0} {}
    const Shape &shape() const { return shape_; }
    virtual void draw(Canvas) = 0;
    virtual void press(Position) {}
    virtual void release(Position) {}
    bool contains(const Position &position) const { return shape_.contains(position.x, position.y); }
};

#endif
