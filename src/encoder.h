#ifndef ENCODER_H_
#define ENCODER_H_

class Encoder {
private:
    static signed char lookup[16];
    int count_;
    unsigned char state_;
    unsigned char shift_;
public:
    Encoder(): count_{0}, state_{0}, shift_{0} {}
    void consume(unsigned char) volatile;
    int count() { return count_ >> shift_; }
};

#endif
