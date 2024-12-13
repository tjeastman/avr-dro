#include <avr/eeprom.h>

#include "calibration.h"

Calibration::Calibration()
{
    // identity transform
    theta_[0][0] = 1.0;
    theta_[0][1] = 0.0;
    theta_[0][2] = 0.0;
    theta_[1][0] = 0.0;
    theta_[1][1] = 1.0;
    theta_[1][2] = 0.0;
}

Position Calibration::translate(Position position) const
{
    int x = position.x;
    int y = position.y;
    position.x = theta_[0][0] * x + theta_[0][1] * y + theta_[0][2];
    position.y = theta_[1][0] * x + theta_[1][1] * y + theta_[1][2];
    return position;
}

void Calibration::process(const float A[9][3], const int X[9], const int Y[9])
{
    // calculate M = A^T * A
    float M[3][3];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            M[i][j] = 0.0;
        }
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 9; ++k) {
                M[i][j] += A[k][i] * A[k][j];
            }
        }
    }

    // calculate det(M)
    float detM = 0.0;
    detM += M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]);
    detM -= M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0]);
    detM += M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]);

    // calculate adj(M)
    float C[3][3];

    C[0][0] = M[1][1] * M[2][2] - M[1][2] * M[2][1];
    C[0][1] = -(M[1][0] * M[2][2] - M[1][2] * M[2][0]);
    C[0][2] = M[1][0] * M[2][1] - M[1][1] * M[2][0];

    C[1][0] = -(M[0][1] * M[2][2] - M[0][2] * M[2][1]);
    C[1][1] = M[0][0] * M[2][2] - M[0][2] * M[2][0];
    C[1][2] = -(M[0][0] * M[2][1] - M[0][1] * M[2][0]);

    C[2][0] = M[0][1] * M[1][2] - M[0][2] * M[1][1];
    C[2][1] = -(M[0][0] * M[1][2] - M[0][2] * M[1][0]);
    C[2][2] = M[0][0] * M[1][1] - M[0][1] * M[1][0];

    float adjM[3][3];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            adjM[i][j] = C[j][i];
        }
    }

    for (int i = 0; i < 3; ++i) {
        theta_[0][i] = 0.0;
        theta_[1][i] = 0.0;
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 9; ++k) {
                theta_[0][i] += adjM[i][j] * A[k][j] * X[k];
                theta_[1][i] += adjM[i][j] * A[k][j] * Y[k];
            }
        }
    }
    for (int i = 0; i < 3; ++i) {
        theta_[0][i] /= detM;
        theta_[1][i] /= detM;
    }
}

void Calibration::save() const
{
    eeprom_write_block((const void *)theta_, 0, 2 * 3 * sizeof(float));
}

CalibrationProcedure::CalibrationProcedure(const Shape &shape)
{
    index_ = 0;

    X_[0] = 20;
    X_[1] = 20;
    X_[2] = 20;
    X_[3] = shape.width / 2 - 1;
    X_[4] = shape.width / 2 - 1;
    X_[5] = shape.width / 2 - 1;
    X_[6] = shape.width - 1 - 20;
    X_[7] = shape.width - 1 - 20;
    X_[8] = shape.width - 1 - 20;

    Y_[0] = 20;
    Y_[1] = shape.height / 2 - 1;
    Y_[2] = shape.height - 1 - 20;
    Y_[3] = 20;
    Y_[4] = shape.height / 2 - 1;
    Y_[5] = shape.height - 1 - 20;
    Y_[6] = 20;
    Y_[7] = shape.height / 2 - 1;
    Y_[8] = shape.height - 1 - 20;
}

bool CalibrationProcedure::done() const
{
    return index_ == 9;
}

void CalibrationProcedure::consume(const Position &position)
{
    A_[index_][0] = position.x;
    A_[index_][1] = position.y;
    A_[index_][2] = 1.0;

    index_++;
}

void CalibrationProcedure::update(Calibration &calibration) const
{
    calibration.process(A_, X_, Y_);
}

void CalibrationProcedure::move(Canvas &canvas) const
{
    return canvas.move({X_[index_] - 20, Y_[index_] - 20});
}

CalibrationPanel::CalibrationPanel(CalibrationProcedure &procedure, const Color &color): procedure_{procedure}, target_{40, color}
{
}

void CalibrationPanel::draw(Canvas canvas)
{
    procedure_.move(canvas);
    target_.draw(canvas);
}

void CalibrationPanel::press(Position position)
{
    target_.press(position);
}

void CalibrationPanel::release(Position position)
{
    procedure_.consume(position);
    target_.release(position);
}
