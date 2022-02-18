/* 
 * File:   splash.cpp
 * Author: sei
 * 
 */

#include "splash.h"


Splash::Splash(NavButtons *buttons, U8G2 *u8g2)
    : Widget(buttons, u8g2)
{
    freshlystarted = true;
}

void Splash::set_target(Widget *target) {
    this->target = target;
}


void Splash::input(void) 
{   
    if (buttons->press.fallingEdge()) {
        target->claim_input();
        target->claim_draw();
    }  
}

void Splash::draw(void) {
   
    u8g2->setFont(u8g2_font_bubble_tr);
    u8g2->drawStr(0,24,"Teensy");
    u8g2->drawStr(0,48,"LockIn");
    u8g2->setFont(u8g2_font_streamline_hand_signs_t);
    u8g2->setCursor(128-21,64);

    // draw blinking colon
    if (Widget::blink) {
        u8g2->print((char) 61);
    } else {
        u8g2->print((char) 52);
    }

    if (freshlystarted) {
        freshlystarted = false;
        start_millis = millis();
    }

    if (millis() > (start_millis+1500)) {
        target->claim_input();
        target->claim_draw();
        freshlystarted = true;
    }
}
