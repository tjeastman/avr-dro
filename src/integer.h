#ifndef INTEGER_H_
#define INTEGER_H_

#include "color.h"
#include "canvas.h"
#include "control.h"
#include "font.h"

class Integer : public Control {
private:
    static unsigned int divisors_[5];
protected:
    const Font &font_;
    const Color &color_;
    unsigned char digits_;
    unsigned int magnitude_;
public:
    Integer(unsigned char, const Font &, const Color &);
    void draw(Canvas) override;
};

class UnsignedInteger : public Integer
{
public:
    UnsignedInteger(unsigned char, const Font &, const Color &);
    void update(unsigned int);
};

class SignedInteger : public Integer
{
private:
    bool negative_;
public:
    SignedInteger(unsigned char, const Font &, const Color &);
    void draw(Canvas) override;
    void update(int);
};

#endif
