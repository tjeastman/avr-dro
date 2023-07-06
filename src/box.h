#ifndef BOX_H_
#define BOX_H_

#include "canvas.h"
#include "control.h"

class Box : public Control {
private:
    Control *control_;
    bool hidden_;
public:
    Box(Control *);
    void draw(Canvas &) const;
    void hide() { hidden_ = true; };
    void show() { hidden_ = false; };
};

#endif
