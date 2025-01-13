#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "calibration.h"
#include "command.h"
#include "coordinate.h"
#include "display.h"
#include "pendant.h"
#include "serial.h"
#include "touch.h"
#include "ui/canvas.h"
#include "ui/color.h"
#include "ui/common.h"

int main(void)
{
    DDRC = 0xff;
    DDRA = 0xff;

    DDRD |= _BV(PD7); // RS
    DDRG |= _BV(PG2); // WR
    DDRG |= _BV(PG1); // CS
    DDRG |= _BV(PG0); // RST
    DDRL |= _BV(PL6); // RD

    PORTD |= _BV(PD7);
    PORTG |= _BV(PG2);
    PORTG |= _BV(PG1);
    PORTG |= _BV(PG0);
    PORTL |= _BV(PL6);

    PORTG |= _BV(PG0); // RST=HIGH
    _delay_ms(10);
    PORTG &= ~_BV(PG0); // RST=LOW
    _delay_ms(100);
    PORTG |= _BV(PG0); // RST=HIGH
    _delay_ms(50);

    PORTG |= _BV(PG1); // CS=HIGH
    PORTG |= _BV(PG2); // WR=HIGH
    PORTG &= ~_BV(PG1); // CS=LOW
    _delay_ms(50);

    // SPI
    // MISO (input) pin 50 PB3
    DDRB |= _BV(PB0); // TP_CS (output) pin 53 PB0
    DDRB |= _BV(PB1); // EX_CLK (output) pin 52 PB1
    DDRB |= _BV(PB2); // MOSI (output) pin 51 PB2
    // enable SPI master with SCK=F_CPU/4
    SPCR = 0;
    SPCR |= _BV(MSTR);
    SPCR |= _BV(SPE);

    PORTB |= _BV(PB0); // deselect

    // configure UART for 115200 baud 8N1
    UBRR0H = 0;
    UBRR0L = 16;
    UCSR0A |= _BV(U2X0);
    UCSR0B |= _BV(RXEN0);
    UCSR0B |= _BV(TXEN0);
    UCSR0C |= _BV(UCSZ01);
    UCSR0C |= _BV(UCSZ00);

    sei();

    Display display = Display();
    display.initialize(Display::Orientation::LANDSCAPE);

    const ui::Shape& shape = display.shape();
    ui::Canvas canvas = ui::Canvas(display);
    canvas.select(ui::Color(0, 0, 0));
    canvas.move(ui::Position { 0, 0 });
    canvas.dimension(shape);
    canvas.fill(shape);

    Serial serial = Serial();
    serial << 'H';
    serial << 'e';
    serial << 'l';
    serial << 'l';
    serial << 'o';
    serial << '!';
    serial << '\r';
    serial << '\n';
    _delay_ms(1000);

    serial << "Hello, world!\r\n";
    _delay_ms(1000);

    serial << "Example commands:\r\n";
    serial << Command();
    serial << Command('X');
    serial << Command('Y');
    serial << Command('Z');
    serial << Command('X', 225, 102);
    serial << Command('Y', -592, 99);
    serial << Command('Z', -3, -10);
    _delay_ms(1000);

    Calibration calibration = Calibration();
    Touch touch = Touch(calibration);

    CoordinatePanel panel = CoordinatePanel();

    Pendant pendant = Pendant();
    Pendant::initialize(&pendant);

    sei();

    while (true) {
        panel.dispatch(touch);
        pendant.project(panel);
        panel.draw(canvas);
    }

    return 0;
}
