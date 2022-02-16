/* 
 * File:   MenuItem.cpp
 * Author: sei
 * 
 * Created on 21. August 2014, 22:35
 */

#include "MenuItem.h"

MenuItem::MenuItem(Widget *target,String label, Widget *parent)
    : Button(label, parent, nullptr) 
{
    this->target = target;
}

MenuItem::MenuItem(String label, Widget *parent)
    : Button(label, parent, nullptr) 
{
    this->target = target;
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
