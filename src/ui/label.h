#ifndef UI_LABEL_H_
#define UI_LABEL_H_

#include "canvas.h"
#include "control.h"

namespace ui {

class Label : public Control {
protected:
    const char *text_;
    bool changed_;
public:
    Label(const char *);
    void draw(Canvas) override;
};

}  // namespace ui

#endif  // UI_LABEL_H_
