#ifndef NAVBUTTONS_H
#define	NAVBUTTONS_H

#include <Bounce.h>


const int pinup = 0;
const int pindown = 1;
const int pinleft = 2;
const int pinright = 4;
const int pinpress = 3;
const int pinblue = 17;
const int pinred = 18;



class NavButtons {
public:
    NavButtons();

    void update();

    Bounce up = Bounce(pinup, 15);
    Bounce down = Bounce(pindown, 15);
    Bounce left = Bounce(pinleft, 15);
    Bounce right = Bounce(pinright, 15);
    Bounce press = Bounce(pinpress, 15);
    Bounce blue = Bounce(pinblue, 15);
    Bounce red = Bounce(pinred, 15);
};

#endif	/* NAVBUTTONS_H */