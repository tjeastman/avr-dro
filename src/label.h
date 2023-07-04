#ifndef LABEL_H_
#define LABEL_H_

#include "canvas.h"
#include "font.h"

class Label {
private:
    const char *value_;
    Font &font_;
public:
    Label(const char *value, Font &font): value_{value}, font_{font} {};
    void draw(Canvas &) const;
};

#endif
