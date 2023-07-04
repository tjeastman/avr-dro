#include <stdbool.h>

#include <avr/io.h>
#include <util/delay.h>

#include "canvas.h"
#include "color.h"
#include "common.h"
#include "display.h"
#include "font.h"
#include "integer.h"
#include "label.h"
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

    auto display = Display();
    display.initialize();
    display.clear(0);

    auto palette = Palette(Color(3, 4, 5), Color(2, 28, 4));

    auto canvas = Canvas(display, palette);
    canvas.dimension(Shape{800, 480});
    canvas.fill(Shape{800, 480}, 0);
    canvas.move(Position{25, 25});
    Label("0123456789", Font::small).draw(canvas);
    canvas.adjust(Direction::DOWN, Shape{0, 62}, 10);
    Label("abcdefghiJKLMNOPQRST", Font::small).draw(canvas);
    canvas.adjust(Direction::DOWN, Shape{0, 62}, 10);
    Label("\x01~!@#$%^&*()[]{}<>_+", Font::small).draw(canvas);
    canvas.adjust(Direction::DOWN, Shape{0, 62}, 10);

    int value = 0;
    auto integer = Integer(value, Font::small);
    while (true) {
        integer.draw(canvas);
        integer.update(++value);
        _delay_ms(10);
    }

    return 0;
}
