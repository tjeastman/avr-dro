#ifndef LABEL_H_
#define LABEL_H_

#include "canvas.h"
#include "control.h"
#include "font.h"

class Label : public Control {
private:
    const char *value_;
    Font &font_;
public:
    Label(const char *, Font &);
    void draw(Canvas &) const;
};

#endif
