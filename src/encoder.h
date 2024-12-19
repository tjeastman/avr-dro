#ifndef ENCODER_H_
#define ENCODER_H_

#include "button.h"
#include "canvas.h"
#include "color.h"
#include "common.h"
#include "control.h"
#include "decimal.h"
#include "font.h"
#include "grid.h"
#include "label.h"

class Encoder {
private:
    static signed char lookup_[16];
    int count_;
    unsigned char state_;
public:
    Encoder(): count_{0}, state_{0} {}
    void consume(unsigned char) volatile;
    int count() const { return count_; }
    void clear() { count_ = 0; }
};

class EncoderResetButton : public Button {
private:
    Encoder &encoder_;
public:
    EncoderResetButton(Encoder &, const char *, const Font &, const Color &);
    void release(Position) override;
};

class EncoderPanelRow : public Grid {
private:
    Label label_;
    Decimal decimal_;
    Label label_unit_;
    EncoderResetButton button_;
    Encoder &encoder_;
public:
    EncoderPanelRow(Encoder &, const char *, const char *, const char *, const Font &, const Color &);
    void draw(Canvas) override;
};

class EncoderPanel : public Grid {
private:
    EncoderPanelRow rowX_;
    EncoderPanelRow rowY_;
    EncoderPanelRow rowZ_;
public:
    EncoderPanel(Font &, Color &);
};

#endif
