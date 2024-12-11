#include <avr/io.h>
#include <util/delay.h>

#include "canvas.h"
#include "color.h"
#include "common.h"
#include "display.h"
#include "panel.h"

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

    auto display = Display(Display::Orientation::PORTRAIT);
    display.initialize();

    auto shape = Shape{display.width(), display.height()};
    auto canvas = Canvas(display);
    canvas.dimension(shape);
    canvas.fill(shape, Color(0, 0, 0), 0);

    canvas.select(Color(30, 0, 0));
    canvas.dimension(shape);
    canvas.fill(shape);

    canvas.select(Color(0, 30, 0));
    canvas.dimension(shape);
    canvas.fill(shape);

    canvas.select(Color(0, 0, 30));
    canvas.dimension(shape);
    canvas.fill(shape);

    canvas.select(Color(3, 4, 5));
    canvas.dimension(shape);
    canvas.fill(shape);

    canvas.move(Position{25, 25});

    auto color = Color(2, 28, 4);
    auto panel = Panel(color);
    panel.draw(canvas);

    int value = 0;
    while (true) {
        panel.update(++value);
        panel.draw(canvas);
        _delay_ms(10);
    }

    return 0;
}
