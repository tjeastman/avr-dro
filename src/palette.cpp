#include "palette.h"
#include "color.h"

unsigned char Palette::scale_[2][32] = {
    {0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10},
    {0, 1, 1, 2, 3, 3, 4, 5, 5, 6, 7, 7, 8, 9, 9, 10, 11, 11, 12, 13, 13, 14, 15, 15, 16, 17, 17, 18, 19, 19, 20, 21}
};

Palette::Palette(Color bg, Color fg)
{
    colors_[0] = bg.value;
    colors_[1] = Color
        (bg.R() + (scale_[0][fg.R()] - scale_[0][bg.R()]),
         bg.G() + (scale_[0][fg.G()] - scale_[0][bg.G()]),
         bg.B() + (scale_[0][fg.B()] - scale_[0][bg.B()])).value;
    colors_[2] = Color
        (bg.R() + (scale_[1][fg.R()] - scale_[1][bg.R()]),
         bg.G() + (scale_[1][fg.G()] - scale_[1][bg.G()]),
         bg.B() + (scale_[1][fg.B()] - scale_[1][bg.B()])).value;
    colors_[3] = fg.value;
}

unsigned int Palette::color(unsigned char v) const
{
    return colors_[v];
}
