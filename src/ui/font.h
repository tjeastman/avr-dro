#ifndef FONT_H_
#define FONT_H_

#include "common.h"
#include "canvas.h"

namespace UI {
    class Character {
    private:
        const unsigned char *data_;
        int length_;
        Shape shape_;
    public:
        Character(const unsigned char *);
        const Shape &shape() const { return shape_; }
        void draw(const Canvas &, const Color &) const;
    };

    class Font {
    private:
        Character *characters_;
        Character *character_invalid_;
        signed int offset_;
        signed int length_;
    public:
        static Font medium;
        Font(Character *, Character *, signed char, signed char);
        const Character *character(signed char) const;
        const Character *digit(unsigned int) const;
    };
}

#endif
