#ifndef LABEL_H_
#define LABEL_H_

#include "color.h"
#include "canvas.h"
#include "control.h"
#include "font.h"

class Label : public Control {
private:
    const char *value_;
    const Font &font_;
    const Color &color_;
    bool changed_;
public:
    Label(const char *, const Font &, const Color &);
    void draw(Canvas) override;
};

#endif
