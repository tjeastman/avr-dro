#ifndef UI_DECIMAL_H_
#define UI_DECIMAL_H_

#include <stdint.h>

#include "canvas.h"
#include "control.h"
#include "integer.h"

namespace ui {

class Decimal : public Control {
protected:
    int16_t value_;

private:
    uint16_t divisor_;
    bool changed_;
    UnsignedInteger integer_;
    UnsignedInteger fractional_;

public:
    Decimal(uint8_t, uint8_t);
    void update(int16_t);
    void draw(Canvas) override;

private:
    void draw_sign(Canvas&);
    void draw_integer(Canvas&);
    void draw_dot(Canvas&);
};

} // namespace ui

#endif // UI_DECIMAL_H_
