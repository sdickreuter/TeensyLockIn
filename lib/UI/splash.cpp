/* 
 * File:   splash.cpp
 * Author: sei
 * 
 */

#include "splash.h"


Splash::Splash(NavButtons *buttons, U8G2 *u8g2)
    : Widget(buttons, u8g2)
{

}

void Splash::set_target(Widget *target) {
    this->target = target;
}

void Splash::input(void) 
{   
    if (buttons->press.risingEdge()) {
        target->claim_input();
        target->claim_draw();
    }  
}

void Splash::draw(void) {
   
    u8g2->setFont(u8g2_font_10x20_me);	// choose a suitable font
    u8g2->drawStr(32,32,"HELLO!");

    // draw blinking colon
    if (Widget::blink) {
            char buf[1];
            u8g2->setFont(u8g2_font_open_iconic_all_2x_t);	// choose a suitable font
            buf[0] = 71;
            u8g2->drawStr(128-16,64,buf);
    }
}
