/* 
 * File:   ToggleButton.cpp
 * Author: sei
 * 
 */

#include "ToggleButton.h"

ToggleButton::ToggleButton(String label, Widget *parent, void (*callback)() )
    : Button(label, parent, callback) 
{
    this->state = false;
}

void ToggleButton::input(void) 
{   
   if (buttons->press.fallingEdge()) {
        this->state = !this->state;
        this->callback();
    }  
}

void ToggleButton::draw(void) 
{    
    Button::draw();
    u8g2->setFont(u8g2_font_m2icon_9_tf);
    u8g2->setCursor(x+(128 - x -(13)),y);
    if (this->state) {
        u8g2->print((char) 70); 
    } else {
        u8g2->print((char) 69); 
    }
}
