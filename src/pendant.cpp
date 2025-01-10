#include "pendant.h"

#include <avr/interrupt.h>
#include <avr/io.h>

PendantAxis::PendantAxis(PendantAxis::Identifier identifier, int minimum, int maximum):
    identifier_{identifier},
    minimum_{minimum},
    maximum_{maximum},
    position_{0},
    rate_{0}
{
}

void PendantAxis::increment(int delta) volatile
{
    if (position_ < 0) {
        position_ += delta;
    } else if (delta <= maximum_ - position_) {
        position_ += delta;
    } else {
        position_ = maximum_;
    }
}

void PendantAxis::decrement(int delta) volatile
{
    if (position_ > 0) {
        position_ -= delta;
    } else if (-delta >= minimum_ - position_) {
        position_ -= delta;
    } else {
        position_ = minimum_;
    }
}

void PendantAxis::pace(int rate) volatile
{
    rate_ = rate;
}

void PendantAxis::project(PendantAxisSpace &space) const
{
    space.project(identifier_, position_, rate_);
}

Pendant::Pendant():
    axes_{
        {PendantAxis::Identifier::NONE, 0, 0},
        {PendantAxis::Identifier::X, -14750, 14750},
        {PendantAxis::Identifier::Y, -12000, 12000},
        {PendantAxis::Identifier::Z, -25000, 0}
    },
    index_{0},
    delta_{0},
    state_{0}
{
}

void Pendant::turn(unsigned char input) volatile
{
    input &= 0x03;

    state_ <<= 2;
    state_ |= input;
    state_ &= 0x0f;

    if (state_ == 0x06) {
        axes_[index_].increment(delta_);
    } else if (state_ == 0x0c) {
        axes_[index_].decrement(delta_);
    }
}

void Pendant::press(unsigned char input) volatile
{
    input &= 0x3f;

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
        delta_ = 1;
    } else if (input & _BV(4)) {
        delta_ = 10;
    } else if (input & _BV(5)) {
        delta_ = 100;
    } else {
        delta_ = 0;
    }
}

void Pendant::pace(unsigned int input) volatile
{
    axes_[index_].pace(input & 0x3f8);
}

void Pendant::project(PendantAxisSpace &space) const
{
    axes_[index_].project(space);
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

ISR(ADC_vect)
{
    pendant.pace(ADCL + (ADCH << 8));
}
