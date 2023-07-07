#ifndef BOX_H_
#define BOX_H_

#include "canvas.h"
#include "control.h"

class Box : public Control {
protected:
    Control *control_;
private:
    bool hidden_;
public:
    Box(Control *);
    void draw(Canvas &) const override;
    void hide() { hidden_ = true; };
    void show() { hidden_ = false; };
};

class InvisibleBox : public Box {
public:
    InvisibleBox(Control *control): Box(control) {};
    void draw(Canvas &) const override;
};

#endif
