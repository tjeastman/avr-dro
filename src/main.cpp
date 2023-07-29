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

    Color fg = Color(2, 28, 4);
    Label label1 = Label("0123456789", Font::small, fg);
    Label label2 = Label("abcdefghijklm", Font::small, fg);
    Label label3 = Label("nopqrstuvwxyz", Font::small, fg);
    Label label4 = Label("ABCDEFGHIJKLM", Font::small, fg);
    Label label5 = Label("NOPQRSTUVWXYZ", Font::small, fg);
    Label label6 = Label("\x01~!@#$%^&*()", Font::small, fg);
    Integer integer = Integer(0, Font::small, fg);
    Integer integer0 = Integer(0, Font::small, fg);
    Box box(&integer, fg);
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
