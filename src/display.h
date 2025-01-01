#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "ui/common.h"

class Display {
public:
    enum class Orientation {
        PORTRAIT, LANDSCAPE
    };
private:
    UI::Shape shape_;
public:
    Display(): shape_{0, 0} {}
    UI::Shape shape() const { return shape_; }
    void initialize(Orientation);
    void data(unsigned int) const;
    void address(unsigned int, unsigned int, unsigned int, unsigned int) const;
private:
    void transmit(unsigned int) const;
    void command(unsigned int) const;
    void command(unsigned int, unsigned int) const;
};

#endif
