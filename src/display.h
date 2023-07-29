#ifndef DISPLAY_H_
#define DISPLAY_H_

class Display {
public:
    enum class Orientation {
        PORTRAIT = 0,
        LANDSCAPE = 1,
    };
private:
    void transmit(unsigned int) const;
    void command(unsigned int) const;
    void command(unsigned int, unsigned int) const;
    Orientation orientation_;
    int width_;
    int height_;
public:
    Display(Orientation);
    void initialize() const;
    void data(unsigned int) const;
    void address(unsigned int, unsigned int, unsigned int, unsigned int) const;
    int width() const { return width_; };
    int height() const { return height_; };
};

#endif
