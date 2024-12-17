#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "common.h"

class Display {
public:
    enum class Orientation {
        PORTRAIT, LANDSCAPE
    };
private:
    void transmit(unsigned int) const;
    void command(unsigned int) const;
    void command(unsigned int, unsigned int) const;
    Shape shape_;
public:
    Display(): shape_{0, 0} {}
    void initialize(Orientation);
    void data(unsigned int) const;
    void address(unsigned int, unsigned int, unsigned int, unsigned int) const;
    Shape shape() const { return shape_; }
};

#endif
