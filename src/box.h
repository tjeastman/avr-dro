#ifndef BOX_H_
#define BOX_H_

#include "color.h"
#include "canvas.h"
#include "control.h"

class Box : public Control {
protected:
    Control *control_;
private:
    Color color_;
    bool hidden_;
public:
    Box(Control *, Color, bool = false);
    Box(Control *);
    void draw(Canvas) const override;
    void hide() { hidden_ = true; };
    void show() { hidden_ = false; };
};

#endif
