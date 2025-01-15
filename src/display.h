#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

#include "ui/common.h"
#include "ui/display.h"

class Display : public ui::Display {
public:
    enum class Orientation {
        PORTRAIT,
        LANDSCAPE
    };

private:
    ui::Shape shape_;

public:
    Display()
        : shape_ { 0, 0 }
    {
    }
    ui::Shape shape() const { return shape_; }
    void initialize(Orientation);
    void data(uint16_t) const override;
    void address(uint16_t, uint16_t, uint16_t, uint16_t) const override;

private:
    void transmit(uint16_t) const;
    void command(uint16_t) const;
    void command(uint16_t, uint16_t) const;
};

#endif // DISPLAY_H_
