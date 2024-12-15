#include <avr/interrupt.h>

#include "encoder.h"

signed char Encoder::lookup[16] = {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, 0, 0, 0};

void Encoder::consume(unsigned char input) volatile
{
    input &= 0x03;

    state_ <<= 2;
    state_ |= input;
    state_ &= 0x0f;

    count_ += lookup[state_];
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

EncoderResetButton::EncoderResetButton(Encoder &encoder, const char *text, const Font &font, const Color &color):
    encoder_{encoder},
    Button(text, font, color)
{
}

void EncoderResetButton::release(Position position)
{
    encoder_.clear();
    Button::release(position);
}

EncoderPanelRow::EncoderPanelRow(Encoder &encoder, const char *axis, const char *axis0, const char *unit, const Font &font, const Color &color):
    label_{axis, font, color},
    decimal_{4, 3, font, color},
    label_unit_{unit, font, color},
    button_{encoder, axis0, font, color},
    encoder_{encoder},
    Grid(Direction::RIGHT, 20)
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

EncoderPanel::EncoderPanel(Font &font, Color &color):
    rowX_{encoders[0], "X:", "X0", "mm", font, color},
    rowY_{encoders[1], "Y:", "Y0", "mm", font, color},
    rowZ_{encoders[2], "Z:", "Z0", "mm", font, color},
    Grid{Direction::DOWN, 20}
{
    add(&rowX_);
    add(&rowY_);
    add(&rowZ_);
}
