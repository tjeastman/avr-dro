#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "common.h"

class Display {
private:
    void transmit(unsigned int);
    void command(unsigned int);
    void command(unsigned int, unsigned int);
public:
    Display() {};
    void initialize();
    void clear(unsigned int);
    void data(unsigned int);
    void address(unsigned int, unsigned int, unsigned int, unsigned int);
};

#endif
