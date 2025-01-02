#ifndef UI_BUTTON_H_
#define UI_BUTTON_H_

#include "canvas.h"
#include "control.h"
#include "label.h"

namespace UI {
    class Button : public Label {
    private:
        bool pressed_;
    public:
        Button(const ControlProperties &, const char *);
        void draw(Canvas) override;
    };
}

#endif  // UI_BUTTON_H_
