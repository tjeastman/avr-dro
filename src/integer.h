#ifndef INTEGER_H_
#define INTEGER_H_

#include "canvas.h"
#include "font.h"

class Integer {
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
    Font &font_;
    void draw_sign(Canvas &) const;
    void draw_magnitude(Canvas &) const;
public:
    Integer(int value, Font &font): value_{value}, font_{font} {};
    void draw(Canvas &) const;
    void update(int);
};

#endif
