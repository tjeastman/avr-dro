#ifndef INTEGER_H_
#define INTEGER_H_

#include "color.h"
#include "canvas.h"
#include "control.h"
#include "font.h"

class UnsignedInteger : public Control {
private:
    static unsigned int divisors_[5];
    const Font &font_;
    const Color &color_;
    unsigned char digits_;
    bool changed_;
    unsigned int magnitude_;
public:
    UnsignedInteger(unsigned char, const Font &, const Color &);
    void update(unsigned int);
    void draw(Canvas) override;
};

#endif
