#ifndef DISPLAY_H_
#define DISPLAY_H_

class Display {
public:
    enum class Orientation {
        PORTRAIT = 0,
        LANDSCAPE = 1,
    };
private:
    void transmit(unsigned int);
    void command(unsigned int);
    void command(unsigned int, unsigned int);
    Orientation orientation_;
    int width_;
    int height_;
public:
    Display(Orientation);
    void initialize();
    void data(unsigned int);
    void address(unsigned int, unsigned int, unsigned int, unsigned int);
    int width() const { return width_; };
    int height() const { return height_; };
};

#endif
