#ifndef BUTTON_H_
#define BUTTON_H_

#include "canvas.h"
#include "control.h"

class Button : public Control {
private:
    const char *text_;
    bool pressed_;
    bool changed_;
public:
    Button(const ControlProperties &, const char *);
    void draw(Canvas) override;
};

#endif
