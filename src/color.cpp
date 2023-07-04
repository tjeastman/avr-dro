#include "color.h"

Color::Color(unsigned char red, unsigned char green, unsigned char blue)
{
    value = ((red & 0x1f) << 11) | (((2 * green) & 0x3f) << 5) | (blue & 0x1f);
}

unsigned char Color::R() const
{
    return value >> 11;
}

unsigned char Color::G() const
{
    return (value >> 6) & 0x1f;
}

unsigned char Color::B() const
{
    return value & 0x1f;
}
