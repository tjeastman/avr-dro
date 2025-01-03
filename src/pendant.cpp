#include "pendant.h"

#include <avr/interrupt.h>
#include <avr/io.h>

#include "coordinate.h"

PendantAxis::PendantAxis(int minimum, int maximum):
    minimum_{minimum},
    maximum_{maximum},
    position_{0}
{
}

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

void PendantAxis::project(CoordinateAxis &axis) const
{
    axis.project(position_);
}

Pendant::Pendant():
    axes_{{-14750, 14750}, {-12000, 12000}, {-25000, 0}},
    index_{-1},
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

    if (index_ == -1) {

    } else if (state_ == 0x06) {
        axes_[index_].move(multiplier_);
    } else if (state_ == 0x0c) {
        axes_[index_].move(-multiplier_);
    }
}

void Pendant::press(unsigned char input) volatile
{
    input &= 0x3f;

    if (input == 0) {
        return;
    }

    if (input & _BV(0)) {
        index_ = 0;
    } else if (input & _BV(1)) {
        index_ = 1;
    } else if (input & _BV(2)) {
        index_ = 2;
    } else {
        index_ = -1;
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

void Pendant::project(CoordinateSystem &system) const
{
    axes_[0].project(system.axis(0));
    axes_[1].project(system.axis(1));
    axes_[2].project(system.axis(2));
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
