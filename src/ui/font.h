#ifndef UI_FONT_H_
#define UI_FONT_H_

#include <stdint.h>

#include "canvas.h"
#include "common.h"

namespace ui {

class Character {
private:
    const uint8_t* data_;
    int length_;
    Shape shape_;

public:
    Character(const uint8_t*);
    const Shape& shape() const { return shape_; }
    void draw(const Canvas&, const Color&) const;
};

class Font {
private:
    Character* characters_;
    Character* character_invalid_;
    int16_t offset_;
    int16_t length_;

public:
    static Font medium;
    Font(Character*, Character*, int8_t, int8_t);
    const Character* character(int8_t) const;
    const Character* digit(uint16_t) const;
};

} // namespace ui

#endif // UI_FONT_H_
