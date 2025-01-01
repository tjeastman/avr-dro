#ifndef CALIBRATION_H_
#define CALIBRATION_H_

#include "ui/common.h"

class Calibration {
private:
    float theta_[2][3];
public:
    Calibration();
    UI::Position translate(UI::Position) const;
};

#endif
