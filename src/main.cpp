#include <avr/io.h>
#include <util/delay.h>

#include "box.h"
#include "canvas.h"
#include "color.h"
#include "common.h"
#include "display.h"
#include "font.h"
#include "grid.h"
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

    auto display = Display(Display::Orientation::PORTRAIT);
    display.initialize();
    display.clear(0);

    auto palette = Palette(Color(3, 4, 5), Color(2, 28, 4));

    auto shape = Shape{display.width(), display.height()};
    auto canvas = Canvas(display, palette);
    canvas.dimension(shape);
    canvas.fill(shape, 0);
    canvas.move(Position{25, 25});

    Label label1 = Label("0123456789", Font::small);
    Label label2 = Label("abcdefghijklm", Font::small);
    Label label3 = Label("nopqrstuvwxyz", Font::small);
    Label label4 = Label("ABCDEFGHIJKLM", Font::small);
    Label label5 = Label("NOPQRSTUVWXYZ", Font::small);
    Label label6 = Label("\x01~!@#$%^&*()", Font::small);
    Integer integer = Integer(0, Font::small);
    Integer integer0 = Integer(0, Font::small);
    Box box(&integer);
    InvisibleBox box0(&integer0);

    Grid grid = Grid(Direction::DOWN);
    grid.add(&label1);
    grid.add(&label2);
    grid.add(&label3);
    grid.add(&label4);
    grid.add(&label5);
    grid.add(&label6);
    grid.add(&box0);
    grid.add(&box);
    grid.draw(canvas);

    int value = 0;
    while (true) {
        integer.update(++value);
        integer0.update(value);
        if (value % 20 == 5) {
            box.hide();
        } else {
            box.show();
        }
        grid.draw(canvas);
        _delay_ms(10);
    }

    return 0;
}
