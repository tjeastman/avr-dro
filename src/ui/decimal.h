#ifndef UI_DECIMAL_H_
#define UI_DECIMAL_H_

#include "canvas.h"
#include "control.h"
#include "integer.h"

namespace UI {
    class Decimal : public Control {
    private:
        UnsignedInteger integer_;
        UnsignedInteger fractional_;
        bool changed_;
        int value_;
        unsigned int divisor_;
    public:
        Decimal(const ControlProperties &, unsigned char, unsigned char);
        void update(int);
        void draw(Canvas) override;
    private:
        void draw_sign(Canvas &);
        void draw_integer(Canvas &);
        void draw_dot(Canvas &);
    };
}

#endif  // UI_DECIMAL_H_
