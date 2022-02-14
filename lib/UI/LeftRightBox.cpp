/* 
 * File:   LeftRightBox.cpp
 * Author: sei
 * 
 * Created on 24. August 2014, 19:09
 */

#include "LeftRightBox.h"

LeftRightBox::LeftRightBox(Widget *parent, const String label ) 
    : Widget(parent)
{
    this->label = label;
    this->height = 12;
    has_input = false;
    direction = 0;
}

void LeftRightBox::claim_input() {
    Widget::claim_input();
    has_input = true;
    direction = 0;
}

boolean LeftRightBox::is_increased() {
    if (direction >= 1) {
        direction = 0;
        return true;
    }
    else return false;
}

boolean LeftRightBox::is_decreased() {
    if (direction <= -1) {
        direction = 0;
        return true;
    }
    else return false;   
}

void LeftRightBox::draw() {
    u8g2->setCursor(x, y);
        
    u8g2->setFont(u8g2_font_6x10_mf);
    
    u8g2->print(label);

    u8g2->setFont(u8g2_font_cu12_h_symbols);
    
    u8g2->setCursor(x+32,y);
    
    char buf[3];
    buf[0] = indicators[0];
    buf[1] = indicators[1];
    buf[2] = indicators[2];
        
    if (has_input) buf[(direction + 1)] -= 1;
    
    u8g2->print( buf );    
}

void LeftRightBox::input() {       
    if (buttons->press.risingEdge()) {
        release_input(); 
        has_input = false;        
    } 
}