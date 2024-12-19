#ifndef BUTTON_H_
#define BUTTON_H_

#include "canvas.h"
#include "control.h"
#include "font.h"

class Button : public Control {
private:
    const Font &font_;
    const Color &color_;
    const char *text_;
    bool pressed_;
    bool changed_;
public:
    Button(const char *, const Font &, const Color &);
    void draw(Canvas) override;
};

#endif
