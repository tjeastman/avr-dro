#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "canvas.h"
#include "color.h"
#include "common.h"
#include "display.h"
#include "touch.h"

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

    // SPI
    // MISO (input) pin 50 PB3
    DDRB |= _BV(0); // TP_CS (output) pin 53 PB0
    DDRB |= _BV(1); // EX_CLK (output) pin 52 PB1
    DDRB |= _BV(2); // MOSI (output) pin 51 PB2
    // enable SPI master with SCK=F_CPU/4
    SPCR = 0;
    SPCR |= (1 << MSTR);
    SPCR |= (1 << SPE);

    PORTB |= _BV(0); // deselect

    // set up external interrupt (INT0) on any change
    EIMSK |= _BV(INT0);
    EICRA |= _BV(ISC00);

    sei();

    Display display = Display();
    display.initialize(Display::Orientation::LANDSCAPE);

    Shape shape = display.shape();
    Canvas canvas = Canvas(display);

    canvas.select(Color(0, 0, 0));
    canvas.move(Position{0, 0});
    canvas.dimension(shape);
    canvas.fill(shape);

    Color color = Color(2, 28, 4);

    Calibration calibration = Calibration();
    Touch touch = Touch(calibration);

    auto procedure = CalibrationProcedure(shape);
    auto panel = CalibrationPanel(procedure, color);
    while (!procedure.done()) {
        touch.dispatch(panel);
        panel.draw(canvas);
        _delay_ms(10);
    }
    procedure.update(calibration);

    calibration.save();

    canvas.dimension(shape);
    canvas.fill(shape);

    while (true) {}

    return 0;
}
