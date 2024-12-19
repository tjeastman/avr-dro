#ifndef DECIMAL_H_
#define DECIMAL_H_

#include "color.h"
#include "canvas.h"
#include "control.h"
#include "font.h"
#include "integer.h"

class Decimal : public Control {
private:
    const Font &font_;
    const Color &color_;
    UnsignedInteger integer_;
    UnsignedInteger fractional_;
    bool changed_;
    int value_;
    unsigned int divisor_;
public:
    Decimal(unsigned char, unsigned char, const Font &, const Color &);
    void update(int);
    void draw(Canvas) override;
private:
    void draw_sign(Canvas &);
    void draw_integer(Canvas &);
    void draw_dot(Canvas &);
};

#endif
