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
    bool changed_;
public:
    Box(Control *, Color, bool = false);
    Box(Control *);
    void draw(Canvas) override;
    void hide();
    void show();
};

#endif
