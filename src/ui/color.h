#ifndef UI_COLOR_H_
#define UI_COLOR_H_

namespace UI {
    class Color {
    private:
        static unsigned char scale_[2][32];
        unsigned int value_;
    public:
        Color(): value_{0} {}
        Color(unsigned char, unsigned char, unsigned char);
        unsigned int value() const { return value_; }
        Color blend(Color, unsigned char) const;
    private:
        unsigned char R() const;
        unsigned char G() const;
        unsigned char B() const;
    };
}

#endif  // UI_COLOR_H_
