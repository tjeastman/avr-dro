#include "touch.h"

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "ui/common.h"
#include "ui/control.h"

TouchState::TouchState()
    : event_ { Event::NONE }
    , position_ { 0, 0 }
    , readings_ { 0 }
{
}

void TouchState::press(int16_t x, int16_t y)
{
    if (readings_ == 0) {
        position_.x = x;
        position_.y = y;
    } else {
        position_.x += x;
        position_.y += y;
    }
    // keep a running "average" of the press coordinates
    if (readings_++) {
        position_.x >>= 1;
        position_.y >>= 1;
    }
    // avoid spurious state transitions due to overflow
    if (readings_ >= 10000) {
        readings_ = 10000;
    }
    event_ = Event::PRESS;
}

void TouchState::release()
{
    // preserve position for use in release events
    readings_ = 0;
    // only allow one consecutive release event
    if (event_ == Event::PRESS) {
        event_ = Event::RELEASE;
    } else if (event_ == Event::RELEASE) {
        event_ = Event::NONE;
    }
}

void TouchState::dispatch(const Calibration& calibration, ui::Control& control)
{
    if (event_ == TouchState::Event::NONE) {
        return;
    }

    ui::Position position = calibration.translate(position_);
    if (!control.contains(position)) {
        return;
    } else if (event_ == TouchState::Event::PRESS) {
        control.press(position);
    } else if (event_ == TouchState::Event::RELEASE) {
        control.release(position);
    }
}

Touch::Touch(const Calibration& calibration)
    : calibration_ { calibration }
    , state_ {}
{
}

void Touch::dispatch(ui::Control& control)
{
    transition();
    state_.dispatch(calibration_, control);
}

uint8_t Touch::transmit8(uint8_t value)
{
    SPDR = value;
    loop_until_bit_is_set(SPSR, SPIF);
    return SPDR;
}

uint16_t Touch::transmit16(uint16_t value)
{
    uint16_t result;
    result = transmit8(value >> 8) << 8;
    result |= transmit8(value);
    return result;
}

void Touch::update()
{
    transmit8(0xb1);
    transmit16(0xc1);
    transmit16(0x91);
    int16_t y = transmit16(0xd0) >> 3;
    int16_t x = transmit16(0x00) >> 3;
    state_.press(x, y);
}

void Touch::clear()
{
    state_.release();
}

bool Touch::interrupt()
{
    return bit_is_clear(PINL, PL5);
}

void Touch::transition()
{
    _delay_ms(10);
    if (interrupt()) {
        PORTB &= ~_BV(PB0); // select
        update();
        PORTB |= _BV(PB0); // deselect
    } else {
        clear();
    }
}
