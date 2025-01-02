#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "ui/common.h"
#include "ui/display.h"

class Display : public UI::Display {
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
    void data(unsigned int) const override;
    void address(unsigned int, unsigned int, unsigned int, unsigned int) const override;
private:
    void transmit(unsigned int) const;
    void command(unsigned int) const;
    void command(unsigned int, unsigned int) const;
};

#endif
