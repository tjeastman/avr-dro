#ifndef UI_DISPLAY_H_
#define UI_DISPLAY_H_

#include <stdint.h>

namespace ui {

class Display {
public:
    virtual void data(uint16_t) const = 0;
    virtual void address(uint16_t, uint16_t, uint16_t, uint16_t) const = 0;
};

} // namespace ui

#endif // UI_DISPLAY_H_
