#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>

#include "color.h"
#include "common.h"
#include "display.h"
#include "palette.h"

int main(void)
{
    DDRC = 0xFF;
    DDRA = 0xFF;

    DDRD |= _BV(7); // RS
    DDRG |= _BV(2); // WR
    DDRG |= _BV(1); // CS
    DDRG |= _BV(0); // RST
    DDRL |= _BV(6); // RD

    PORTD |= _BV(7);
    PORTG |= _BV(2);
    PORTG |= _BV(1);
    PORTG |= _BV(0);
    PORTL |= _BV(6);

    PORTG |= _BV(0); // RST=HIGH
    _delay_ms(10);
    PORTG &= ~_BV(0); // RST=LOW
    _delay_ms(100);
    PORTG |= _BV(0); // RST=HIGH
    _delay_ms(50);

    PORTG |= _BV(1); // CS=HIGH
    PORTG |= _BV(2); // WR=HIGH
    PORTG &= ~_BV(1); // CS=LOW
    _delay_ms(50);

    auto palette = Palette(Color(25, 30, 5), Color(2, 4, 28));
    auto display = Display();

    display.initialize();
    display.blank();
    display.fill(Position{0, 0}, Shape{200, 480}, palette.color(0));
    display.fill(Position{200, 0}, Shape{200, 480}, palette.color(1));
    display.fill(Position{400, 0}, Shape{200, 480}, palette.color(2));
    display.fill(Position{600, 0}, Shape{200, 480}, palette.color(3));

    while (true);

    return 0;
}
