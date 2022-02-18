/* 
 * File:   Button.cpp
 * Author: sei
 * 
 */

#include "Button.h"

Button::Button(String label, Widget *parent, void (*callback)() )
    : Widget(parent) 
{
    this->label = label;
    this->height = 10;
    this->callback = callback;
}

void Button::set_callback(void (*callback)()) {
    this->callback = callback;
}

void Button::input(void) 
{   
    if (buttons->press.fallingEdge()) {
        this->callback();
    }  
}

void Button::draw(void) 
{    
    u8g2->setCursor(x, y);
        
    u8g2->setFont(u8g2_font_6x10_mf);
    
    u8g2->print(label);   
    
}
