#include <avr/eeprom.h>

#include "calibration.h"

Calibration::Calibration()
{
    eeprom_read_block((void *)theta_, 0, 2 * 3 * sizeof(float));
}

UI::Position Calibration::translate(UI::Position position) const
{
    int x = position.x;
    int y = position.y;
    position.x = theta_[0][0] * x + theta_[0][1] * y + theta_[0][2];
    position.y = theta_[1][0] * x + theta_[1][1] * y + theta_[1][2];
    return position;
}
