#ifndef COLOR_H_
#define COLOR_H_

class Color {
private:
    static unsigned char scale_[2][32];
    unsigned int value_;
    unsigned char R() const;
    unsigned char G() const;
    unsigned char B() const;
public:
    Color(): value_{0} {};
    Color(unsigned char, unsigned char, unsigned char);
    Color blend(Color, unsigned char) const;
    unsigned int value() const { return value_; };
};

#endif
