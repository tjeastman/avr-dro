#include "serial.h"

#include <avr/io.h>

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

void Serial::write(char c) const
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}

void Serial::write(unsigned int v, int n) const
{
    if (v > 0 || n > 0) {
        write(v / 10, n > 0 ? n - 1 : 0);
        write('0' + v % 10);
    }
}
