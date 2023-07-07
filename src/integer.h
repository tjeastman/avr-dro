#ifndef INTEGER_H_
#define INTEGER_H_

#include "color.h"
#include "canvas.h"
#include "control.h"
#include "font.h"

class Integer : public Control {
private:
    struct Value {
        bool negative;
        union {
            int value;
            unsigned int magnitude;
        };
        Value(int);
    };
    Value value_;
    const Font &font_;
    const Color &color_;
    bool changed_;
    void draw_sign(Canvas &);
    void draw_magnitude(Canvas &);
public:
    Integer(int, const Font &, const Color &);
    void draw(Canvas) override;
    void update(int);
};

#endif
