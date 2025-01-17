#include "pendant.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

PendantAxis::PendantAxis(char identifier, int16_t minimum, int16_t maximum)
    : identifier_ { identifier }
    , minimum_ { minimum }
    , maximum_ { maximum }
    , position_ { 0 }
    , rate_ { 0 }
{
}

void PendantAxis::increment(int16_t delta) volatile
{
    if (position_ < 0) {
        position_ += delta;
    } else if (delta <= maximum_ - position_) {
        position_ += delta;
    } else {
        position_ = maximum_;
    }
}

void PendantAxis::decrement(int16_t delta) volatile
{
    if (position_ > 0) {
        position_ -= delta;
    } else if (-delta >= minimum_ - position_) {
        position_ -= delta;
    } else {
        position_ = minimum_;
    }
}

void PendantAxis::pace(int16_t rate) volatile
{
    rate_ = rate;
}

void PendantAxis::project(PendantAxisSpace& space) volatile const
{
    space.project(identifier_, position_, rate_);
}

void PendantAxis::project(CommandQueue& commands) volatile const
{
    commands.project(identifier_, position_, rate_);
}

Pendant::Pendant(CommandQueue& commands)
    : axes_ { { 0, 0, 0 }, { 'X', -14750, 14750 }, { 'Y', -12000, 12000 }, { 'Z', -25000, 0 } }
    , index_ { 0 }
    , delta_ { 0 }
    , state_ { 0 }
    , commands_ { commands }
    , changed_ { false }
{
}

void Pendant::turn(uint8_t input) volatile
{
    input &= 0x03;

    state_ <<= 2;
    state_ |= input;
    state_ &= 0x0f;

    // FIX: what if axis is at a limit?
    if (state_ == 0x06) {
        axes_[index_].increment(delta_);
        changed_ = true;
    } else if (state_ == 0x0c) {
        axes_[index_].decrement(delta_);
        changed_ = true;
    }
}

void Pendant::press(uint8_t input) volatile
{
    input &= 0x3f;

    if (input == 0) {
        return;
    }

    if (changed_ && index_ > 0) {
        axes_[index_].project(commands_);
    }

    changed_ = false;

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

void Pendant::pace(uint16_t input) volatile
{
    axes_[index_].pace(input & 0x3f8);
}

void Pendant::project(PendantAxisSpace& space) const
{
    axes_[index_].project(space);
}

Pendant* Pendant::instance = nullptr;

void Pendant::initialize(Pendant* pendant)
{
    instance = pendant;

    // set up external interrupt to handle MPG turn events
    EIMSK |= _BV(INT0);
    EICRA |= _BV(ISC00);

    // set up pin change interrupts to handle button press events
    PCICR |= _BV(PCIE2);
    PCMSK2 |= _BV(PCINT16);
    PCMSK2 |= _BV(PCINT17);
    PCMSK2 |= _BV(PCINT18);
    PCMSK2 |= _BV(PCINT19);
    PCMSK2 |= _BV(PCINT20);
    PCMSK2 |= _BV(PCINT21);

    // set up analog to digital converter to manage feed rate
    ADMUX |= _BV(REFS0);
    ADMUX |= _BV(MUX2);
    ADMUX |= _BV(MUX1);
    ADCSRA |= _BV(ADEN);
    ADCSRA |= _BV(ADSC);
    ADCSRA |= _BV(ADATE);
    ADCSRA |= _BV(ADIE);
    ADCSRA |= _BV(ADPS2);
    ADCSRA |= _BV(ADPS1);
    ADCSRA |= _BV(ADPS0);
    ADCSRB |= _BV(MUX5);
}

ISR(INT0_vect)
{
    Pendant::instance->turn(PIND);
}

ISR(PCINT2_vect)
{
    Pendant::instance->press(PINK);
}

ISR(ADC_vect)
{
    Pendant::instance->pace(ADCL + (ADCH << 8));
}
