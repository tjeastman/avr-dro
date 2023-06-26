#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

#include "common.h"
#include "palette.h"

class Display {
private:
    void transmit(uint16_t);
    void command(uint16_t);
    void command(uint16_t, uint16_t);
    void data(uint16_t);
    void address(uint16_t, uint16_t, uint16_t, uint16_t);
public:
    Display() {};
    void initialize();
    void blank();
    void fill(Position, Shape, uint16_t);
};

#endif
