/* 
 * File:   slpash.h
 * Author: sei
 *
 */

#ifndef SPLASH_H
#define	SPLASH_H

#include <Widget.h>


class Splash : public Widget {
public:
    Splash(NavButtons *buttons, U8G2 *u8g2);

    void draw();
    void input();
  
    void set_target(Widget *target);

private:
    int timeout_counter;
    Widget *target;
    uint32_t start_millis;
    boolean freshlystarted;
};

#endif	/* SPLASH_H */

