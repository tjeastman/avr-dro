#ifndef BOX_H_
#define BOX_H_

#include "color.h"
#include "canvas.h"
#include "control.h"

class Box : public Control {
protected:
    Control *control_;
private:
    bool hidden_;
    Color &color_;
public:
    Box(Control *, Color &);
    void draw(Canvas &) const override;
    void hide() { hidden_ = true; };
    void show() { hidden_ = false; };
};

class InvisibleBox : public Control {
private:
    Control *control_;
public:
    InvisibleBox(Control *);
    void draw(Canvas &) const override;
};

#endif
