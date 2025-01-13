#ifndef SERIAL_H_
#define SERIAL_H_

class Serial {
public:
    Serial() {}
    void operator<<(char) const;
    void operator<<(const char *) const;
    void write(unsigned int, int) const;
private:
    void write(char) const;
};

#endif
