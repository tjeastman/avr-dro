#ifndef PENDANT_H_
#define PENDANT_H_

#include <stdint.h>

class PendantAxis {
private:
    int minimum_;
    int maximum_;
    int position_;
public:
    PendantAxis(): minimum_{INT16_MIN}, maximum_{INT16_MAX}, position_{0} {}
    PendantAxis(int minimum, int maximum): minimum_{minimum}, maximum_{maximum}, position_{0} {}
    void move(int) volatile;
    int position(int) const;
};

class Pendant {
private:
    static signed char lookup_[16];
    PendantAxis axes_[4];
    int index_;
    int multiplier_;
    unsigned char state_;
public:
    Pendant();
    void turn(unsigned char) volatile;
    void press(unsigned char) volatile;
    const PendantAxis &axis(char) const;
};

#endif
