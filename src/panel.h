#ifndef PANEL_H_
#define PANEL_H_

#include "label.h"
#include "integer.h"
#include "grid.h"
#include "box.h"

class Panel {
private:
    Label label1_;
    Label label2_;
    Label label3_;
    Label label4_;
    Label label5_;
    Label label6_;
    Integer integer_;
    Integer integer0_;
    Box box_;
    Box box0_;
    Grid grid_;
public:
    Panel(Color &);
    void draw(Canvas);
    void update(int);
};

#endif
