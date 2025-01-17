#ifndef PENDANT_H_
#define PENDANT_H_

#include <stdint.h>

#include "command.h"

class PendantAxisSpace {
public:
    virtual void project(char, int16_t, int16_t) = 0;
};

class PendantAxis {
private:
    char identifier_;
    int16_t minimum_;
    int16_t maximum_;
    int16_t position_;
    int16_t rate_;

public:
    PendantAxis(char, int16_t, int16_t);
    void increment(int16_t) volatile;
    void decrement(int16_t) volatile;
    void pace(int16_t) volatile;
    void project(PendantAxisSpace&) volatile const;
    void project(CommandQueue&) volatile const;
};

class Pendant {
private:
    PendantAxis axes_[4];
    int16_t index_;
    int16_t delta_;
    uint8_t state_;
    CommandQueue& commands_;
    bool changed_;

public:
    Pendant(CommandQueue&);
    void turn(uint8_t) volatile;
    void press(uint8_t) volatile;
    void pace(uint16_t) volatile;
    void project(PendantAxisSpace&) const;
    static Pendant* instance;
    static void initialize(Pendant*);
};

#endif // PENDANT_H_
