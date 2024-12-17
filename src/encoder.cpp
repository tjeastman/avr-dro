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
