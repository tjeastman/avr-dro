#include "control.h"

#include "color.h"
#include "font.h"

namespace ui {

const ControlProperties& Control::properties_{Font::medium, Color(2, 28, 4)};

bool Control::contains(const Position &position) const
{
    return shape_.contains(position.x, position.y);
}

}  // namespace ui
