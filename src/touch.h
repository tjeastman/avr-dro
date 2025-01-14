#ifndef TOUCH_H_
#define TOUCH_H_

#include "calibration.h"
#include "ui/common.h"
#include "ui/control.h"

struct TouchState {
    enum class Event {
        NONE, PRESS, RELEASE
    };
    Event event;
    ui::Position position;
    int readings;
    TouchState();
    void press(int, int, int);
    void release();
};

class Touch {
private:
    Calibration &calibration_;
    TouchState state_;
    bool pressed_;
    unsigned char transmit8(unsigned char);
    unsigned int transmit16(unsigned int);
    void update();
public:
    Touch(Calibration &calibration): calibration_{calibration}, state_{}, pressed_{false} {}
    void dispatch(ui::Control &);
    static Touch *instance;
    static void initialize(Touch *);
    void clock();
    void press(bool);
};

#endif  // TOUCH_H_
