#ifndef UI_INTEGER_H_
#define UI_INTEGER_H_

#include <stdint.h>

#include "canvas.h"
#include "control.h"

namespace ui {

class UnsignedInteger : public Control {
private:
    static uint16_t divisors_[5];
    uint8_t digits_;
    bool changed_;
    uint16_t magnitude_;

public:
    UnsignedInteger(uint8_t);
    void update(uint16_t);
    void draw(Canvas) override;
};

} // namespace ui

#endif // UI_INTEGER_H_
