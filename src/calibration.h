#ifndef CALIBRATION_H_
#define CALIBRATION_H_

#include "common.h"

class Calibration {
private:
    float theta_[2][3];
public:
    Calibration();
    Position translate(Position) const;
};

#endif
