#include <avr/pgmspace.h>

#include "font.inc"
#include "font.h"

Character::Character(const unsigned char *data)
{
    data_ = data + 6;
    length_ = pgm_read_word(&data[0]);
    shape.width = pgm_read_word(&data[2]);
    shape.height = pgm_read_word(&data[4]);
}

void Character::draw(const Canvas &canvas, const Color &color) const
{
    canvas.dimension(shape);
    for (int i = 0; i < length_; ++i) {
        unsigned char b = pgm_read_byte(&data_[i]);
        canvas.dot(color, b & 0x03, b >> 2);
    }
}

Font::Font(Character *characters, Character *character_invalid, signed char offset, signed char length)
{
    characters_ = characters;
    character_invalid_ = character_invalid;
    offset_ = offset;
    length_ = length;
}

const Character *Font::character(signed char code) const
{
    code -= offset_;
    if (code < 0) {
        return character_invalid_;
    } else if (code >= length_) {
        return character_invalid_;
    }
    return &characters_[code];
}

const Character *Font::digit(unsigned int x) const
{
    return character('0' + x % 10);
}

static Character characters[] = {
    Character(CHARACTER_032),
    Character(CHARACTER_033),
    Character(CHARACTER_034),
    Character(CHARACTER_035),
    Character(CHARACTER_036),
    Character(CHARACTER_037),
    Character(CHARACTER_038),
    Character(CHARACTER_039),
    Character(CHARACTER_040),
    Character(CHARACTER_041),
    Character(CHARACTER_042),
    Character(CHARACTER_043),
    Character(CHARACTER_044),
    Character(CHARACTER_045),
    Character(CHARACTER_046),
    Character(CHARACTER_047),
    Character(CHARACTER_048),
    Character(CHARACTER_049),
    Character(CHARACTER_050),
    Character(CHARACTER_051),
    Character(CHARACTER_052),
    Character(CHARACTER_053),
    Character(CHARACTER_054),
    Character(CHARACTER_055),
    Character(CHARACTER_056),
    Character(CHARACTER_057),
    Character(CHARACTER_058),
    Character(CHARACTER_059),
    Character(CHARACTER_060),
    Character(CHARACTER_061),
    Character(CHARACTER_062),
    Character(CHARACTER_063),
    Character(CHARACTER_064),
    Character(CHARACTER_065),
    Character(CHARACTER_066),
    Character(CHARACTER_067),
    Character(CHARACTER_068),
    Character(CHARACTER_069),
    Character(CHARACTER_070),
    Character(CHARACTER_071),
    Character(CHARACTER_072),
    Character(CHARACTER_073),
    Character(CHARACTER_074),
    Character(CHARACTER_075),
    Character(CHARACTER_076),
    Character(CHARACTER_077),
    Character(CHARACTER_078),
    Character(CHARACTER_079),
    Character(CHARACTER_080),
    Character(CHARACTER_081),
    Character(CHARACTER_082),
    Character(CHARACTER_083),
    Character(CHARACTER_084),
    Character(CHARACTER_085),
    Character(CHARACTER_086),
    Character(CHARACTER_087),
    Character(CHARACTER_088),
    Character(CHARACTER_089),
    Character(CHARACTER_090),
    Character(CHARACTER_091),
    Character(CHARACTER_092),
    Character(CHARACTER_093),
    Character(CHARACTER_094),
    Character(CHARACTER_095),
    Character(CHARACTER_096),
    Character(CHARACTER_097),
    Character(CHARACTER_098),
    Character(CHARACTER_099),
    Character(CHARACTER_100),
    Character(CHARACTER_101),
    Character(CHARACTER_102),
    Character(CHARACTER_103),
    Character(CHARACTER_104),
    Character(CHARACTER_105),
    Character(CHARACTER_106),
    Character(CHARACTER_107),
    Character(CHARACTER_108),
    Character(CHARACTER_109),
    Character(CHARACTER_110),
    Character(CHARACTER_111),
    Character(CHARACTER_112),
    Character(CHARACTER_113),
    Character(CHARACTER_114),
    Character(CHARACTER_115),
    Character(CHARACTER_116),
    Character(CHARACTER_117),
    Character(CHARACTER_118),
    Character(CHARACTER_119),
    Character(CHARACTER_120),
    Character(CHARACTER_121),
    Character(CHARACTER_122),
    Character(CHARACTER_123),
    Character(CHARACTER_124),
    Character(CHARACTER_125),
    Character(CHARACTER_126),
};

static Character character_invalid = Character(CHARACTER_INVALID);

Font Font::medium = Font{characters, &character_invalid, 32, 95};
