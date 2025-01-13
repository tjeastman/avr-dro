#ifndef COMMAND_H_
#define COMMAND_H_

#include "pendant.h"
#include "serial.h"

class Command {
private:
    char axis_;
    int position_;
    int rate_;
public:
    Command(): axis_{0}, position_{0}, rate_{0} {}
    Command(char axis): axis_{axis}, position_{0}, rate_{0} {}
    Command(char axis, int position, int rate): axis_{axis}, position_{position}, rate_{rate} {}
    friend const Serial &operator<<(const Serial &, const Command &);
};

#endif  // COMMAND_H_
