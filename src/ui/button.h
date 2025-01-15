#ifndef UI_BUTTON_H_
#define UI_BUTTON_H_

#include "canvas.h"
#include "control.h"
#include "label.h"

namespace ui {

class Button : public Label {
public:
    Button(const char*);
    void draw(Canvas) override;
};

} // namespace ui

#endif // UI_BUTTON_H_
