#ifndef PENDANT_H_
#define PENDANT_H_

class PendantAxisSpace;

class PendantAxis {
public:
    enum class Identifier {
        NONE, X, Y, Z
    };
private:
    Identifier identifier_;
    int minimum_;
    int maximum_;
    int position_;
    int rate_;
public:
    PendantAxis(Identifier, int, int);
    void increment(int) volatile;
    void decrement(int) volatile;
    void pace(int) volatile;
    void project(PendantAxisSpace &) const;
};

class Pendant {
private:
    PendantAxis axes_[4];
    int index_;
    int delta_;
    unsigned char state_;
public:
    Pendant();
    void turn(unsigned char) volatile;
    void press(unsigned char) volatile;
    void pace(unsigned int) volatile;
    void project(PendantAxisSpace &) const;
};

class PendantAxisSpace {
public:
    virtual void project(PendantAxis::Identifier, int, int) = 0;
};

#endif  // PENDANT_H_
