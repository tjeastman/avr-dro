#include "touch.h"

#include <avr/io.h>
#include <util/delay.h>

#include "ui/common.h"
#include "ui/control.h"

TouchState::TouchState(): event{Event::NONE}, position{0, 0}, readings{0}
{
}

void TouchState::press(int x, int y, int z)
{
    if (readings == 0) {
        position.x = x;
        position.y = y;
    } else {
        position.x += x;
        position.y += y;
    }
    // keep a running "average" of the press coordinates
    if (readings++) {
        position.x >>= 1;
        position.y >>= 1;
    }
    // avoid spurious state transitions due to overflow
    if (readings >= 10000) {
        readings = 10000;
    }
    event = Event::PRESS;
}

void TouchState::release()
{
    // preserve position for use in release events
    readings = 0;
    // only allow one consecutive release event
    if (event == Event::PRESS) {
        event = Event::RELEASE;
    } else if (event == Event::RELEASE) {
        event = Event::NONE;
    }
}

unsigned char Touch::transmit8(unsigned char value)
{
    SPDR = value;
    loop_until_bit_is_set(SPSR, SPIF);
    return SPDR;
}

unsigned int Touch::transmit16(unsigned int value)
{
    unsigned int result;
    result = transmit8(value >> 8) << 8;
    result |= transmit8(value);
    return result;
}

void Touch::update()
{
    transmit8(0xb1);
    int z0 = transmit16(0xc1) >> 3;
    int z1 = transmit16(0x91) >> 3;
    int y = transmit16(0xd0) >> 3;
    int x = transmit16(0x00) >> 3;
    state_.press(x, y, z1 - z0);
}

void Touch::clear()
{
    state_.release();
}

bool Touch::interrupt()
{
    return bit_is_clear(PINL, 5);
}

void Touch::transition()
{
    _delay_ms(10);
    if (interrupt()) {
        PORTB &= ~_BV(0); // select
        update();
        PORTB |= _BV(0); // deselect
    } else {
        clear();
    }
}

void Touch::dispatch(ui::Control &control)
{
    transition();
    if (state_.event == TouchState::Event::NONE) {
        return;
    }

    ui::Position position = calibration_.translate(state_.position);
    if (!control.contains(position)) {
        return;
    } else if (state_.event == TouchState::Event::PRESS) {
        control.press(position);
    } else if (state_.event == TouchState::Event::RELEASE) {
        control.release(position);
    }
}
