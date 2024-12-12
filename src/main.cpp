#include <avr/io.h>
#include <util/delay.h>

#include "calibration.h"
#include "canvas.h"
#include "color.h"
#include "common.h"
#include "control.h"
#include "display.h"
#include "grid.h"
#include "integer.h"
#include "label.h"
#include "touch.h"

class MainPanel : public Control {
private:
    Label labelX_;
    Label labelY_;
    Integer integerX_;
    Integer integerY_;
    Grid gridX_;
    Grid gridY_;
    Grid grid_;
public:
    MainPanel(Color &);
    void draw(Canvas) override;
    void press(const Position &) override;
    void release(const Position &) override;
};

MainPanel::MainPanel(Color &color):
    labelX_{"X:", Font::small, color},
    labelY_{"Y:", Font::small, color},
    integerX_{-1, Font::small, color},
    integerY_{-1, Font::small, color},
    gridX_{Direction::RIGHT},
    gridY_{Direction::RIGHT},
    grid_{Direction::DOWN}
{
    gridX_.add(&labelX_);
    gridX_.add(&integerX_);
    gridY_.add(&labelY_);
    gridY_.add(&integerY_);
    grid_.add(&gridX_);
    grid_.add(&gridY_);
}

void MainPanel::draw(Canvas canvas)
{
    grid_.draw(canvas);
}

void MainPanel::press(const Position &position)
{
    integerX_.update(position.x);
    integerY_.update(position.y);
}

void MainPanel::release(const Position &position)
{
    integerX_.update(0);
    integerY_.update(0);
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

    Display display = Display();
    display.initialize(Display::Orientation::PORTRAIT);

    // Shape shape = Shape{display.width(), display.height()};
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
    auto panel0 = CalibrationPanel(procedure, color);
    while (!procedure.done()) {
        touch.dispatch(panel0);
        panel0.draw(canvas);
        _delay_ms(10);
    }
    procedure.update(calibration);

    canvas.dimension(shape);
    canvas.fill(shape);

    MainPanel panel = MainPanel(color);
    panel.draw(canvas);

    while (true) {
        touch.dispatch(panel);
        panel.draw(canvas);
        _delay_ms(10);
    }

    return 0;
}
