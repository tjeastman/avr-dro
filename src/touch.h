#ifndef TOUCH_H_
#define TOUCH_H_

#include <stdint.h>

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
    int16_t readings_;

public:
    TouchState();
    void press(int16_t, int16_t);
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
    uint8_t transmit8(uint8_t);
    uint16_t transmit16(uint16_t);
    void update();
    void clear();
    bool interrupt();
    void transition();
};

#endif // TOUCH_H_
