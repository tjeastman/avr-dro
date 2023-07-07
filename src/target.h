#ifndef TARGET_H_
#define TARGET_H_

#include "canvas.h"
#include "color.h"
#include "common.h"
#include "control.h"

class Target : public Control {
private:
    const Color &color_;
    bool pressed_;
public:
    Target(int, const Color &);
    void draw(Canvas) override;
    void press(const Position &) override;
    void release(const Position &) override;
};

#endif
