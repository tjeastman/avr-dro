#include "touch.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "ui/common.h"
#include "ui/control.h"

TouchState::TouchState():
    event{Event::NONE},
    position{0, 0},
    readings{0}
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

Touch::Touch(Calibration &calibration):
    calibration_{calibration},
    state_{},
    pressed_{false}
{
}

void Touch::dispatch(ui::Control &control)
{
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
        state_.release();
    }
}

Touch *Touch::instance = nullptr;

void Touch::initialize(Touch *touch)
{
    instance = touch;

    // set up timer for fast PWM, prescaler=256, frequency=5Hz
    TIMSK1 |= _BV(TOIE1);
    TCCR1A |= _BV(WGM10);
    TCCR1A |= _BV(WGM11);
    TCCR1B |= _BV(WGM12);
    TCCR1B |= _BV(WGM13);
    TCCR1B |= _BV(CS12);
    OCR1AH = (12500 >> 8) & 0xff;
    OCR1AL = 12500 & 0xff;

    // set up pin change interrupts
    PCICR |= _BV(PCIE1);
    PCMSK1 |= _BV(PCINT9);
}

void Touch::clock()
{
    if (pressed_) {
        PORTB &= ~_BV(0); // select
        update();
        PORTB |= _BV(0); // deselect
    }
}

void Touch::press(bool state)
{
    if (!state) {
        pressed_ = true;
        PORTB &= ~_BV(0); // select
        update();
        PORTB |= _BV(0); // deselect
    } else {
        pressed_ = false;
        state_.release();
    }
}

ISR(PCINT1_vect)
{
    Touch::instance->press(PINJ & _BV(0));
}

ISR(TIMER1_OVF_vect)
{
    Touch::instance->clock();
}
