#include "serial.h"

#include <avr/io.h>

void Serial::initialize() const
{
    // configure UART for 115200 baud 8N1
    UBRR0H = 0;
    UBRR0L = 16;
    UCSR0A |= _BV(U2X0);
    UCSR0B |= _BV(TXEN0);
    UCSR0C |= _BV(UCSZ01);
    UCSR0C |= _BV(UCSZ00);
}

void Serial::operator<<(char c) const
{
    write(c);
}

void Serial::operator<<(const char* s) const
{
    for (; *s; ++s) {
        write(*s);
    }
}

void Serial::write(char c) const
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}
