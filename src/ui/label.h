#ifndef LABEL_H_
#define LABEL_H_

#include "canvas.h"
#include "control.h"

class Label : public Control {
protected:
    const char *text_;
    bool changed_;
public:
    Label(const ControlProperties &, const char *);
    void draw(Canvas) override;
};

#endif
