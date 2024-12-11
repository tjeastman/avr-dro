#include "panel.h"

Panel::Panel(Color &fg):
    label1_{"0123456789", Font::small, fg},
    label2_{"abcdefghijklm", Font::small, fg},
    label3_{"nopqrstuvwxyz", Font::small, fg},
    label4_{"ABCDEFGHIJKLM", Font::small, fg},
    label5_{"NOPQRSTUVWXYZ", Font::small, fg},
    label6_{"\x01~!@#$%^&*()", Font::small, fg},
    integer_{0, Font::small, fg},
    integer0_{0, Font::small, fg},
    box_{&integer_, fg},
    box0_{&integer0_},
    grid_{Direction::DOWN}
{
    grid_.add(&label1_);
    grid_.add(&label2_);
    grid_.add(&label3_);
    grid_.add(&label4_);
    grid_.add(&label5_);
    grid_.add(&label6_);
    grid_.add(&box0_);
    grid_.add(&box_);
}

void Panel::draw(Canvas canvas)
{
    grid_.draw(canvas);
}

void Panel::update(int value)
{
    integer_.update(value);
    integer0_.update(value);
    if (value % 20 == 5) {
        box_.hide();
    } else {
        box_.show();
    }
}
