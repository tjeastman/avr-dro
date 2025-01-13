#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "calibration.h"
#include "coordinate.h"
#include "display.h"
#include "touch.h"
#include "pendant.h"
#include "ui/canvas.h"
#include "ui/color.h"
#include "ui/common.h"

extern Pendant pendant;

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
    SPCR |= _BV(MSTR);
    SPCR |= _BV(SPE);

    PORTB |= _BV(0); // deselect

    // set up analog to digital converter
    ADMUX |= _BV(REFS0); // AVCC with external capacitor at AREF pin
    ADMUX |= _BV(MUX1);
    ADMUX |= _BV(MUX2);
    ADCSRB |= _BV(MUX5); // ADC14

    ADCSRA |= _BV(ADPS0);
    ADCSRA |= _BV(ADPS1);
    ADCSRA |= _BV(ADPS2);

    ADCSRA |= _BV(ADEN);
    ADCSRA |= _BV(ADATE); // auto trigger (free running mode)
    ADCSRA |= _BV(ADIE);

    ADCSRA |= _BV(ADSC); // start conversion

    // set up external interrupt (INT0) on any change
    EIMSK |= _BV(INT0);
    EICRA |= _BV(ISC00);

    // set up pin change interrupts
    PCICR |= _BV(PCIE2);
    PCMSK2 |= _BV(PCINT16);
    PCMSK2 |= _BV(PCINT17);
    PCMSK2 |= _BV(PCINT18);
    PCMSK2 |= _BV(PCINT19);
    PCMSK2 |= _BV(PCINT20);
    PCMSK2 |= _BV(PCINT21);

    sei();

    Display display = Display();
    display.initialize(Display::Orientation::LANDSCAPE);

    const ui::Shape &shape = display.shape();
    ui::Canvas canvas = ui::Canvas(display);
    canvas.select(ui::Color(0, 0, 0));
    canvas.move(ui::Position{0, 0});
    canvas.dimension(shape);
    canvas.fill(shape);

    Calibration calibration = Calibration();
    Touch touch = Touch(calibration);

    CoordinatePanel panel = CoordinatePanel();

    while (true) {
        panel.dispatch(touch);
        pendant.project(panel);
        panel.draw(canvas);
    }

    return 0;
}
