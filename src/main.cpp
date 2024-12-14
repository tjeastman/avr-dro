#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "canvas.h"
#include "color.h"
#include "common.h"
#include "control.h"
#include "display.h"
#include "grid.h"
#include "integer.h"
#include "label.h"
#include "encoder.h"

extern Encoder encoders[3];

class MainPanel : public Control {
private:
    Label labelX_;
    Label labelY_;
    Label labelZ_;
    Integer integerX_;
    Integer integerY_;
    Integer integerZ_;
    Label labelX_unit_;
    Label labelY_unit_;
    Label labelZ_unit_;
    Grid gridX_;
    Grid gridY_;
    Grid gridZ_;
    Grid grid_;
public:
    MainPanel(Color &);
    void draw(Canvas) override;
    void update(Encoder[3]);
};

MainPanel::MainPanel(Color &color):
    labelX_{"X:", Font::medium, color},
    labelY_{"Y:", Font::medium, color},
    labelZ_{"Z:", Font::medium, color},
    integerX_{-1, Font::medium, color},
    integerY_{-1, Font::medium, color},
    integerZ_{-1, Font::medium, color},
    labelX_unit_{"mm", Font::medium, color},
    labelY_unit_{"mm", Font::medium, color},
    labelZ_unit_{"mm", Font::medium, color},
    gridX_{Direction::RIGHT, 20},
    gridY_{Direction::RIGHT, 20},
    gridZ_{Direction::RIGHT, 20},
    grid_{Direction::DOWN, 20}
{
    gridX_.add(&labelX_);
    gridX_.add(&integerX_);
    gridX_.add(&labelX_unit_);
    gridY_.add(&labelY_);
    gridY_.add(&integerY_);
    gridY_.add(&labelY_unit_);
    gridZ_.add(&labelZ_);
    gridZ_.add(&integerZ_);
    gridZ_.add(&labelZ_unit_);
    grid_.add(&gridX_);
    grid_.add(&gridY_);
    grid_.add(&gridZ_);
}

void MainPanel::draw(Canvas canvas)
{
    grid_.draw(canvas);
}

void MainPanel::update(Encoder encoders[3])
{
    integerX_.update(encoders[0].count());
    integerY_.update(encoders[1].count());
    integerZ_.update(encoders[2].count());
}

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
    MainPanel panel = MainPanel(color);

    while (true) {
        panel.update(encoders);
        panel.draw(canvas);
        _delay_ms(10);
    }

    return 0;
}
