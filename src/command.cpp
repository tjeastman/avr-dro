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
