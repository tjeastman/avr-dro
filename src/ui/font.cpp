#include <avr/pgmspace.h>

#include "font.inc"
#include "font.h"

UI::Character::Character(const unsigned char *data)
{
    data_ = data + 6;
    length_ = pgm_read_word(&data[0]);
    shape_.width = pgm_read_word(&data[2]);
    shape_.height = pgm_read_word(&data[4]);
}

void UI::Character::draw(const Canvas &canvas, const UI::Color &color) const
{
    canvas.dimension(shape_);
    for (int i = 0; i < length_; ++i) {
        unsigned char b = pgm_read_byte(&data_[i]);
        canvas.dot(color, b & 0x03, b >> 2);
    }
}

UI::Font::Font(UI::Character *characters, Character *character_invalid, signed char offset, signed char length)
{
    characters_ = characters;
    character_invalid_ = character_invalid;
    offset_ = offset;
    length_ = length;
}

const UI::Character *UI::Font::character(signed char code) const
{
    code -= offset_;
    if (code < 0) {
        return character_invalid_;
    } else if (code >= length_) {
        return character_invalid_;
    }
    return &characters_[code];
}

const UI::Character *UI::Font::digit(unsigned int x) const
{
    return character('0' + x % 10);
}

static UI::Character characters[] = {
    UI::Character(CHARACTER_032),
    UI::Character(CHARACTER_033),
    UI::Character(CHARACTER_034),
    UI::Character(CHARACTER_035),
    UI::Character(CHARACTER_036),
    UI::Character(CHARACTER_037),
    UI::Character(CHARACTER_038),
    UI::Character(CHARACTER_039),
    UI::Character(CHARACTER_040),
    UI::Character(CHARACTER_041),
    UI::Character(CHARACTER_042),
    UI::Character(CHARACTER_043),
    UI::Character(CHARACTER_044),
    UI::Character(CHARACTER_045),
    UI::Character(CHARACTER_046),
    UI::Character(CHARACTER_047),
    UI::Character(CHARACTER_048),
    UI::Character(CHARACTER_049),
    UI::Character(CHARACTER_050),
    UI::Character(CHARACTER_051),
    UI::Character(CHARACTER_052),
    UI::Character(CHARACTER_053),
    UI::Character(CHARACTER_054),
    UI::Character(CHARACTER_055),
    UI::Character(CHARACTER_056),
    UI::Character(CHARACTER_057),
    UI::Character(CHARACTER_058),
    UI::Character(CHARACTER_059),
    UI::Character(CHARACTER_060),
    UI::Character(CHARACTER_061),
    UI::Character(CHARACTER_062),
    UI::Character(CHARACTER_063),
    UI::Character(CHARACTER_064),
    UI::Character(CHARACTER_065),
    UI::Character(CHARACTER_066),
    UI::Character(CHARACTER_067),
    UI::Character(CHARACTER_068),
    UI::Character(CHARACTER_069),
    UI::Character(CHARACTER_070),
    UI::Character(CHARACTER_071),
    UI::Character(CHARACTER_072),
    UI::Character(CHARACTER_073),
    UI::Character(CHARACTER_074),
    UI::Character(CHARACTER_075),
    UI::Character(CHARACTER_076),
    UI::Character(CHARACTER_077),
    UI::Character(CHARACTER_078),
    UI::Character(CHARACTER_079),
    UI::Character(CHARACTER_080),
    UI::Character(CHARACTER_081),
    UI::Character(CHARACTER_082),
    UI::Character(CHARACTER_083),
    UI::Character(CHARACTER_084),
    UI::Character(CHARACTER_085),
    UI::Character(CHARACTER_086),
    UI::Character(CHARACTER_087),
    UI::Character(CHARACTER_088),
    UI::Character(CHARACTER_089),
    UI::Character(CHARACTER_090),
    UI::Character(CHARACTER_091),
    UI::Character(CHARACTER_092),
    UI::Character(CHARACTER_093),
    UI::Character(CHARACTER_094),
    UI::Character(CHARACTER_095),
    UI::Character(CHARACTER_096),
    UI::Character(CHARACTER_097),
    UI::Character(CHARACTER_098),
    UI::Character(CHARACTER_099),
    UI::Character(CHARACTER_100),
    UI::Character(CHARACTER_101),
    UI::Character(CHARACTER_102),
    UI::Character(CHARACTER_103),
    UI::Character(CHARACTER_104),
    UI::Character(CHARACTER_105),
    UI::Character(CHARACTER_106),
    UI::Character(CHARACTER_107),
    UI::Character(CHARACTER_108),
    UI::Character(CHARACTER_109),
    UI::Character(CHARACTER_110),
    UI::Character(CHARACTER_111),
    UI::Character(CHARACTER_112),
    UI::Character(CHARACTER_113),
    UI::Character(CHARACTER_114),
    UI::Character(CHARACTER_115),
    UI::Character(CHARACTER_116),
    UI::Character(CHARACTER_117),
    UI::Character(CHARACTER_118),
    UI::Character(CHARACTER_119),
    UI::Character(CHARACTER_120),
    UI::Character(CHARACTER_121),
    UI::Character(CHARACTER_122),
    UI::Character(CHARACTER_123),
    UI::Character(CHARACTER_124),
    UI::Character(CHARACTER_125),
    UI::Character(CHARACTER_126),
};

static UI::Character character_invalid = UI::Character(CHARACTER_INVALID);

UI::Font UI::Font::medium = UI::Font{characters, &character_invalid, 32, 95};
