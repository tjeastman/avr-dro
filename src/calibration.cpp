#include "calibration.h"

#include <avr/eeprom.h>
#include <stdint.h>

#include "ui/common.h"

Calibration::Calibration()
{
    eeprom_read_block((void*)theta_, 0, 2 * 3 * sizeof(float));
}

ui::Position Calibration::translate(ui::Position position) const
{
    int16_t x = position.x;
    int16_t y = position.y;
    position.x = theta_[0][0] * x + theta_[0][1] * y + theta_[0][2];
    position.y = theta_[1][0] * x + theta_[1][1] * y + theta_[1][2];
    return position;
}
