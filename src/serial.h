#ifndef SERIAL_H_
#define SERIAL_H_

class Serial {
public:
    Serial() { }
    void initialize() const;
    void operator<<(char) const;
    void operator<<(const char*) const;

private:
    void write(char) const;
};

#endif
