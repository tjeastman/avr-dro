#include "serial.h"

#include <avr/io.h>

Serial::Serial()
{
}

void Serial::write(char c) const
{
    while (!(UCSR0A & (1 << UDRE0))) {}
    UDR0 = c;
}

void Serial::operator<<(char c) const
{
    write(c);
}

void Serial::operator<<(const char *s) const
{
    for (; *s; ++s) {
        write(*s);
    }
}
