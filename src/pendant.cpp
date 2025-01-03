#include "pendant.h"

#include <avr/interrupt.h>
#include <avr/io.h>

void PendantAxis::move(int delta) volatile
{
    if (position_ >= 0 && delta > maximum_ - position_) {
        position_ = maximum_;
    } else if (position_ <= 0 && delta < minimum_ - position_) {
        position_ = minimum_;
    } else {
        position_ += delta;
    }
}

int PendantAxis::position(int origin) const
{
    return position_ - origin;
}

signed char Pendant::lookup_[16] = {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, 0, 0, 0};

Pendant::Pendant():
    axes_{{}, {-14750, 14750}, {-12000, 12000}, {-25000, 0}},
    index_{0},
    multiplier_{0},
    state_{0}
{
}

void Pendant::turn(unsigned char input) volatile
{
    input &= 0x03;

    state_ <<= 2;
    state_ |= input;
    state_ &= 0x0f;

    axes_[index_].move(multiplier_ * lookup_[state_]);
}

void Pendant::press(unsigned char input) volatile
{
    if (input == 0) {
        return;
    }

    if (input & _BV(0)) {
        index_ = 1;
    } else if (input & _BV(1)) {
        index_ = 2;
    } else if (input & _BV(2)) {
        index_ = 3;
    } else {
        index_ = 0;
    }

    if (input & _BV(3)) {
        multiplier_ = 1;
    } else if (input & _BV(4)) {
        multiplier_ = 10;
    } else if (input & _BV(5)) {
        multiplier_ = 100;
    } else {
        multiplier_ = 0;
    }
}

const PendantAxis &Pendant::axis(char axis) const
{
    switch (axis) {
    case 'X':
        return axes_[1];
    case 'Y':
        return axes_[2];
    case 'Z':
        return axes_[3];
    default:
        return axes_[0];
    }
}

Pendant pendant;

ISR(INT0_vect)
{
    pendant.turn(PIND);
}

ISR(PCINT2_vect)
{
    pendant.press(PINK);
}
