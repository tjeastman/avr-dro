#ifndef UI_COMMON_H_
#define UI_COMMON_H_

#include <stdint.h>

namespace ui {

enum class Direction {
    NONE,
    LEFT,
    UP,
    RIGHT,
    DOWN
};

struct Shape {
    int width;
    int height;
    void expand(Direction, Shape, int8_t);
    bool contains(int16_t, int16_t) const;
};

struct Position {
    int x;
    int y;
    void adjust(Direction, Shape, int8_t);
};

} // namespace ui

#endif // UI_COMMON_H_
