#ifndef TOUCH_H_
#define TOUCH_H_

#include "calibration.h"
#include "common.h"
#include "control.h"

enum class TouchEvent {
    NONE, PRESS, RELEASE
};

struct TouchState {
    TouchEvent event;
    Position position;
    int readings;
    TouchState();
    void press(int, int, int);
    void release();
};

class Touch {
private:
    Calibration &calibration_;
    TouchState state_;
    unsigned char transmit8(unsigned char);
    unsigned int transmit16(unsigned int);
    void update();
    void clear();
    bool interrupt();
    void transition();
public:
    Touch(Calibration &calibration): calibration_{calibration}, state_{} {};
    void dispatch(Control &);
};

#endif
