#ifndef UI_INTEGER_H_
#define UI_INTEGER_H_

#include "canvas.h"
#include "control.h"

namespace UI {

class UnsignedInteger : public Control {
private:
    static unsigned int divisors_[5];
    unsigned char digits_;
    bool changed_;
    unsigned int magnitude_;
public:
    UnsignedInteger(const ControlProperties &, unsigned char);
    void update(unsigned int);
    void draw(Canvas) override;
};

}  // namespace UI

#endif  // UI_INTEGER_H_
