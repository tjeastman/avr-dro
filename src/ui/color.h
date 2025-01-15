#ifndef UI_COLOR_H_
#define UI_COLOR_H_

#include <stdint.h>

namespace ui {

class Color {
private:
    static uint8_t scale_[2][32];
    uint16_t value_;

public:
    Color()
        : value_ { 0 }
    {
    }
    Color(uint8_t, uint8_t, uint8_t);
    uint16_t value() const { return value_; }
    Color blend(Color, uint8_t) const;

private:
    uint8_t R() const;
    uint8_t G() const;
    uint8_t B() const;
};

} // namespace ui

#endif // UI_COLOR_H_
