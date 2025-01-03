#ifndef PENDANT_H_
#define PENDANT_H_

#include "coordinate.h"

class PendantAxis {
private:
    int minimum_;
    int maximum_;
    int position_;
public:
    PendantAxis(int, int);
    void move(int) volatile;
    void project(CoordinateAxis &) const;
};

class Pendant {
private:
    PendantAxis axes_[3];
    int index_;
    int multiplier_;
    unsigned char state_;
public:
    Pendant();
    void turn(unsigned char) volatile;
    void press(unsigned char) volatile;
    void project(CoordinateSystem &) const;
};

#endif
