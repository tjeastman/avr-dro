#ifndef COMMAND_H_
#define COMMAND_H_

#include "serial.h"

class Command {
private:
    char axis_;
    int position_;
    int rate_;

public:
    Command();
    friend const Serial& operator<<(const Serial&, const Command&);
    friend class CommandQueue;
};

class CommandQueue {
private:
    Command commands_[20];
    int head_;
    int tail_;

public:
    CommandQueue();
    int size() const;
    void project(char, int, int);
    void something(const Serial&);
};

#endif // COMMAND_H_
