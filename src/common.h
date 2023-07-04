#ifndef COMMON_H_
#define COMMON_H_

enum class Direction {
    NONE = 0,
    LEFT = 1,
    UP = 2,
    RIGHT = 3,
    DOWN = 4,
};

struct Shape {
    int width;
    int height;
};

struct Position {
    int x;
    int y;
    void adjust(Direction, Shape, signed char);
};

#endif
