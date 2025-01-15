#ifndef TOUCH_H_
#define TOUCH_H_

#include "calibration.h"
#include "ui/common.h"
#include "ui/control.h"

class TouchState {
public:
    enum class Event {
        NONE,
        PRESS,
        RELEASE
    };

private:
    Event event_;
    ui::Position position_;
    int readings_;

public:
    TouchState();
    void press(int, int, int);
    void release();
    void dispatch(const Calibration&, ui::Control&);
};

class Touch {
private:
    const Calibration& calibration_;
    TouchState state_;

public:
    Touch(const Calibration&);
    void dispatch(ui::Control&);

private:
    unsigned char transmit8(unsigned char);
    unsigned int transmit16(unsigned int);
    void update();
    void clear();
    bool interrupt();
    void transition();
};

#endif // TOUCH_H_
