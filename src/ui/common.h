#ifndef UI_COMMON_H_
#define UI_COMMON_H_

namespace UI {
    enum class Direction {
        NONE, LEFT, UP, RIGHT, DOWN
    };

    struct Shape {
        int width;
        int height;
        void expand(Direction, Shape, signed char);
        bool contains(int, int) const;
    };

    struct Position {
        int x;
        int y;
        void adjust(Direction, Shape, signed char);
    };
}

#endif  // UI_COMMON_H_
