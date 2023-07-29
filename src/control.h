#ifndef CONTROL_H_
#define CONTROL_H_

#include "canvas.h"
#include "common.h"

class Control {
protected:
    Shape shape_{0, 0};
public:
    const Shape &shape() const { return shape_; }
    virtual void draw(Canvas) const = 0;
};

#endif
