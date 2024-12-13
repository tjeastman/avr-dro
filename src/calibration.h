#ifndef CALIBRATION_H_
#define CALIBRATION_H_

#include "canvas.h"
#include "common.h"
#include "target.h"

class Calibration {
private:
    float theta_[2][3];
public:
    Calibration();
    Position translate(Position) const;
    void process(const float A[9][3], const int X[9], const int Y[9]);
    void save() const;
};

class CalibrationProcedure {
private:
    int index_;
    float A_[9][3];
    int X_[9];
    int Y_[9];
public:
    CalibrationProcedure(const Shape &);
    bool done() const;
    void consume(const Position &);
    void update(Calibration &) const;
    void move(Canvas &) const;
};

class CalibrationPanel : public Control {
private:
    CalibrationProcedure &procedure_;
    Target target_;
public:
    CalibrationPanel(CalibrationProcedure &, const Color &);
    void draw(Canvas) override;
    void press(Position) override;
    void release(Position) override;
};

#endif
