#ifndef COLOR_H_
#define COLOR_H_

struct Color {
    unsigned int value;
    Color(unsigned char, unsigned char, unsigned char);
    unsigned char R() const;
    unsigned char G() const;
    unsigned char B() const;
};

#endif
