/* 
 * File:   MenuItem.cpp
 * Author: sei
 * 
 * Created on 21. August 2014, 22:35
 */

#include "MenuItem.h"

MenuItem::MenuItem(Widget *target,String label, Widget *parent)
    : Widget(parent) 
{
    this->label = label;
    this->target = target;
    this->height = 10;
}

MenuItem::MenuItem(String label, Widget *parent)
    : Widget(parent) 
{
    this->label = label;
    this->height = 10;
}

void MenuItem::set_target(Widget *target) {
    this->target = target;
}

void MenuItem::input(void) 
{   
    if (buttons->press.fallingEdge()) {
        target->claim_input();
        target->claim_draw();
    }  
}

/*
 * function draw_clock()
 *
 * function for drawing the clock-face
 */
void MenuItem::draw(void) 
{    
    u8g2->setCursor(x, y);
        
    u8g2->setFont(u8g2_font_6x10_mf);
    
    u8g2->print(label);   
    
}
