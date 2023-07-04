#ifndef FONT_H_
#define FONT_H_

#include "common.h"
#include "canvas.h"

class Character {
private:
    const unsigned char *data_;
    int length_;
public:
    Shape shape;
    Character(const unsigned char *);
    void draw(Canvas &) const;
};

class Font {
private:
    Character *characters_;
    Character *character_invalid_;
    signed int offset_;
    signed int length_;
public:
    static Font small;
    Font(Character *, Character *, signed char, signed char);
    const Character *character(signed char) const;
    const Character *digit(unsigned int) const;
};

#endif
