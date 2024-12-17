#ifndef COMMON_H_
#define COMMON_H_

enum class Direction {
    NONE, LEFT, UP, RIGHT, DOWN
};

struct Shape {
    int width;
    int height;
    void expand(Direction, Shape, signed char);
    bool contains(int, int);
};

struct Position {
    int x;
    int y;
    void adjust(Direction, Shape, signed char);
};

#endif
