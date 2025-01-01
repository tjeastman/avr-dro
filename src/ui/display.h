#ifndef UI_DISPLAY_H_
#define UI_DISPLAY_H_

namespace ui {

class Display {
public:
    virtual void data(unsigned int) const = 0;
    virtual void address(unsigned int, unsigned int, unsigned int, unsigned int) const = 0;
};

}  // namespace ui

#endif  // UI_DISPLAY_H_
