#ifndef UI_DECIMAL_H_
#define UI_DECIMAL_H_

#include "canvas.h"
#include "control.h"
#include "integer.h"

namespace ui {

class Decimal : public Control {
protected:
    int value_;
private:
    unsigned int divisor_;
    bool changed_;
    UnsignedInteger integer_;
    UnsignedInteger fractional_;
public:
    Decimal(unsigned char, unsigned char);
    void update(int);
    void draw(Canvas) override;
private:
    void draw_sign(Canvas &);
    void draw_integer(Canvas &);
    void draw_dot(Canvas &);
};

}  // namespace ui

#endif  // UI_DECIMAL_H_
