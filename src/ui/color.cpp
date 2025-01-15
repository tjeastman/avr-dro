#include "color.h"

#include <stdint.h>

namespace ui {

uint8_t Color::scale_[2][32] = {
    { 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10 },
    { 0, 1, 1, 2, 3, 3, 4, 5, 5, 6, 7, 7, 8, 9, 9, 10, 11, 11, 12, 13, 13, 14, 15, 15, 16, 17, 17, 18, 19, 19, 20, 21 },
};

Color::Color(uint8_t red, uint8_t green, uint8_t blue)
{
    value_ = ((red & 0x1f) << 11) | (((2 * green) & 0x3f) << 5) | (blue & 0x1f);
}

Color Color::blend(Color color, uint8_t alpha) const
{
    if (alpha == 0) {
        return *this;
    } else if (alpha >= 3) {
        return color;
    }
    return Color(R() + (scale_[alpha - 1][color.R()] - scale_[alpha - 1][R()]),
        G() + (scale_[alpha - 1][color.G()] - scale_[alpha - 1][G()]),
        B() + (scale_[alpha - 1][color.B()] - scale_[alpha - 1][B()]));
}

uint8_t Color::R() const
{
    return value_ >> 11;
}

uint8_t Color::G() const
{
    return (value_ >> 6) & 0x1f;
}

uint8_t Color::B() const
{
    return value_ & 0x1f;
}

} // namespace ui
