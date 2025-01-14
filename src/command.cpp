#include "command.h"

#include "serial.h"

const Serial &operator<<(const Serial &serial, const Command &command)
{
    serial << "G90 G01 ";
    serial << command.axis_;

    // TODO: implement robust absolute value
    int position = command.position_;
    if (position < 0) {
        position *= -1;
        serial << '-';
    }

    serial.write(position / 100, 1);
    serial << '.';
    serial.write(position % 100, 2);

    serial << ' ';
    serial << 'F';
    serial.write(command.rate_ / 10, 1);
    serial << '.';
    serial.write(command.rate_ % 10, 1);
    serial << "\r\n";

    return serial;
}

int CommandQueue::size() const
{
    return (head_ + 20 - tail_) % 20;
}

void CommandQueue::project(char axis, int position, int rate)
{
    if (axis == 0) {
        return;
    }

    if (size() < 2) {
        head_++;
    } else if (commands_[head_].axis_ != axis) {
        head_++;
    }

    if (head_ >= 20) {
        head_ = 0;
    }

    commands_[head_].axis_ = axis;
    commands_[head_].position_ = position;
    commands_[head_].rate_ = rate;
}

void CommandQueue::something(const Serial &serial)
{
    if (size() == 0) {
        return;
    }

    serial << commands_[tail_++];

    if (tail_ >= 20) {
        tail_ = 0;
    }
}
