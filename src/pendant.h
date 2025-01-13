#ifndef PENDANT_H_
#define PENDANT_H_

class PendantAxisSpace {
public:
    virtual void project(char, int, int) = 0;
};

class PendantAxis {
private:
    char identifier_;
    int minimum_;
    int maximum_;
    int position_;
    int rate_;
public:
    PendantAxis(char, int, int);
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
    static Pendant *instance;
    static void initialize(Pendant *);
};

#endif  // PENDANT_H_
