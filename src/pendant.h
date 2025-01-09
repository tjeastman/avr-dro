#ifndef PENDANT_H_
#define PENDANT_H_

#include "coordinate.h"

class PendantAxis {
private:
    int minimum_;
    int maximum_;
    int &position_;
public:
    PendantAxis(int, int, int &);
    void increment(int) volatile;
    void decrement(int) volatile;
};

class Pendant {
private:
    int position_[3];
    PendantAxis axes_[3];
    int rate_;
    int index_;
    int multiplier_;
    unsigned char state_;
public:
    Pendant();
    void turn(unsigned char) volatile;
    void press(unsigned char) volatile;
    void pace(unsigned int) volatile;
    void project(CoordinateSystem &) const;
};

#endif  // PENDANT_H_
