#include <avr/interrupt.h>

#include "encoder.h"

signed char Encoder::lookup_[16] = {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, 0, 0, 0};

void Encoder::consume(unsigned char input) volatile
{
    input &= 0x03;

    state_ <<= 2;
    state_ |= input;
    state_ &= 0x0f;

    count_ += lookup_[state_];
}

Encoder encoders[3];

ISR(INT0_vect)
{
    encoders[0].consume(PINK);
}

// ISR(INT1_vect)
// {
//     encoders[1].consume(PINK >> 2);
// }

// ISR(INT2_vect)
// {
//     encoders[2].consume(PINK >> 4);
// }

EncoderResetButton::EncoderResetButton(const ControlProperties &properties, Encoder &encoder, const char *text):
    Button(properties, text),
    encoder_{encoder}
{
}

void EncoderResetButton::release(Position position)
{
    encoder_.clear();
    Button::release(position);
}

EncoderPanelRow::EncoderPanelRow(const ControlProperties &properties, Encoder &encoder, const char *axis, const char *axis0, const char *unit):
    Grid(properties, Direction::RIGHT, 20),
    label_{properties, axis},
    decimal_{properties, 4, 3},
    label_unit_{properties, unit},
    button_{properties, encoder, axis0},
    encoder_{encoder}
{
    add(&label_);
    add(&decimal_);
    add(&label_unit_);
    add(&button_);
}

void EncoderPanelRow::draw(Canvas canvas)
{
    decimal_.update(encoder_.count());
    Grid::draw(canvas);
}

EncoderPanel::EncoderPanel(const ControlProperties &properties):
    Grid{properties, Direction::DOWN, 20},
    rowX_{properties, encoders[0], "X:", "X0", "mm"},
    rowY_{properties, encoders[1], "Y:", "Y0", "mm"},
    rowZ_{properties, encoders[2], "Z:", "Z0", "mm"}
{
    add(&rowX_);
    add(&rowY_);
    add(&rowZ_);
}
